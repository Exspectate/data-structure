#include "stdio.h"
#include "stdlib.h"
#include "math.h"


int count = 0;

int IsSafe(int n,int* QueenList)
{
    for(int i = 0; i < n; i++)
    {
        if(QueenList[i] == QueenList[n] ||
        abs(i - n) == abs(QueenList[i] - QueenList[n]))
        {
            return 0;
        }
    }
    return 1;
}

void Print(int* QueenList)
{
    for(int i = 0; i < 8; i ++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(QueenList[i] == j)
                printf("Q ");
            else
            {
                printf("# ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

void Add(int i,int* QueenList)
{
    if(i == 8)
    {
        printf("%d\n",count);
        Print(QueenList);
        count++;
        return;
    }
    else
    {
        for(int j = 0; j < 8; j++)
        {
            QueenList[i] = j;
            if(IsSafe(i,QueenList))
            {
                Add(i + 1,QueenList);
            }
        }
        return;

    }
}


void Test(int* QueenList)
{

    for(int k = 0; k < 8; k++)
    {
        QueenList[k] = 0;
    }

    Add(0,QueenList);
}

int main()
{
    int QueenList[11] = {0};
    Test(QueenList);
    return 0;
}

