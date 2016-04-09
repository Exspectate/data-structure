#include "stdio.h"
#include "stdlib.h"
#include "time.h"
typedef struct car
{
    int state;
    time_t InTime;
    time_t OutTime;
    time_t StayTime;
    int ID;
}Car,*Position;

typedef struct park
{
    int Size;
    int Max;
    Position Cars;
}Park;

Car* BuildCar(int InTime,int ID)
{
    Car* Temp = (Car*)malloc(sizeof(Car));
    Temp->InTime = InTime;
    Temp->state = 0;
    Temp->ID = ID;
    return Temp;
}

Park* BuildPark()
{
    Park* Temp = (Park*)malloc(sizeof(Park));
    Temp->Max = 3;
    Temp->Cars = (Car*)malloc(Temp->Max * sizeof(Car));

    for(int k = 0; k < Temp->Max; k++)
    {
        Temp->Cars[k].state = 0;
    }
    Temp->Size = 0;
    return Temp;
}

int IsParkFull(Park *P)
{
    return P->Size == P->Max;
}

Car* Find(int ID,Park *P)
{
    if(P != NULL)
    {
        for(int k = 0;k < P->Max; k++)
        {
            if(P->Cars[k].ID == ID)
            {
                return &P->Cars[k];
            }
        }
    }
    return NULL;
}

void Delete(Car* T,Park* P)
{
    T->state = 0;
    P->Size--;
}

void InPark(Car T,Park *P)
{
    if(IsParkFull(P))
    {
        printf("无空余位置！请稍候。\n");

    }
    else
    {
        if(Find(T.ID, P))
        {
            printf("该车已存在！\n");
        }
        else
        {
            for(int k = 0; k < P->Max; k++)
            {
                if(P->Cars[k].state == 0)
                {
                    P->Cars[k].state = 1;
                    P->Cars[k].InTime = T.InTime;
                    P->Cars[k].ID = T.ID;
                    P->Size++;
                    return;
                }
            }
        }
    }
}

void Test()
{
    Park* P = BuildPark();
    int Record[1000][4];
    int SizeOfRec = 0;
    time_t BEGIN = time(NULL);

    while(1)
    {
        printf("请输入指令：\n");
        printf("0: 打印\n");
        printf("1：进出\n");
        int choose0;
        fflush(stdin);
        scanf("%d",&choose0);
        if(choose0 == 0)
        {
            for(int k = 0; k < SizeOfRec; k++)
            {
                if(Record[k][0] == 1)
                {
                    printf("%d车于%d分进入。\n",Record[k][1],Record[k][2]);
                }
                else if (Record[k][0] == 2)
                {
                    printf("%d车于%d分退出，收费%d元。\n",Record[k][1],Record[k][2],Record[k][3]);
                }
            }
        }
        else if(choose0 == 1)
        {
            printf("1：进入 或 2：离开 + ID\n");
            int choose;
            int ID;
            time_t T = time(NULL);
            int Time = T - BEGIN;
            fflush(stdin);
            scanf("%d %d",&choose,&ID);
            if(choose == 1)
            {
                Car* Temp = BuildCar(Time, ID);
                InPark(*Temp, P);
                printf("%d车进入，进入时间：%ld\n",Temp->ID,Temp->InTime);
                Record[SizeOfRec][0] = choose;
                Record[SizeOfRec][1] = ID;
                Record[SizeOfRec][2] = Time;
                Record[SizeOfRec][3] = 0;
                SizeOfRec++;

            }
            else if(choose == 2)
            {
                Car *Temp = Find(ID,P);
                if(Temp == NULL)
                {
                    printf("无此车！请重新选择。\n");
                }
                else
                {
                    Delete(Temp, P);
                    Temp->OutTime = Time;
                    Temp->StayTime = Temp->OutTime - Temp->InTime;
                    printf("%d车离开，收费%ld元\n",Temp->ID,Temp->StayTime);
                    Record[SizeOfRec][0] = choose;
                    Record[SizeOfRec][1] = ID;
                    Record[SizeOfRec][2] = Time;
                    Record[SizeOfRec][3] = Temp->StayTime;
                    SizeOfRec++;
                }
            }
            else
            {
                printf("ERROR! 请重新输入！");
            }
        }
    }

}


int main()
{
    Test();
    return 0;
}
