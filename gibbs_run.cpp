#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <math.h>
using namespace std;
#define item 1000
#define cate 100
#define person 100
double P[cate];
int V[cate];
int T[item];
double Pi[person][cate*cate];
int C[person][item];//score

int t_update()
{
    int judge[item][cate];
    for (int i=0;i<item;i++)
    {
        for (int j=0;j<cate;j++)
        {
            double num=1.0;
            for (int k=0;k<person;k++)
              num = num * Pi[k][j*cate+C[k][i]];
            judge[i][j]=P[j]*num;
        }
    }
    for (int i=0;i<item;i++)
    {
        double all=1.0;//============change to 0
        double before=0.0;
        double J[cate+1];
        J[0]=0;
        for (int j=0;j<cate;j++)
        {
            all+=judge[i][j];
        }
        for (int j=0;j<cate;j++)
        {
            before+=judge[i][j];
            J[j+1]=before/all;
        }
        double temp=(rand()%30000)/30000.0;
        for (int j=0;j<cate;j++)
        {
            if (temp>J[j] && temp<=J[j+1])
            {
                T[i]=j;
            }
        }
    }
}

int p_update()
{
    /*int time=10;
    double temp[time][cate];
    int final,final_num;
    for (int i=0;i<time;i++)
    {
        temp[time]=dir_sample();
        double num=1;
        for (int j=0;j<cate;j++)
        {
            int count=0;
            for (int k=0;k<item;k++)
            {
                if (T[k]==j)
                {
                    count++;
                }
            }
            num*=pow(temp[time][j],count+V[j]-1);
        }
        if (final<num)
        {
            final=num;
            final_num=time;
        }
    }
    for (int i=0;i<cate;i++)
    {
        P[i]=temp[final_num][i];
    }*/

}

int pi_update()
{
    ;
}

int a_update()
{
    ;
}

int main()
{
    cout<<Pi[0][200]<<endl;
    srand((unsigned)time(0));
    //initial();
    for (int i=0;i<10;i++)
    {
        //cout<<i<<endl;
        t_update();
        p_update();
        pi_update();
        a_update();
    }
    return 0;
}
