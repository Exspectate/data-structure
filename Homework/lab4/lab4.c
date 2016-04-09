
#include "stdio.h"
#include "stdlib.h"

typedef struct person
{
    int Operation;
    struct person* Next;
}Person;

typedef struct queue
{
    int size;
    Person* First;
}Queue;

typedef struct bank
{
    Queue* Q1;	//CPF
    Queue* Q2;	//CreditCard
    Queue* Q3;
    Queue* Q4;
    Queue* Q5;	//FinanceCard
    Queue* Q6;
}Bank;

Person* MakePerson(int Operation)
{
    Person* Temp = (Person*)malloc(sizeof(Person));
    Temp->Next = NULL;
    Temp->Operation = Operation;
    return Temp;
}

Queue * MakeQueue()
{
    Queue* Q = (Queue*)malloc(sizeof(Queue));
    Q->First = NULL;
    Q->size = 0;
    return Q;
}

Bank* MakeBank()
{
    Bank* B = (Bank*)malloc(sizeof(Bank));
    B->Q1 = MakeQueue();
    B->Q2 = MakeQueue();
    B->Q3 = MakeQueue();
    B->Q4 = MakeQueue();
    B->Q5 = MakeQueue();
    B->Q6 = MakeQueue();
    return B;
}

int IsEmpty(Queue Q)
{
    return Q.size == 0;
}



void EnQueue(Queue* Q,Person* P)
{
    if(Q == NULL)
    {
        //printf("Queue is not exist!");
        printf("队列不存在\n");

        return;
    }
    else
    {
        if(Q->size == 0)
        {
            Q->First = P;
        }
        else
        {
            Person *Temp = Q->First;
            while(Temp->Next != NULL)
            {
                Temp = Temp->Next;
            }
            Temp->Next = P;
        }

        Q->size++;
    }
}

int DeQueue(Queue* Q, Person *p)
{
    if(Q == NULL)
    {
        //printf("Queue is not exist!\n");
        printf("队列不存在\n");

        return 0;
    }
    else
    {
        if(Q->size == 0)
        {
            //printf("The Queue Is Empty!\n");
            printf("队列为空\n");

            return 0;
        }
        else
        {
            Person *Temp = Q->First;
            Q->First = Temp->Next;
            Q->size--;
            p = Temp;
            return 1;
        }
    }
}

void AddToQueues(Bank* B,Person* P)
{
    switch(P->Operation)
    {
        case 0:
        {
            EnQueue(B->Q1,P);
            break;
        }
        case 1:
        {
            Queue* Temp;
            Temp = B->Q2->size < B->Q3->size ? B->Q2 : B->Q3;
            Temp = Temp->size < B->Q4->size ? Temp : B->Q4;
            EnQueue(Temp,P);
            break;
        }
        case 2:
        {

            if(B->Q5->size == 0 || B->Q6->size == 0)
            {
                if(B->Q5->size  == 0)
                {
                    EnQueue(B->Q5,P);
                }
                else
                {
                    EnQueue(B->Q6,P);
                }
            }
            else
            {
                if(B->Q2 ->size == 0 || B->Q3->size == 0 || B->Q4->size == 0)
                {
                    if(B->Q2->size == 0)
                    {
                        EnQueue(B->Q2,P);
                    }
                    else if(B->Q3->size == 0)
                    {
                        EnQueue(B->Q3,P);
                    }
                    else
                    {
                        EnQueue(B->Q4,P);
                    }
                }
                else
                {
                    Queue* Temp = B->Q5->size < B->Q6->size ? B->Q5 : B->Q6;
                    EnQueue(Temp,P);
                }
            }
            break;
        }
        default:
        {
            printf("Fatel ERROR!\n");
        }
    }
}

void ShowQueue(Queue* Q)
{
    if(Q == NULL)
    {
        printf("Queue is not exist!");
        return;
    }

    if(Q->size == 0)
    {
        //printf("Queue is Empty\n");
        printf("队列为空\n");

        return;
    }

    Person* Temp = Q->First;
    //printf("This Queue Has %d People\n",Q->size);
    printf("本队列有%d人在排队\n",Q->size);

    while(Temp->Next != NULL)
    {
        printf("业务为：%d\n",Temp->Operation);
        Temp = Temp->Next;
    }
    printf("业务为：%d\n",Temp->Operation);
    return;

}

void ShowBank(Bank *B)
{
    printf("Q1:");
    ShowQueue(B->Q1);
    printf("Q2:");
    ShowQueue(B->Q2);
    printf("Q3:");
    ShowQueue(B->Q3);
    printf("Q4:");
    ShowQueue(B->Q4);
    printf("Q5:");
    ShowQueue(B->Q5);
    printf("Q6:");
    ShowQueue(B->Q6);
}

void DelWholeQueue(Queue* Q)
{
    if(Q == NULL || Q->First == NULL)
    {
        return;
    }
    Person* Temp = Q->First;
    Person* p;
    while(Temp->Next != NULL)
    {
        DeQueue(Q,p);
        free(&p);
    }

}
void DelBank(Bank* B)
{
    if(B == NULL)
    {
        return;
    }
    DelWholeQueue(B->Q1);
    DelWholeQueue(B->Q2);
    DelWholeQueue(B->Q3);
    DelWholeQueue(B->Q4);
    DelWholeQueue(B->Q5);
    DelWholeQueue(B->Q6);

}
void HCI(Bank* B,int *state)
{
    int choose0;
    printf("欢迎使用本系统!\n");
    printf("0:关闭系统\n");
    printf("1:排队\n");
    printf("2:业务完成\n");
    printf("3:当前窗口状态\n");
    fflush(stdin);
    if(scanf("%d",&choose0) != 1)
    {
        printf("输入有错!");
        HCI(B,state);
    }
    if(choose0 == 0)
    {
        DelBank(B);
        B = NULL;
        *state = 0;
        printf("关机...");
        return;
    }
    else if(choose0 == 1)
    {
        printf("请选择服务:\n0:公积金\n1:银行卡\n2:理财卡\n");
        int a;
        fflush(stdin);
        if(scanf("%d",&a) == 1 && 0 <= a && a <=2)
        {
            Person *Temp = MakePerson(a);
            AddToQueues(B,Temp);
        }
        else
        {
            printf("输入有误!\n");
            HCI(B,state);
        }
    }
    else if(choose0 == 2)
    {
        printf("请输入窗口号:\n");
        int a;
        fflush(stdin);
        if(scanf("%d",&a) == 1 && 1 <= a && a <=6)
        {
            Person *T;
            switch (a)
            {
                case 1:
                {
                    DeQueue(B->Q1,T);
                    break;
                }
                case 2:
                {
                    DeQueue(B->Q2,T);
                    break;
                }
                case 3:
                {
                    DeQueue(B->Q3,T);
                    break;
                }
                case 4:
                {
                    DeQueue(B->Q4,T);
                    break;
                }
                case 5:
                {
                    DeQueue(B->Q5,T);
                    break;
                }
                case 6:
                {
                    DeQueue(B->Q6,T);
                    break;
                }
            }
        }
        else
        {
            printf("输入有误!\n");
            HCI(B,state);
        }
    }
    else if(choose0 == 3)
    {
        ShowBank(B);
    }
    else
    {
        printf("输入有误!\n");
        HCI(B,state);
    }


}

void Test()
{
    Bank *B = MakeBank();
    int* state = (int*)malloc(sizeof(int));
    *state = 1;
    while(*state == 1)
    {
        HCI(B,state);
    }
}
int main()
{
    Test();
    return 0;
}



