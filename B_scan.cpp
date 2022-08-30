#include "B_scan.h"
#include "patient.h"

B_scan::B_scan()
{
    cur_patient = NULL;
    diagnosed_num = 0;
    time_left = 0;
}

void B_scan::SetPatient(Patient* patient)//设置当前就诊病人
{
    cur_patient = patient;
    if (cur_patient == NULL)
        time_left = 0;
    else
        time_left = patient->Get_Bscan_time() - 1;
}

Patient* B_scan::GetPatient()//获取当前病人
{
    return cur_patient;
}

int B_scan::Gettime_left()//获取当前病人剩余时间
{
    return time_left;
}

void B_scan::Settime_left(int time)//设置当前病人的剩余时间
{
    time_left = time;
}
