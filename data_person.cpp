#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;

int main()
{
    ifstream in("labels.txt");
    ofstream out("person_id.txt");
    char buffer[800];
    string a,b,c;
    string person[1500];
    int count=0;
    //while(!in.eof())
    int i=0;
    out<<"ID "<<" person"<<endl;
    while(!in.eof())
    {
        in.getline(buffer,800);
        string aa="";
        for (int j=0;j<30;j++)
        {

            if (buffer[j]=='\t')
               break;
            if (buffer[j]!='\t')
               aa+=buffer[j];
        }
        int judge=0;
        for (int i=0;i<count;i++)
        {
            if (person[i]==aa)
            {
                judge=1;
            }
        }
        if (judge==0)
        {
            out<<count<<" "<<aa<<endl;
            cout<<count<<" "<<aa<<endl;
            person[count]=aa;
            count++;
        }
    }
    cout<<"1"<<endl;
    in.close();
    out.close();
    return 0;
}
