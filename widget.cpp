#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QMessageBox>
#include <QMovie>
#include <string>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <stdlib.h>
#include<fstream>
using namespace std;



Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setFixedSize(1200,850);
    setWindowTitle("医院排队叫号系统");


    ui->picture_view->setPixmap(QPixmap(":/img/2.jpg"));
//    QMovie *movie =new QMovie(":/img/1.gif");
//    ui->picture_view->setMovie(movie);
//    movie->start();

    ui->queue_table->setEditTriggers(QAbstractItemView::NoEditTriggers);//表格内容不可编辑
    ui->queue_table->setSelectionMode(QAbstractItemView::NoSelection);		//设置不可选
    ui->queue_table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);  //设置滚动隐藏
    ui->queue_table->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->queue_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->queue_table->item(0,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->queue_table->horizontalHeader()->setStyleSheet(
    "QHeaderView::section{background-color:rgba(255,255,255,100);"
    "font:12pt '黑体';color: black;};");
    ui->queue_table->verticalHeader()->setStyleSheet(
    "QHeaderView::section{background-color:rgba(255,255,255,100);"
    "font:12pt '黑体';color: black;};");

    QPalette pBuff = ui->queue_table->palette();
    pBuff.setBrush(QPalette::Base,QBrush(QColor(255,255,255,100)));
    ui->queue_table->setPalette(pBuff);




    count=0;//挂号病人序号初始化
    cur_min=0;//时间初始化

    //设置tabWidget样式
    ui->tabWidget->setStyleSheet(
                    "QTabWidget{"
                    "background-color:transparent;"
                    "}"
                    "QTabWidget::pane{"
                    "    border:2px;"
                    "}"
                    "QTabWidget::tab-bar{"
                    "        alignment:left;"
                    "}"
                    "QTabBar::tab{"
                    "    background:rgb(14, 106, 175);"
                    "    color:white;"
                    "    min-width:35ex;"
                    "    min-height:10ex;"
                    "}"
                    "QTabBar::tab:hover{"
                    "    background:rgb(255, 255, 255, 100);"
                    "color:black;"
                    "}"
                    "QTabBar::tab:selected{"
                    "    border-color: black;"
                    "    background:red;"
                    "    color:white;"
                    "}"
                    );

    QImage _image;
    _image.load(":/img/7.jpeg");
    setAutoFillBackground(true);   // 这个属性一定要设置
    QPalette pal(palette());
    pal.setBrush(QPalette::Window, QBrush(_image.scaled(size(), Qt::IgnoreAspectRatio,
                       Qt::SmoothTransformation)));
    setPalette(pal);






    //挂号操作
    connect(ui->register_btn,&QPushButton::clicked,[=](){
        if(GetPatient_name()!=NULL)
        {
            Patient* new_patient = new(nothrow)Patient;
            if (new_patient == NULL)
                exit(EXIT_FAILURE);
            new_patient->Register(++count, GetPatient_name(),GetPatient_department(),GetPatient_doctor());
            queues[GetPatient_department()-1].EnQueue(new_patient);
        }
        //消息提示框
        static QMessageBox box;
        box.setStyleSheet("QLabel{"
            "min-width: 300px;"
            "min-height: 150px; "
            "font-size:24px;"
            "}");
        if(GetPatient_name()!=NULL)
            box.setText("挂号成功，您的编号为"+QString::number(count));
        else
            box.setText("挂号失败，请输入您的姓名！");
        box.setWindowTitle("挂号结果");
        box.setWindowIcon(QPixmap(":/img/4.jpg"));
        box.exec();
        //重置输入框
        ui->patient_name->clear();
        ui->patient_department->setValue(1);
        ui->patient_doctor->setValue(0);
    });


    //时间显示
    connect(ui->next_time_btn,&QPushButton::clicked,[=](){
        if(cur_min==480)
        {
            static QMessageBox box;
            box.setStyleSheet("QLabel{"
                "min-width: 300px;"
                "min-height: 150px; "
                "font-size:24px;"
                "}");
            box.setText("医院下班啦，请明天再来哦~");
            box.setWindowTitle("下班通知");
            box.setButtonText(1,"确定");
            //box.setIconPixmap(QPixmap(":/img/1.jpg").scaled(360,270));
            box.exec();
        }
        else
        {
            cur_min++;
            //LCD显示时间
            ui->cur_time->display(cur_min);
            //显示各个医生当前就诊患者姓名和各个科室排队人数
            for (int i = 0; i < 15; i++)//更新每个科室对应的病人队列
            {
                for (int j = 0; j < 3; j++)//检查每个医生当前病人是否诊断完
                {
                    if (doctors[i][j].Gettime_left() > 0)//当前病人尚未诊断完
                        doctors[i][j].Settime_left(doctors[i][j].Gettime_left() - 1);
                    else//当前病人诊断完
                    {
                        //释放诊断完的当前病人
                        Patient* patient_diagnosed = doctors[i][j].GetPatient();
                        if (patient_diagnosed != NULL)
                        {
                            fstream f;
                            f.open("department" + to_string(i + 1) + "_doctor" + to_string(j + 1) + ".txt", ios::out | ios::app);
                            f <<"   "<<patient_diagnosed->Get_id()<<"     "<< patient_diagnosed->Get_name().toStdString() << "    " << patient_diagnosed->Get_visit_time() << "min    "<<patient_diagnosed->Get_Bscan_time()<<"min  " << endl;
                            f.close();
                            if (patient_diagnosed->Get_Bscan_time() != 0)//需要做B超
                                queues[15].EnQueue(patient_diagnosed);
                            else
                                delete patient_diagnosed;
                        }
                        //为医生安排新的病人
                        Patient* temp = queues[i].DeQueue(0, j + 1);
                        doctors[i][j].SetPatient(temp);
                        if (temp != NULL)
                        {
                            QString text=QString::number(cur_min)+"：请"+QString::number(temp->Get_id())
                                    +"号病人" +temp->Get_name()+"前往"+QString::number(i+1)+"号科室医生"
                                    +QString::number(j+1)+"处就诊！";
                            ui->textBrowser->append(text);
                            ui->queue_table->setItem(i,j,new QTableWidgetItem(QString::number(doctors[i][j].GetPatient()->Get_id())+" "+doctors[i][j].GetPatient()->Get_name()));
                            ui->queue_table->item(i,j)->setBackground(QColor(255,255,0,100));
                        }
                        else
                        {
                            ui->queue_table->setItem(i,j,new QTableWidgetItem("空闲"));
                            ui->queue_table->item(i,j)->setBackground(QColor(255,255,255,80));
                        }
                    }

                }
                ui->queue_table->setItem(i,3,new QTableWidgetItem(QString::number(queues[i].GetLength())));
            }
            for (int k = 0; k < 3; k++)//检查B超室的每个B超机并更新
            {
                if (B_scans[k].Gettime_left() > 0)//当前病人尚未B超完
                    B_scans[k].Settime_left(B_scans[k].Gettime_left() - 1);
                else//当前病人B超完
                {
                    //释放B超完的当前病人
                    Patient* patient_Bscaned = B_scans[k].GetPatient();
                    if (patient_Bscaned != NULL)
                        delete patient_Bscaned;
                    //为B超机安排新的病人
                    Patient* temp = queues[15].DeQueue(1, 0);
                    B_scans[k].SetPatient(temp);
                    if (temp != NULL)
                    {
                        QString text=QString::number(cur_min)+"：请"+QString::number(temp->Get_id())
                                +"号病人" +temp->Get_name()+"前往B超室"
                                +QString::number(k+1)+"台B超机处进行B超！";
                        ui->textBrowser->append(text);
                        ui->queue_table->setItem(15,k,new QTableWidgetItem(QString::number(temp->Get_id())+" "+temp->Get_name()));
                        ui->queue_table->item(15,k)->setBackground(QColor(255,255,0,100));
                    }
                    else
                    {
                        ui->queue_table->setItem(15,k,new QTableWidgetItem("空闲"));
                        ui->queue_table->item(15,k)->setBackground(QColor(255,255,255,80));
                    }
                }
                ui->queue_table->setItem(15,3,new QTableWidgetItem(QString::number(queues[15].GetLength())));
            }
        }
    });

    //查询记录
    connect(ui->search_btn,&QPushButton::clicked,[=](){
        int department=ui->doctor_department->value();
        int doctor_num=ui->doctor_num->value();
        ui->search_result->clear();
        fstream f;
        f.open("department" + to_string(department) + "_doctor" + to_string(doctor_num) + ".txt", ios::in);
        ui->search_result->clear();
        ui->search_result->append("患者编号 患者姓名 就诊时间 B超时间");
        string s;
        while (getline(f,s))
        {
           ui->search_result->append(QString::fromStdString(s));
        }
        f.close();
    });



}

QString Widget::GetPatient_name()
{
    return ui->patient_name->text();
}

int Widget::GetPatient_department()
{
    return ui->patient_department->value();
}
int Widget::GetPatient_doctor()
{
    return ui->patient_doctor->value();
}



Widget::~Widget()
{
    delete ui;
}

