#include <stdio.h>
#define Pcount 5
#define Scount 3
int Available[Scount];
int Max[Pcount][Scount];
int Allocation[Pcount][Scount];
int Need[Pcount][Scount];

Max Allocation Need Available
    P0 0 1 0 7 4 3 3 3 2 P1 2 0 0 1 2 2 P2 3 0 2 6 0 0 P3 2 1 1 0 1 1 P4 0 0 2 4 3 1

    void
    InitializeData();

void ShowData(int line);

void CalcMaxMatrix();

int Equals(int a[Scount], int b[Scount]);

int CheckSafe();

int CheckFinish(int Finish[Scount]);

void Add(int *a, int b[Scount]);

void Minus(int *a, int b[Scount]);

int Request(int P, int Request[Scount]);

void RequestShowMsg(int P, int R[Scount]);
int main()
{
    //???????????,????
    InitializeData();
    printf("=============??????=============\n");
    ShowData(0);
    //?????
    CheckSafe();

    //??P1 ????{1,0,2}
    int apply[Scount] = {1, 0, 2};
    RequestShowMsg(1, apply);

    //??P4 ????{1,0,2}
    int apply2[Scount] = {3, 3, 0};
    RequestShowMsg(4, apply2);

    //??P0 ????{0,2,0}
    int apply3[Scount] = {0, 2, 0};
    RequestShowMsg(0, apply3);

    return 0;
}

void InitializeData()
{

    Allocation[0][0] = 0, Allocation[0][1] = 1, Allocation[0][2] = 0;
    Allocation[1][0] = 2, Allocation[1][1] = 0, Allocation[1][2] = 0;
    Allocation[2][0] = 3, Allocation[2][1] = 0, Allocation[2][2] = 2;
    Allocation[3][0] = 2, Allocation[3][1] = 1, Allocation[3][2] = 1;
    Allocation[4][0] = 0, Allocation[4][1] = 0, Allocation[4][2] = 2;

    Need[0][0] = 7, Need[0][1] = 4, Need[0][2] = 3;
    Need[1][0] = 1, Need[1][1] = 2, Need[1][2] = 2;
    Need[2][0] = 6, Need[2][1] = 0, Need[2][2] = 0;
    Need[3][0] = 0, Need[3][1] = 1, Need[3][2] = 1;
    Need[4][0] = 4, Need[4][1] = 3, Need[4][2] = 1;

    Available[0] = 3, Available[1] = 3, Available[2] = 2;

    CalcMaxMatrix();
}

int Request(int P, int Request[Scount])
{
    printf("??P%d????%d %d %d:\n", P, Request[0], Request[1], Request[2]);

    if (!Equals(Request, Need[P]))
    {
        printf("??P%d,Request:%d %d %d > Need:%d %d %d ????,????????????!\n", P, Request[0], Request[1], Request[2], Need[P][0], Need[P][1], Need[P][2]);
        return 0;
    }
    //??2 ??????Request <= Available??????3
    if (!Equals(Request, Available))
    {
        printf("??P%d,Request:%d %d %d > Available:%d %d %d ????,??????,???????!\n", P, Request[0], Request[1], Request[2], Available[0], Available[1], Available[2]);
        return 0;
    }
    printf("??P%d,Request:%d %d %d <= Need:%d %d %d\n", P, Request[0], Request[1], Request[2], Need[P][0], Need[P][1], Need[P][2]);
    printf("??P%d,Request:%d %d %d <= Available:%d %d %d \n", P, Request[0], Request[1], Request[2], Available[0], Available[1], Available[2]);
    //??3 ????????P
    Minus(Available, Request);   //Available -= Request
    Add(Allocation[P], Request); //Allocation += Request
    Minus(Need[P], Request);     //Need -= Request
    //??4 ?????
    int Safestate = CheckSafe();
    if (Safestate)
    {
        return Safestate; //????????? ????
    }

    Add(Available, Request);       //Available += Request
    Minus(Allocation[P], Request); //Allocation -= Request
    Add(Need[P], Request);         //Need += Request
    return Safestate;
}
//???????????
void RequestShowMsg(int P, int R[Scount])
{
    //??P ????Request{1,0,2}
    printf("\n??????:P%d???? %d %d %d\n======================\n", P, R[0], R[1], R[2]);
    int State = Request(P, R);
    if (State)
    {
        printf("????????!\n");
        ShowData(0);
    }
    else
    {
        printf("????????!??P%d????\n", P);
    }
}
//?????,??????????
int CheckSafe()
{
    printf("???????:\n");
    //??1 ??????
    int Finish[Pcount] = {0}; //??????,?????False,???????True
    int Work[Scount] = {0};   //????
    Add(Work, Available);     //???Work = Available
    //??2 ????????????????
    //Finish[i] =  false;
    //Need[i,j] <= Work[j];
    for (int i = 0; i < Pcount; i++)
    {
        if (Finish[i])
            continue; //?????True???
        if (!Equals(Need[i], Work))
            continue; //Need[i,j] > Work[j] ????
        //??????,????3
        Add(Work, Allocation[i]); //Work += Allocation;
        Finish[i] = 1;            //Finish[i]=True;
        printf("P%d??,Work=%d %d %d,Finish=true,????\n", i, Work[0], Work[1], Work[2]);
        i = -1; //????2
    }
    //??4 ??Finish
    if (CheckFinish(Finish))
    {
        printf("????????:?Finish??true,?????????\n");
        return 1; //??True
    }
    printf("????????:?Finish??False,??????????\n");
    return 0; //??False
}
//????????True,???1 ????0
int CheckFinish(int Finish[Scount])
{
    for (int i = 0; i < Scount; i++)
    {
        if (Finish[i] == 0)
            return 0;
    }
    return 1;
}
//?????????
void ShowData(int line)
{
    printf("	Max	Alloca	Need	Available\n");
    for (int i = 0; i < Pcount; i++)
    {
        printf("p%d:\t", i);
        for (int j = 0; j < Scount; j++)
        {
            printf("%d ", Max[i][j]);
        }
        printf("\t");
        for (int j = 0; j < Scount; j++)
        {
            printf("%d ", Allocation[i][j]);
        }
        printf("\t");
        for (int j = 0; j < Scount; j++)
        {
            printf("%d ", Need[i][j]);
        }

        if (line == i)
        {
            printf("\t");
            for (int j = 0; j < Scount; j++)
            {
                printf("%d ", Available[j]);
            }
        }

        printf("\n");
    }
}
//????????
void CalcMaxMatrix()
{
    for (int i = 0; i < Pcount; i++)
    {
        for (int j = 0; j < Scount; j++)
        {
            Max[i][j] = Need[i][j] + Allocation[i][j];
        }
    }
}
//???? a = a+b
void Add(int *a, int b[Scount])
{
    for (int i = 0; i < Scount; i++)
    {
        a[i] = a[i] + b[i];
    }
}
//???? a = a-b
void Minus(int *a, int b[Scount])
{
    for (int i = 0; i < Scount; i++)
    {
        a[i] = a[i] - b[i];
    }
}
//????   a<=b ??1     a>b ??0
int Equals(int a[Scount], int b[Scount])
{
    for (int i = 0; i < Scount; i++)
    {
        if (a[i] > b[i])
            return 0;
    }
    return 1;
}