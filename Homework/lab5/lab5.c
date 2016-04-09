#include "stdio.h"
#include "stdlib.h"
typedef struct Fibonacci
{
    int* Arr;
    int size;
    int front;
    int rear;
    int MAXSIZE;
}Fib;

Fib* MakeFib()
{
    Fib* Temp = (Fib*)malloc(sizeof(Fib));
    Temp->size = 0;
    Temp->Arr = (int*)malloc(4 * sizeof(int));
    Temp->front = 0;
    Temp->rear = 0;
    Temp->MAXSIZE = 4;
    return Temp;
}

int QueueLength(Fib Q)
{
    return (Q.rear - Q.front + Q.MAXSIZE) % Q.MAXSIZE;
}

void InQueue(int a,Fib* Q)
{
    if(Q->size == Q->MAXSIZE)
    {
        printf("队满！");
        return;
    }

    Q->size++;
    Q->Arr[Q->rear] = a;
    Q->rear = (Q->rear + 1) % Q->MAXSIZE;

    return;
}

int DeQueue(Fib* Q)
{
    int Temp;

    if(Q->size == 0)
    {
        printf("队空！");
        return 0;
    }

    Temp = Q->Arr[Q->front];
    Q->size--;
    Q->front = (Q->front + 1) % Q->MAXSIZE;
    return Temp;
}

int Sum(Fib *Q)
{
    int sum = 0;
    for(int k = 0; k < Q->MAXSIZE; k++)

    {
        sum += Q->Arr[k];
    }
    return sum;
}

void Test()
{
    Fib* Q = MakeFib();
    InQueue(0,Q);
    InQueue(0,Q);
    InQueue(0,Q);
    InQueue(1,Q);
    int sum = 0;
    while(sum < 2000)
    {
        printf("%d ",sum);
        sum = Sum(Q);
        DeQueue(Q);
        InQueue(sum,Q);
    }
}

int main()
{
    Test();
    return 0;
}


