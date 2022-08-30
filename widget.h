#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
//#include <QString>
#include "patient.h"
#include "PatientQueue.h"
#include "doctor.h"
#include "B_scan.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    QString GetPatient_name();
    int GetPatient_department();
    int GetPatient_doctor();

    ~Widget();

private:
    Ui::Widget *ui;
    int cur_min;//当前时间
    int count;//当前挂号病人编号
    PatientQueue queues[16];//系统所需队列（15条科室队列，1条B超队列）
    Doctor doctors[15][3];//医生数组，15个科室，每个科室三个医生
    B_scan B_scans[3];//B超机数组，1个B超室，3个B超机
};
#endif // WIDGET_H
