#include "stdio.h"
#include "stdlib.h"
#include "string.h"

struct Person;

typedef struct Person* Position;

struct Person
{
    int ID;
    int Password;
    Position Next;

};

struct List
{
    Position Head;
    int size;
};

void AddPerson(struct Person* T,struct List* L)
{

    if(L == NULL)
    {
        return;
    }
    if(L->size == 0)
    {
        L->Head = (Position)malloc(sizeof(struct Person));
        L->Head->ID = T->ID;
        L->Head->Password = T->Password;
        L->Head->Next = L->Head;
    }
    else
    {
        T->Next = L->Head->Next;
        L->Head->Next = T;
    }
    L->size++;
}

void DelPerson(Position P,struct List *L)
{
    Position Temp = L->Head;
    while(Temp->Next != P)
    {
        Temp = Temp->Next;
    }
    if(P == L->Head)
    {
        L->Head = P->Next;
    }
    Temp->Next = P->Next;
    free(P);
    L->size--;
}

void Test(int m)
{
    struct List* L;
    L = (struct List*)malloc(sizeof(struct List));
    L->size = 0;

    struct Person* A1 = (struct Person*)malloc(sizeof(struct Person));
    struct Person* A2 = (struct Person*)malloc(sizeof(struct Person));
    struct Person* A3 = (struct Person*)malloc(sizeof(struct Person));
    struct Person* A4 = (struct Person*)malloc(sizeof(struct Person));
    struct Person* A5 = (struct Person*)malloc(sizeof(struct Person));

    A1->ID = 1;
    A2->ID = 2;
    A3->ID = 3;
    A4->ID = 4;
    A5->ID = 5;

    A1->Password = 1;
    A2->Password = 2;
    A3->Password = 3;
    A4->Password = 4;
    A5->Password = 5;


    AddPerson(A1,L);
    AddPerson(A5,L);
    AddPerson(A4,L);
    AddPerson(A3,L);
    AddPerson(A2,L);

    Position Temp = L->Head;
    printf("出队序号依次为：\n");
    while(L->Head != L->Head->Next)
    {
        for(int k = 1; k < m; k++)
        {
            Temp = Temp->Next;
        }
        m = Temp->Password;
        printf("%d ",Temp->ID);
        Position NEXT = Temp->Next;
        DelPerson(Temp,L);
        Temp = NEXT;
    }
    printf("%d\n",L->Head->ID);
}
int main()
{
    Test(2);
    return 0;
}
