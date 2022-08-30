#include "patient.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

void Patient::Register(int patient_id, QString patient_name, int patient_department, int patient_doctor)
{
    id = patient_id;
    name = patient_name;
    my_department = patient_department;
    my_doctor = patient_doctor;

    //srand(time(0));
    visit_time = (rand() % (15 - 5 + 1)) + 5;//就诊时间在5~15分钟随机产生，参数可调


    double P_Bscan = rand() % 100 / (double)101;
    if (P_Bscan < 0.6)//60%的概率不需要做B超，参数可调
        Bscan_time = 0;
    else
        Bscan_time = 20;//B超时间固定为30分钟，参数可调

    next = NULL;
}

int Patient::Get_visit_time()
{
    return visit_time;
}

int Patient::Get_Bscan_time()
{
    return Bscan_time;
}

int Patient::Get_id()
{
    return id;
}

QString Patient::Get_name()
{
    return name;
}
