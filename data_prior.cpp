#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;

int main()
{

    ifstream in("labels_trans.txt");
    ofstream out("prior.txt");
    char buffer[20];
    int count=-1;
    int i=0;
    int aa[5]={0,0,0,0,0};
    while(!in.eof())
    {
        in.getline(buffer,20);
        int a,b,c;
        sscanf(buffer,"%d %d %d",&a,&b,&c);
        aa[c]++;
    }
    int all=0;
    for (int k=0;k<5;k++)
       {
           all+=aa[k];
       }
       cout<<all<<endl;
    for (int j=0;j<5;j++)
       out<<j<<" "<<((aa[j]*100.0)/all)<<endl;
    in.close();
    out.close();
}
