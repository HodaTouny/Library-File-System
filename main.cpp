#include <bits/stdc++.h>
#include "IFilesSystem.h"
#include "IndexSystem.h"
using namespace std;
IFilesSystem x ;


int main() {
    LinkedList<string > kk = x.AvailCreator("Books.txt");
    string maya[] = {"LLLLlee","ta","smLLL"};
    string maya2[] = {"kem","ta","sm"};
    x.addRecord(kk,"Books.txt",maya2,3);
    x.addRecord(kk,"Books.txt",maya,3);


    //To make Index Equation: headerSize +  i[previous record size] + [i*2]+2
    //To update index: offset from header + previous record size + 2

    return 0;
}
