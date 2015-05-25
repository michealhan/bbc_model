#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;

int main()
{
    ifstream in("labels.txt");
    ofstream out("labels_trans.txt");
    char buffer[800];
    string a,b,c;
    string person[1000];
    int count_p=0;
    int count=-1;
    string web="";
    //while(!in.eof())
    while(!in.eof())
    {
        in.getline(buffer,800);
        string aa="";
        string bb="";
        string cc="";
        int kk=0;
        int kkk=0;
        for (int j=0;j<800;j++)
        {

            if (buffer[j]=='\t')
               kk++;
            if (buffer[j]!='\t' && kk==0)
               aa+=buffer[j];
            if (buffer[j]!='\t' && kk==1)
               bb+=buffer[j];
            if (buffer[j]!='\t' && kk==2 && kkk==0)
               {
                   cc+=buffer[j];
                   kkk=1;
                   break;
               }
        }
        int jj=0;
        for (int m=0;m<count_p;m++)
           {
               if (aa==person[m])
                  {
                      out<<m<<" ";
                      jj=1;
                      break;
                  }
        }
       if (jj==0)
       {
           person[count_p]=aa;
           out<<count_p<<" ";
           count_p++;
       }

        if (bb!=web)
           {
               count++;
               web=bb;
           }


        out<<count<<" ";

        if (cc=="G")
          out<<0<<endl;
        if (cc=="P")
          out<<1<<endl;
        if (cc=="R")
          out<<2<<endl;
        if (cc=="X")
          out<<3<<endl;
        if (cc=="B")
          out<<4<<endl;

    }
    cout<<"1"<<endl;
    in.close();
    out.close();
    return 0;
}
