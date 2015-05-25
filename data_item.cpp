#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;

int main()
{
    ifstream in("labels.txt");
    ofstream out("item_id.txt");
    char buffer[800];
    int tru[5]={0,0,0,0,0};
    string a,b,c;
    string person[1500];
    int count=-1;
    string web="";
    //while(!in.eof())
    int i=0;
    out<<"ID "<<"          item               "<<endl;
    while(!in.eof())
    {
        in.getline(buffer,800);
        string aa="";
        string bb="";
        int j=0;
        int k=0;
        for (int l=0;l<800;l++)
        {
            if (buffer[l]=='\t')
               j++;
            if (buffer[l]!='\t' && j==1)
               aa+=buffer[l];
            if (buffer[l]!='\t' && j==2 && k==0)
            {
                bb+=buffer[l];
                k=1;
            }

        }

        if (aa!=web)
        {
            if (count!=-1)
                out<<count<<" "<<web<<"       "<<tru[0]<<"(G) "<<tru[1]<<"(P) "<<tru[2]<<"(R) "<<tru[3]<<"(X) "<<tru[4]<<"(B)"<<endl;
            count++;
            web=aa;
            for (int i=0;i<5;i++)
                tru[i]=0;
        }
        if (bb=="G")
           tru[0]++;
        if (bb=="P")
           tru[1]++;
        if (bb=="R")
            tru[2]++;
        if (bb=="X")
           tru[3]++;
        if (bb=="B")
           tru[4]++;

    }
    out<<count<<" "<<web<<"       "<<tru[0]<<"(G) "<<tru[1]<<"(P) "<<tru[2]<<"(R) "<<tru[3]<<"(X) "<<tru[4]<<"(B)"<<endl;
    cout<<"item"<<endl;
    in.close();
    out.close();
    return 0;
}
