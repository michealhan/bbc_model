#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;

int main()
{

    ofstream out("cate_id.txt");
    char buffer[800];
    string a,b,c;
    string person[1500];
    int count=0;
    //while(!in.eof())
    int i=0;
    out<<"ID "<<" cate"<<endl;
    out<<"0 "<<" G"<<endl;
    out<<"1 "<<" P"<<endl;
    out<<"2 "<<" R"<<endl;
    out<<"3 "<<" X"<<endl;
    out<<"4 "<<" B"<<endl;


    out.close();
    return 0;
}
