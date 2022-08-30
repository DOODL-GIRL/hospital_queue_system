#ifndef B_SCAN_H
#define B_SCAN_H

class Patient;
class B_scan
{
private:
    Patient* cur_patient;//当前B超病人
    int diagnosed_num;//当天已经使用过这台B超机的病人数目
    int time_left;//当前B超病人剩余时间

public:
    B_scan();
    void SetPatient(Patient* patient);//设置当前就诊病人
    Patient* GetPatient();////获取当前病人
    int Gettime_left();//获取当前病人剩余时间
    void Settime_left(int time);//设置当前病人的剩余时间
};


#endif // B_SCAN_H
