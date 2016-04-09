#include "stdio.h"
#include "stdlib.h"

typedef struct slemtype
{
    int ord;        //序号
    int* seat;     //坐标位置
    int di;         //方向
}SlemType;

typedef struct stack
{
    SlemType* L;
    int size;
    int max;
}Stack;

Stack* MakeStack()
{
    Stack* Temp = (Stack*)malloc(sizeof(Stack));
    Temp->max = 100;
    Temp->L = (SlemType*)malloc(Temp->max * sizeof(SlemType));
    Temp->size = 0;
    return Temp;
}

SlemType* MakeSlemType(int ord,int* seat,int di)
{
    SlemType* Temp = (SlemType*)malloc(sizeof(SlemType));
    Temp->ord = ord;
    Temp->seat = seat;
    *Temp->seat = *seat;
    Temp->di = di;
    return Temp;
}

void Push(SlemType T,Stack* S)
{
    if(S->size < S->max)
    {
        S->L[S->size].ord= T.ord;
        S->L[S->size].seat= T.seat;
        S->L[S->size].di= T.di;
        S->size++;
        printf("\nsize of S:[%d]\n",S->size);
    }
    else
    {
        printf("Stack Is Full\n");
    }
}

SlemType* Pop(Stack* S)
    {
        if(S->size != 0)
        {
            S->size--;
            return &S->L[S->size];
        }
        else
        {
            printf("Stack Is Empty!");
            return NULL;
        }
}

int Pass(int* curpos)
{
    return *curpos == 0;
}

void FootPrint(int* curpos)
{
    *curpos = 3;
}

int* NextPos(int *curpos,int di)
{
    switch(di)
    {
        case 1:
            {
                curpos++;
                break;
            }
        case 2:
            {
                curpos += 10;
                break;
            }
        case 3:
            {
                curpos--;
                break;
            }
        case 4:
            {
                curpos -= 10;
                break;
            }
    }
    return curpos;
}

void MarkPoint(int* pos)
{
    *pos = 2;
}

void Show(int** maze)
{
    int* m = (int*)maze;
    for(int k = 0; k < 10; k++)
    {
        for(int i = 0; i < 10; i++)
        {
            printf("%d ",m[10*k + i]);
        }
        printf("\n");
    }
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
}
int MazePath(int** maze,int* start,int* end)
{
    Stack* s = MakeStack();
    int* curpos = start;
    int curstep = 1;

    do
    {
        Show(maze);
        printf("cur:%ld\n",curpos - start + 1);
        if(Pass(curpos))
        {
            FootPrint(curpos);
            Show(maze);
            SlemType* e = MakeSlemType(curstep,curpos,1);
            Push((*e),s);
            if(curpos == end)
            {
                return 1;
            }

            curpos = NextPos(curpos,1);
            printf("cur:%ld\n",curpos - start + 1);

            curstep++;
        }
        else
        {
            if(s->size != 0)
            {
                SlemType* e = Pop(s);

                while((*e).di == 4 && s->size != 0)
                {
                    MarkPoint((*e).seat);
                    Show(maze);
                    e = Pop(s);
                }
                if(e->di < 4)
                {
                    e->di++;
                    Push(*e,s);
                    curpos = NextPos(e->seat,e->di);
                    printf("di:%d\n",e->di);
                    printf("cur:%ld\n",curpos - start + 1);
                }
            }
        }
    }while(s->size != 0);
    return 0;
}

int main()
{
    int maze[][10] =
    {
        {1,0,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,1,0,0,1,1},
        {1,1,1,1,0,1,0,1,1,1},
        {1,0,0,0,0,0,0,0,1,1},
        {1,0,0,0,1,1,1,0,0,1},
        {1,1,1,0,1,0,0,1,1,1},
        {1,0,1,0,0,1,0,0,0,1},
        {1,0,0,0,1,0,0,1,0,1},
        {1,0,1,0,0,0,1,0,0,1},
        {1,1,1,1,1,1,1,1,0,1}
    };
    int res = MazePath((int**)maze,&maze[0][1],&maze[9][8]);
    printf("%d\n\n",res);

    return 0;
}

