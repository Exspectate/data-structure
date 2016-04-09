#include "stdio.h"
#include "stdlib.h"

typedef struct
{
    int i,j;
    int e;
}Triple;

typedef struct
{
    Triple *data;
    int mu,nu,size; //行数 列数 非零元
}TSMatrix;

TSMatrix* MakeMatrix(int nu,int mu,int size)
{
    TSMatrix* Temp = (TSMatrix*)malloc(sizeof(TSMatrix));
    Temp->data = (Triple*)malloc((size + 1)* sizeof(Triple));

    Temp->nu = nu;
    Temp->mu = mu;
    Temp->size = size;
    return Temp;
}

int FastTran(TSMatrix M,TSMatrix* T)
{
    T->mu = M.nu;
    T->nu = M.mu;
    T->size = M.size;

    int* num = (int*)malloc(M.nu * sizeof(int));
    int* cpot = (int*)malloc(M.nu * sizeof(int));

    for(int col = 1; col <= M.nu; ++col)
    {
        num[col] = 0;
    }

    for(int t = 0; t < M.size; ++t)
    {
        ++num[M.data[t].j];
    }

    cpot[1] = 1;
    for(int col = 2; col <= M.nu; ++col)
    {
        cpot[col] = cpot[col - 1] + num[col - 1];
    }

    for(int p = 0; p < M.size; ++p)
    {
        int col = M.data[p].j;
        int q = cpot[col];
        T->data[q].i = M.data[p].j;
        T->data[q].j = M.data[p].i;
        T->data[q].e = M.data[p].e;
        ++cpot[col];
    }
    return 1;
}

void Test()
{
    int T[4][3] =
    {
        {1,2,3},
        {1,5,6},
        {2,8,9},
        {3,3,4}
    };

    TSMatrix *TT = MakeMatrix(3,8,4);
    TSMatrix M;
    M.mu = 3;
    M.nu = 8;
    M.size = 4;

    for(int i=0; i < M.size;++i)
    {
        //  scanf("%d%d%d", &M->data[i].i, &M.data[i].j, &M.data[i].e);
        M.data[i].i = T[i][0];
        M.data[i].j = T[i][1];
        M.data[i].e = T[i][2];
    }

    for(int k = 1; k <= TT->size; k++)
    {
        printf("%d %d %d\n",TT->data[k].i, TT->data[k].j, TT->data[k].e);
    }
}
int main()
{

    Test();
}

