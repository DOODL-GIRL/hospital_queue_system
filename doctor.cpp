#include "doctor.h"
#include "patient.h"

Doctor::Doctor()
{
    cur_patient = NULL;
    diagnosed_num = 0;
    time_left = 0;
}

void Doctor::SetPatient(Patient* patient)//设置当前就诊病人
{
    cur_patient = patient;
    if (cur_patient == NULL)
        time_left = 0;
    else
        time_left = patient->Get_visit_time() - 1;
}

Patient* Doctor::GetPatient()//获取当前病人
{
    return cur_patient;
}

int Doctor::Gettime_left()//获取当前病人剩余时间
{
    return time_left;
}

void Doctor::Settime_left(int time)//设置当前病人的剩余时间
{
    time_left = time;
}
