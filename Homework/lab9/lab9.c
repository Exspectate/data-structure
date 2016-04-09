#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef struct stack
{
    char Ele[100];
    int size;
}Stack;

Stack* MakeStack()
{
    Stack* Temp = (Stack*)malloc(sizeof(Stack));
    for(int k = 0; k < 100; k++)
    {
        Temp->Ele[k] = 'E';
    }
    Temp->size = 0;
    return Temp;
}

void Pop(Stack* S,char* c)
{
    if(c == NULL)
    {
        S->size--;
        return;
    }
    if(S == NULL || S->size == 0)
    {
        return;
    }
    *c = S->Ele[S->size - 1];
    S->size--;
}

void Add(Stack* S,char c)
{
    if(S->size < 100)
    {
        S->Ele[S->size] = c;
        S->size++;
    }
    else
    {
        printf("ERROR");
        return;
    }
}

char GetTop(Stack *S)
{
    return S->Ele[S->size - 1];
}

int Kind(char c)
{

    switch(c)
    {
        case '#':
        {
            return 0;
            break;
        }
        case '+':
        {
            return 1;
            break;
        }
        case '-':
        {
            return 1;
            break;
        }
        case '*':
        {
            return 2;
            break;
        }
        case '/':
        {
            return 2;
            break;
        }
        case '(':
        {
            return 3;
            break;
        }
        case ')':
        {
            return 3;
            break;
        }
        default:
        {
            printf("ERROR!\n");
            break;
        }
    }
    return -1;
}


void NifixToPostfix(char* Nifix,char* Postfix) //中->后
{

    Stack* Sym = MakeStack();

    Add(Sym,'#');

    for(int k = 0; k < 100; k++)
    {
        char c = Nifix[k];

        if('0' <= c && c <= '9')
        {
            char* cc = (char*)malloc(2*sizeof(char));
            cc[0] = c;
            cc[1] = '\0';
            strcat(Postfix,cc);
        }
        else if(c == '\0')
        {
            while(Sym->size > 0)
            {
                if(GetTop(Sym) != '(')
                {
                    char *temp = (char*)malloc(2 * sizeof(char));
                    Pop(Sym,temp);
                    temp[1] = '\0';
                    strcat(Postfix,temp);
                }
                else
                {
                    Pop(Sym,NULL);
                }
            }
            Postfix[strlen(Postfix) - 1] = '\0';
            return;
        }
        else if(c == ' ')
        {
            ;
        }
        else
        {
            int a = Kind(c);
            int b = Kind(GetTop(Sym));

            if(c == ')')  //是右括号
            {
                while(Sym->size > 0)
                {
                    if(GetTop(Sym) != '(')
                    {
                        char *temp = (char *) malloc(2 * sizeof(char));
                        Pop(Sym, temp);
                        temp[1] = '\0';
                        strcat(Postfix, temp);
                    }
                    else
                    {
                        break;
                    }
                }
                Pop(Sym,NULL);
            }

            else
            {
                if(GetTop(Sym) == '(' && c != ')')
                {
                    Add(Sym,c);
                }
                else
                {
                    while(Kind(GetTop(Sym)) >= Kind(c) && Sym->size != 0)
                    {
                        if(GetTop(Sym) == '(')
                            break;
                        char *temp = (char*)malloc(2 * sizeof(char));
                        Pop(Sym,temp);
                        temp[1] = '\0';
                        strcat(Postfix,temp);
                    }
                    Add(Sym,c);
                }
            }
        }
    }
}

int ComputePostfix(char* Postfix)
{
    Stack* Num = MakeStack();
    for(int k = 0; k < strlen(Postfix); k++)
    {
        char c = Postfix[k];
        if('0' <= c && c <= '9')
        {
            Add(Num,c);
        }
        else
        {
            char *a = (char*)malloc(sizeof(char));
            char *b = (char*)malloc(sizeof(char));
            Pop(Num,a);
            Pop(Num,b);
            int m = *a - '0';
            int n = *b - '0';
            switch(c)
            {
                case '+':
                {
                    int w = m + n;
                    char* Temp = (char*)malloc(sizeof(char));
                    sprintf(Temp,"%d",w);
                    Add(Num,*Temp);
                    break;
                }
                case '-':
                {
                    int w = n - m;
                    char* Temp = (char*)malloc(sizeof(char));
                    sprintf(Temp,"%d",w);
                    Add(Num,*Temp);
                    break;
                }
                case '*':
                {
                    int w = m * n;
                    char* Temp = (char*)malloc(sizeof(char));
                    sprintf(Temp,"%d",w);
                    Add(Num,*Temp);
                    break;
                }
                case '/':
                {
                    int w = n / m;
                    char* Temp = (char*)malloc(sizeof(char));
                    sprintf(Temp,"%d",w);
                    Add(Num,*Temp);
                    break;
                }
                default:
                {
                    printf("ERROR\n");
                }
            }
        }
    }
    return (int)Num->Ele[0];
}

void strrev(char* S)
{
    for(int k = 0; k <= strlen(S) / 2; k++)
    {
        char c = S[k];
        S[k] = S[strlen(S) - k - 1];
        S[strlen(S) - k - 1] = c;
    }
    return;
}

void NifixToPrefix(char* Nifix,char* Prefix) //中->前
{

    Stack* Sym = MakeStack();

    Add(Sym,'#');
    strrev(Nifix);
    for(int k = 0; k <= strlen(Nifix); k++)
    {
        char c = Nifix[k];

        if('0' <= c && c <= '9')
        {
            char* cc = (char*)malloc(2*sizeof(char));
            cc[0] = c;
            cc[1] = '\0';
            strcat(Prefix,cc);
        }
        else if(c == '\0')
        {
            while(Sym->size > 0)
            {
                if(GetTop(Sym) != '(')
                {
                    char *temp = (char*)malloc(2 * sizeof(char));
                    Pop(Sym,temp);
                    temp[1] = '\0';
                    strcat(Prefix,temp);
                }
                else
                {
                    Pop(Sym,NULL);
                }
            }
            Prefix[strlen(Prefix) - 1] = '\0';
            strrev(Prefix);
            return;
        }
        else if(c == ' ')
        {
            ;
        }
        else//算符
        {
            int a = Kind(c);
            int b = Kind(GetTop(Sym));

            if(c == '(')  //是左括号
            {
                while(Sym->size > 0)
                {
                    if(GetTop(Sym) != ')')
                    {
                        char *temp = (char *) malloc(2 * sizeof(char));
                        Pop(Sym, temp);
                        temp[1] = '\0';
                        strcat(Prefix, temp);
                    }
                    else
                    {
                        break;
                    }
                }
                Pop(Sym,NULL);
            }

            else //其他算符
            {
                if(GetTop(Sym) == ')' && c != '(')
                {
                    Add(Sym,c);
                }
                else    //不在括号内
                {
                    while(Kind(GetTop(Sym)) > Kind(c) && Sym->size != 0)
                    {
                        if(GetTop(Sym) == ')')
                            break;
                        char *temp = (char*)malloc(2 * sizeof(char));
                        Pop(Sym,temp);
                        temp[1] = '\0';
                        strcat(Prefix,temp);
                    }
                    Add(Sym,c);
                }
            }
        }
    }
}

int ComputePrefix(char* Prefix)
{
    Stack* Num = MakeStack();
    for(int k = strlen(Prefix) - 1; k >= 0; k--)
    {
        char c = Prefix[k];
        if('0' <= c && c <= '9')
        {
            Add(Num,c);
        }
        else
        {
            char *a = (char*)malloc(sizeof(char));
            char *b = (char*)malloc(sizeof(char));
            Pop(Num,a);
            Pop(Num,b);
            int m = *a - '0';
            int n = *b - '0';
            switch(c)
            {
                case '+':
                {
                    int w = m + n;
                    char* Temp = (char*)malloc(sizeof(char));
                    sprintf(Temp,"%d",w);
                    Add(Num,*Temp);
                    break;
                }
                case '-':
                {
                    int w = m - n;
                    char* Temp = (char*)malloc(sizeof(char));
                    sprintf(Temp,"%d",w);
                    Add(Num,*Temp);
                    break;
                }
                case '*':
                {
                    int w = m * n;
                    char* Temp = (char*)malloc(sizeof(char));
                    sprintf(Temp,"%d",w);
                    Add(Num,*Temp);
                    break;
                }
                case '/':
                {
                    int w = m / n;
                    char* Temp = (char*)malloc(sizeof(char));
                    sprintf(Temp,"%d",w);
                    Add(Num,*Temp);
                    break;
                }
                default:
                {
                    printf("ERROR\n");
                }
            }
        }
    }
    return (int)Num->Ele[0];
}
void Test()
{
	printf("请输入四则表达式\n");
	char* Temp = (char*)malloc(100 * sizeof(char));
	char* Res = (char*)malloc(100 * sizeof(char));
	scanf("%s",Temp);

	printf("请选择\n1.转为后缀并计算\n2.转为前缀并计算\n");
	int choose;
	scanf("%d",&choose);

	if(choose == 1)
	{
		NifixToPostfix(Temp,Res);
		printf("%s\n",Res);
		int a = ComputePostfix(Res);
		printf("%c\n",a);

	}
	else if(choose == 2)
	{
		NifixToPrefix(Temp,Res);
		int a = ComputePrefix(Res);
		printf("%s\n",Res);
		printf("%c\n",a);
	}
	else
	{
		printf("ERROR!\n");
	}

}
int main()
{
	Test();
	/*
    char* P = (char*)malloc(100 * sizeof(char));
    char* N = (char*)malloc(100 * sizeof(char));
    //strcpy(N,"1+2*3+(4*5+6)*7");
    strcpy(N,"1*(2+1*4)/5*4");
    //strcpy(N,"2-1");
    //NifixToPostfix(N,P);
    NifixToPrefix(N,P);
    printf("%s\n",P);
    int a = ComputePrefix(P);
    printf("%c\n",a);
	*/
    return 0;
}
