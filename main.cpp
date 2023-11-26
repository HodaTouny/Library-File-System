#include <bits/stdc++.h>
#include "IFilesSystem.cpp"
#include "IFilesSystem.h"
using namespace std;

int main() {
    IFilesSystem x ;
    string data[3] = {"Hoda","Maya","Shahd"};
    x.addRecord(data,3,"Books.txt");
        return 0;
}
