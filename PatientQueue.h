#ifndef PATIENTQUEUE_H
#define PATIENTQUEUE_H


class Patient;

class PatientQueue//以链表形式存储的病人队列
{
private:
    int length;//队列当前长度
    Patient* head;//虚拟队头结点

public:
    PatientQueue();//构造函数
    void EnQueue(Patient* new_patient);//在队尾添加新病人
    Patient* DeQueue(int B_scan_or_not, int free_doctor);//病人出队（满足条件的第一个病人）
    int GetLength();//获取队列长度
    void DestroyQueue();//释放队列
    ~PatientQueue();//析构函数，功能同释放队列函数

};

#endif // PATIENTQUEUE_H
