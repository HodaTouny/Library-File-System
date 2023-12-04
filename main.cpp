#include <bits/stdc++.h>
#include "Interface.h"
using namespace std;

int main() {
    //put inside Books.txt header :  -1_______|0___   first line offset: 17
    IFilesSystem x;
    string maya[] ={"00001","Hoda","Hoda@gmail.com"};
    string maya2[] ={"00002","nada","Nada2@yahoo.com"};
    string maya3[] ={"00003","Nour","Nour@gmail.com"};
    LinkedList<string >ll = x.readAvailFromFile("AVAILBook.txt");
    x.addRecord(ll,"Books.txt",maya);
    x.addRecord(ll,"Books.txt",maya2);
    x.addRecord(ll,"Books.txt",maya3);
    x.writeAvailToFile(ll,"AVAILBook.txt");
    //To make Index Equation: headerSize +  i[previous record size] + [i*2]+2
    //To update index: offset from header + previous record size + 2

    return 0;
}
