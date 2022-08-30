#include "PatientQueue.h"
#include "patient.h"
#include<stdlib.h>
#include<iostream>
using namespace std;


PatientQueue::PatientQueue()//构造函数
{
    head = new(nothrow)Patient;
    if (head == NULL)
        exit(EXIT_FAILURE);
    head->next = NULL;

    length = 0;
}

void PatientQueue::EnQueue(Patient* new_patient)//在队尾添加新病人
{
    Patient* p = head;
    while (p->next != NULL)
        p = p->next;
    p->next = new_patient;
    length++;
}

Patient* PatientQueue::DeQueue(int B_scan_or_not,int free_doctor)//病人出队（满足条件的第一个病人）
{
    if (length == 0)
        return NULL;
    if (B_scan_or_not == 1)//B超队列直接队头病人出队即可
    {
        Patient* q = head->next;
        head->next = q->next;
        length--;
        q->next = NULL;
        return q;
    }
    //接下来是就诊室病人队列出队规则
    Patient* p = head;
    while (p->next != NULL)
    {
        //选择没有医生偏好或医生偏好刚好是free_doctor的病人出队就诊
        if (p->next->my_doctor == 0 || p->next->my_doctor == free_doctor)
        {
            Patient* q = p->next;
            p->next = q->next;
            length--;
            q->next = NULL;
            return q;
        }
        p = p->next;
    }
    return NULL;//（意思是没人想去这个医生这里看病哈哈哈）
}

int PatientQueue::GetLength()//获取队列长度
{
    return length;
}

void PatientQueue::DestroyQueue()//释放队列
{
    Patient* p = head->next;
    while (p != NULL)
    {
        Patient* q = p;
        p = p->next;
        delete q;
    }
}

PatientQueue::~PatientQueue()//析构函数，功能同释放队列函数
{
    Patient* p = head->next;
    while (p != NULL)
    {
        Patient* q = p;
        p = p->next;
        delete q;
    }
    //delete head;
}
