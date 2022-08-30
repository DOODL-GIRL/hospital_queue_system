#ifndef DOCTOR_H
#define DOCTOR_H

class Patient;
class Doctor
{
private:
    Patient* cur_patient;//当前就诊病人
    int diagnosed_num;//当天已经诊断过的病人数目
    int time_left;//当前就诊病人剩余时间

public:
    Doctor();
    void SetPatient(Patient* patient);//设置当前就诊病人
    Patient* GetPatient();////获取当前病人
    int Gettime_left();//获取当前病人剩余时间
    void Settime_left(int time);//设置当前病人的剩余时间
};

#endif // DOCTOR_H
