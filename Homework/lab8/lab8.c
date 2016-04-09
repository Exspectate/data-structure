#include "stdio.h"
#include "stdlib.h"


int Map[][7] =
        {
                {0,1,1,1,1,1,0},
                {1,0,0,0,0,1,0},
                {1,0,0,1,1,0,0},
                {1,0,1,0,1,1,0},
                {1,0,1,1,0,1,0},
				{1,1,0,1,1,0,0},
				{0,0,0,0,0,0,0}
        };

int IsOK(int State,int* Areas,int Num,int color)
{
    for(int i = Num * State; i < (State + 1) * Num; i++)
    {
        if(Map[State][i % Num] != 0)
        {
            if(Areas[i % Num] == color)
            {
                return 0;
            }
        }
    }
    return 1;
}

void Print(int* Areas,int Num)
{
    for(int i = 0; i < Num; i ++)
    {
        printf("%d ",Areas[i]);
    }
    printf("\n");
}

void Paint(int State,int* Areas,int Num)
{
    if(State == Num)
    {
        Print(Areas,Num);
        return;
    }
    else
    {
        for(int j = 0; j < 4; j++)
        {
            Areas[State] = j;
            if(IsOK(State,Areas,Num,j))
            {
                Paint(State + 1,Areas,Num);
            }
        }
        return;

    }
}


void Test(int* Areas,int Num)
{

    for(int k = 0; k < Num; k++)
    {
        Areas[k] = -1;
    }

    Paint(0,Areas,Num);
}

int main()
{
    int NumOfAreas = 7;
    int* Areas = (int*)malloc(NumOfAreas * sizeof(int));
    Test(Areas,NumOfAreas);
    return 0;
}



