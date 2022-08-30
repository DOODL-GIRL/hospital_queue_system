#ifndef PATIENT_H
#define PATIENT_H
#include <QString>
using namespace std;

class Patient
{
private:
    int id;//分配给每个病人的唯一编号
    QString name;//病人挂号登记的姓名
    int visit_time;//就诊时间（>0）
    int Bscan_time;//B超时间（>=0）
    int my_department;//选择的科室（0~15）
    int my_doctor;//选择或分配的医生（0为未主动选择医生；1，2，3为主动选择对应医生）
    Patient* next;//在队列中的下一个病人

public:
    //挂号函数，参数从界面用户输入获取
    void Register(int patient_id, QString patient_name, int patient_department, int patient_doctor);
    int Get_visit_time();//获取就诊时间
    int Get_Bscan_time();//获取B超时间
    int Get_id();//获取id
    QString Get_name();//获取姓名
    friend class PatientQueue;
};
#endif // PATIENT_H
