#include "stdio.h"
#include "stdlib.h"
#include "string.h"


struct Worker
{
    int ID;
    char* Name;
    char* Job;
};

typedef struct Worker* Position;

struct List
{
    Position Workers;
    int size;
};

struct List* MakeList()
{
    struct List *T = (struct List*)malloc(sizeof(struct List));
    T->Workers = (struct Worker*)malloc(40 * sizeof(struct Worker));
    T->size = 0;

    return T;
}

void AddWorker(struct Worker T,struct List *L)
{
    if(L->size >= 40)
    {
        //printf("Out Of Space!");
        printf("超过最大限度！\n");
        return;
    }

    L->Workers[L->size].ID  = T.ID;
    L->Workers[L->size].Name = T.Name;
    L->Workers[L->size].Job = T.Job;

    L->size++;
    printf("%s 加入成功！\n",T.Name);
}

void DelWorker(int ID, struct List *L)
{
    int k = 0;
    while(L->Workers[k].ID != ID)
    {
        k++;
        if(k == L->size)
        {
            //printf("Receiver ID: %d not found!\n",ID);
            printf("%d号员工不存在！\n",ID);
            return;
        }
    }

    while(k != L->size - 1)
    {
        L->Workers[k].ID = L->Workers[k + 1].ID;
        L->Workers[k].Job = L->Workers[k + 1].Job;
        free(L->Workers[k + 1].Job);
        L->Workers[k].Name = L->Workers[k + 1].Name;
        free(L->Workers[k + 1].Name);
        k++;
    }
    L->size--;
}

void ShowList(struct List *L)
{
    if(L != NULL)
    {
        int k = 0;
        printf("当前人员名单：");
        while(k < L->size)
        {
            printf("%s  ",L->Workers[k].Name);
            k++;
        }
        printf("\n");
    }
    else
    {
        //printf("List Is Empty!");
        printf("列表为空！\n");
    }
}

void Test(struct List* L)
{
    printf("1 入职\n2 离职\n3 打印人员名单\n");
    int choose = -1;
    scanf("%d",&choose);
    switch(choose)
    {
        case 1:
            {
                printf("请依次输入：ID、姓名、工作\n");
                struct Worker T;
                T.Name = (char*)malloc(20);
                T.Job = (char*)malloc(20);
                scanf("%d %s %s",&T.ID,T.Name,T.Job);
                AddWorker(T,L);
                break;
            }
        case 2:
            {
                printf("请输入ID\n");
                int ID;
                scanf("%d",&ID);
                DelWorker(ID,L);
                break;
            }
        case 3:
            {
                ShowList(L);
                break;
            }
    }
}

int main()
{
    struct List* L = MakeList();
/*
    struct Worker A1;
    A1.ID = 1;
    A1.Name = &"MEME";
    A1.Job = &"WE";

    struct Worker A2;
    A2.ID = 2;
    A2.Name = &"MEME2";
    A2.Job = &"WE2";

    struct Worker A3;
    A3.ID = 3;
    A3.Name = &"MEME3";
    A3.Job = &"WE3";

    struct Worker A4;
    A4.ID = 4;
    A4.Name = &"MEME4";
    A4.Job = &"WE4";

    AddWorker(A1,L);
    AddWorker(A2,L);
    AddWorker(A3,L);
    ShowList(L);
    DelWorker(1, L);
    ShowList(L);
    AddWorker(A4,L);
    ShowList(L);
    DelWorker(1, L);
    ShowList(L); */
    while(1)
    {
        Test(L);
    }
    return 0;
}















