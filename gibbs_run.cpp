#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <math.h>
using namespace std;
#define item 496
#define cate 5
#define person 338
double P[cate];
double V[cate];
int T[item];
double Pi[person][cate*cate];
double A[person][cate*cate];
double namta[cate][cate];
int C[person][item];//score

//====================================================================================================================================
#include<fstream>
#include<cstring>
#include <gsl/config.h>
#include <iostream>
#include <math.h>
#include <time.h>
#include <gsl/gsl_sf.h>
#include <math.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_sf_gamma.h>

static void ran_dirichlet_small (const gsl_rng * r, const size_t K, const double alpha[], double theta[]);

void gsl_ran_dirichlet (const gsl_rng * r, const size_t K,const double alpha[], double theta[])
{
  size_t i;
  double norm = 0.0;
  for (i = 0; i < K; i++)
    {
      theta[i] = gsl_ran_gamma (r, alpha[i], 1.0);
    }
  for (i = 0; i < K; i++)
    {
      norm += theta[i];
    }
  if (norm < GSL_SQRT_DBL_MIN)
    {
      ran_dirichlet_small (r, K, alpha, theta);
      return;
    }
  for (i = 0; i < K; i++)
    {
      theta[i] /= norm;
    }
}


static void
ran_dirichlet_small (const gsl_rng * r, const size_t K,
                     const double alpha[], double theta[])
{
  size_t i;
  double norm = 0.0, umax = 0;
  for (i = 0; i < K; i++)
    {
      double u = log(gsl_rng_uniform_pos (r)) / alpha[i];
      theta[i] = u;

      if (u > umax || i == 0) {
        umax = u;
      }
    }

  for (i = 0; i < K; i++)
    {
      theta[i] = exp(theta[i] - umax);
    }
  for (i = 0; i < K; i++)
    {
      theta[i] = theta[i] * gsl_ran_gamma (r, alpha[i] + 1.0, 1.0);
    }
  for (i = 0; i < K; i++)
    {
      norm += theta[i];
    }
  for (i = 0; i < K; i++)
    {
      theta[i] /= norm;
    }
}


double gsl_ran_dirichlet_pdf (const size_t K,const double alpha[], const double theta[])
{
  return exp (gsl_ran_dirichlet_lnpdf (K, alpha, theta));
}

double gsl_ran_dirichlet_lnpdf (const size_t K, const double alpha[], const double theta[])
{
  size_t i;
  double log_p = 0.0;
  double sum_alpha = 0.0;

  for (i = 0; i < K; i++)
    {
      log_p += (alpha[i] - 1.0) * log (theta[i]);
    }
  for (i = 0; i < K; i++)
    {
      sum_alpha += alpha[i];
    }
  log_p += gsl_sf_lngamma (sum_alpha);
  for (i = 0; i < K; i++)
    {
      log_p -= gsl_sf_lngamma (alpha[i]);
    }

  return log_p;
}

//====================================================================================================================================



int t_update()
{
    double judge[item][cate];
    for (int i=0;i<item;i++)
    {
        for (int j=0;j<cate;j++)
        {
            double num=1.0;
            for (int k=0;k<person;k++)
              {
                  if (C[k][i]!=-1)
                      {num=num * (1+Pi[k][j*cate+C[k][i]]);
                  //cout<<C[k][i]<<endl;
                  }
              }
            judge[i][j]=P[j]*num;
        }
    }
    cout<<judge[421][0]<<endl;
    cout<<judge[421][1]<<endl;
    cout<<judge[421][2]<<endl;
    cout<<judge[421][3]<<endl;
    cout<<judge[421][4]<<endl;
    for (int i=0;i<item;i++)
    {
        double all=0.0;//============change to 0
        double before=0.0;
        double J[cate+1];
        J[0]=0;
        for (int j=0;j<cate;j++)
        {
            all+=judge[i][j];
        }
        //cout<<all<<endl;
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
    int times=10;
    double temp[times][cate];
    double num_set[times];
    int final,final_num;
    const gsl_rng_type *T2;
    gsl_rng * r;
    T2 = gsl_rng_ranlxs0;
    r = gsl_rng_alloc(T2);
    gsl_rng_default_seed = ((unsigned long)(time(NULL)));
    for (int i=0;i<times;i++)
    {
        //temp[times]=dir_sample();
        //======================================================================================
        double tt[cate];

        gsl_ran_dirichlet(r,cate,V,tt);
        for (int c=0;c<cate;c++)
        {
            temp[i][c]=tt[c];
            //cout<<tt[c]<<" ";
        }
        //cout<<endl;
    //===================================================================================
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
            num*=pow(temp[times][j],count+V[j]-1);
        }
        num_set[times]=num;
    }
    double all=1.0;//============change to 0
    double before=0.0;
    double J[times+1];
    J[0]=0;
    for (int j=0;j<times;j++)
    {
        all+=num_set[j];
    }
    for (int j=0;j<times;j++)
    {
        before+=num_set[j];
        J[j+1]=before/all;
    }
    double temp2=(rand()%30000)/30000.0;
    for (int j=0;j<times;j++)
    {
        if (temp2>J[j] && temp2<=J[j+1])
        {
                for (int x=0;x<cate;x++)
                   P[x]=temp[j][x];
        }
    }


}

int pi_update()
{
    for (int j=0;j<cate;j++)
    {
        for (int k=0;k<person;k++)
        {
            int time2=10;
            double temp[time2][cate];
            double num_set[time2];
            const gsl_rng_type *T2;
            gsl_rng * r;
            T2 = gsl_rng_ranlxs0;
            r = gsl_rng_alloc(T2);
            gsl_rng_default_seed = ((unsigned long)(time(NULL)));
            for (int i=0;i<time2;i++)
            {
                double tt[cate];
                double pi2a[cate];
                for (int y=0;y<cate;y++)
                {
                    pi2a[y]=A[k][j*cate+y];
                }
                gsl_ran_dirichlet(r,cate,pi2a,tt);
                for (int c=0;c<cate;c++)
                {
                    temp[i][c]=tt[c];
                    //cout<<tt[c]<<" ";
                }
                //cout<<endl;

                double num=1;
                for (int l=0;l<cate;l++)
                {
                    int count=0;
                    for (int z=0;z<item;z++)
                    {
                        if (T[z]==j && C[k][l]==l)
                        {
                            count++;
                        }
                    }
                    num*=pow(temp[time2][l],count+A[k][j*cate+l]-1);
                }
                num_set[time2]=num;
            }
            double all=0;//============change to 0
            double before=0.0;
            double J[time2+1];
            J[0]=0;
            for (int j=0;j<time2;j++)
            {
                all+=num_set[j];
            }
            for (int j=0;j<time2;j++)
            {
                before+=num_set[j];
                J[j+1]=before/all;
            }
            double temp2=(rand()%30000)/30000.0;
            for (int j=0;j<time2;j++)
            {
                if (temp2>J[j] && temp2<=J[j+1])
                {
                    for (int x=0;x<cate;x++)
                        Pi[k][j*cate+x]=temp[j][x];
                }
            }
        }
    }

}


double exp_sample(double lambda)
{
    double pV = 0.0;

    while(true)
    {
        pV = (double)rand()/(double)RAND_MAX;
        if (pV != 1)
        {
            break;
        }
    }
    pV = (-1.0/lambda)*log(1-pV);
    return pV;
}

int a_update()
{
    for (int j=0;j<cate;j++)
    {
        for (int k=0;k<person;k++)
        {
            int time2=10;
            int count=0;

            double temp[time2][cate];
            double num_set[time2];
            //for (int i=0;i<cate;i++)
               //temp[i]=A[k][j*cate+i];
            for (int i=0;i<time2;i++)
            {
                double temp_test[cate];
                for (int z=0;z<cate;z++)
                     temp[i][z]=exp_sample(1/(namta[j][z]));

            }

                for (int i=0;i<time2;i++)
                {
                    double num=1;
                    double summ=0;
                    for (int xx=0;xx<cate;xx++)
                       summ+=temp[i][xx];

                    for (int l=0;l<cate;l++)
                        {

                            num*=(gsl_sf_gamma(summ)/(gsl_sf_gamma(temp[i][l]+0.001)))*pow(Pi[k][j*cate+l],temp[i][l])*exp((-temp[i][l])/(namta[j][l]));
                        }
                    num_set[time2]=num;
                }
                double all=0;//============change to 0
                double before=0.0;
                double J[time2+1];
                J[0]=0;
                for (int j=0;j<time2;j++)
                {
                    all+=num_set[j];
                }
                for (int j=0;j<time2;j++)
                {
                    before+=num_set[j];
                    J[j+1]=before/all;
                }
                double temp2=(rand()%30000)/30000.0;
                for (int j=0;j<time2;j++)
                {
                    if (temp2>J[j] && temp2<=J[j+1])
                    {
                        for (int m=0;m<cate;m++)
                        {
                            A[k][j*cate+m]=temp[j][m];
                        }
                        break;
                    }
                }
        }

    }
}
//===================================================================================================================initial
int c_initial()
{
    for (int i=0;i<person;i++)
    {
        for (int j=0;j<item;j++)
        {
            C[i][j]=-1;
        }
    }
    ifstream in("labels_trans.txt");
    char buffer[20];
    int count=-1;
    int i=0;
    while(!in.eof())
    {
        in.getline(buffer,20);
        int a,b,c;
        sscanf(buffer,"%d %d %d",&a,&b,&c);
        C[a][b]=c;

    }
    cout<<"hahaha"<<endl;
    in.close();
}

int v_initial()
{
    V[0]=28.5978;
    V[1]=27.0338;
    V[2]=32.0413;
    V[3]=10.6662;
    V[4]=1.66088;
}

int namta_initial()
{
    for (int i=0;i<cate;i++)
    {
        for (int j=0;j<cate;j++)
        {
            if (i==j)
             namta[i][j]=10;
            if (i!=j)
             namta[i][j]=1;
        }
    };
}

int a_initial()
{
    srand((unsigned)time(0));
    for (int j=0;j<cate;j++)
    {
        for (int k=0;k<person;k++)
        {
           for (int z=0;z<cate;z++)
              {
                  A[k][j*cate+z]=exp_sample(1/(namta[j][z]));
              }
        }
    }


        for (int j=0;j<cate;j++)
        {
            for (int k=0;k<cate;k++)
            {
                cout<<A[0][j*cate+k]<<" ";
            }
            cout<<endl;
        }


}

int p_initial()
{
    const gsl_rng_type *T2;
    gsl_rng * r;
    T2 = gsl_rng_ranlxs0;
    r = gsl_rng_alloc(T2);
    gsl_rng_default_seed = ((unsigned long)(time(NULL)));
    double tt[cate];
    gsl_ran_dirichlet(r,cate,V,P);
    //cout<<P[0]<<" "<<P[1]<<" "<<P[2]<<" "<<P[3]<<" "<<P[4]<<endl;
}

int pi_initial()
{
    for (int k=0;k<person;k++)
    {
        for (int i=0;i<cate;i++)
        {
            const gsl_rng_type *T2;
            gsl_rng * r;
            T2 = gsl_rng_ranlxs0;
            r = gsl_rng_alloc(T2);
            gsl_rng_default_seed = ((unsigned long)(time(NULL)));

                double tt[cate];
                double pi2a[cate];
                for (int y=0;y<cate;y++)
                {
                    pi2a[y]=A[k][i*cate+y];
                }
                gsl_ran_dirichlet(r,cate,pi2a,tt);
                for (int c=0;c<cate;c++)
                {
                    Pi[k][i*cate+c]=tt[c];
                    //cout<<tt[c]<<endl;
                }

          }
      }
      cout<<"===================="<<endl;
      for (int i=0;i<1;i++)
    {
        for (int j=0;j<cate;j++)
        {
            for (int k=0;k<cate;k++)
            {
                cout<<Pi[i][j*cate+k]<<" ";
            }
            cout<<endl;
        }
    }

}
//===================================================================================================================================================

int main()
{
    v_initial();
    c_initial();
    namta_initial();
    p_initial();
    a_initial();
    pi_initial();


    //cout<<Pi[0][200]<<endl;
    srand((unsigned)time(0));
    //initial();
    for (int i=0;i<20;i++)
    {
        cout<<i<<endl;
        t_update();
        p_update();
        pi_update();
        a_update();
    }
    ofstream out("result.txt");
    {
        for (int z=0;z<item;z++)
            out<<z<<" "<<T[z]<<endl;
    }
    out.close();
    return 0;
}
