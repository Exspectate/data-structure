#include"stdio.h"
#include "stdlib.h"
/*
int FindMinInCol(int *p,int m)
{
    int res = 0;

    for(int k = 0; k < m; k++)
    {
        res = p[res] <= p[k] ? res : k;
    }
    return res;
}

int FindMaxInRol(int*p,int m,int n,int l)
{
    int res = 0;

    for(int k = 0; k < l; k++)
    {
        res = p[res * m + n] >= p[k * m +n] ? res : k;
    }
    return res;
}

int** Find(int* Arr,int m,int n)
{
    int* rols = (int*)malloc(m * sizeof(int));
    int* cols = (int*)malloc(n * sizeof(int));

    for(int k = 0; k < m; k++)
    {
        int rol = FindMinInCol(&Arr[m * k],m);
        rols[k] = rol;
        int col = FindMaxInRol(Arr,m,k,n);
        cols[k] = col;
    }
    for(int i = 0; i < m; i++) //第i列
    {
        int a = cols[i]; //第i列最大值所在的行号为a
        int b = rols[a]; //第a行所对应的列号为b
        if(i == b)
        {
            printf("(%d,%d)",a,b);
        }
    }
    return NULL;
}
*/

int IsMinInCol(int* p,int m,int pos)
{
    for(int k = 0; k < m; k++)
    {
        if(p[k] < p[pos])
        {
            return 0;
        }
    }
    return 1;
}

int IsMaxInRol(int* Arr,int m,int n,int posx,int posy)
{
    for(int k = 0; k < n; k++)
    {
        if(Arr[k * m + posx] > Arr[posy * m + posx])
        {
            return 0;
        }
    }
    return 1;
}

void Find(int* Arr,int m,int n)
{
    for(int k = 0; k < n; k++)
    {
        for(int i = 0; i < m; i++)
        {
            int a = IsMinInCol(&Arr[k * m],m,i);
            int b = IsMaxInRol(Arr,m,n,i,k);
            if(a && b)
                printf("(%d,%d) ",i,k);
        }

    }
}

int main()
{
    int Arr[4][3] =
            {
                    {1,1,1},
                    {1,1,1},
                    {1,1,1},
                    {1,1,1}
            };
    Find((int*)Arr,3,4);
    return 0;
}

