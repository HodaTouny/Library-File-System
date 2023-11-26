#include <bits/stdc++.h>
#include "IFilesSystem.cpp"
using namespace std;

int main() {
    IFilesSystem x ;
    string data[3] = {"Hoda","Maya","Shahd"};
    x.addRecord(data,3,"Books.txt");
    x.addRecord(data,3,"Books.txt");
    string m = x.loadRecord(20,"Books.txt");
    cout<<m<<"\n";

        return 0;
}
