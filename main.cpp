#include <bits/stdc++.h>
#include "IFilesSystem.h"
#include "IndexSystem.h"
using namespace std;

int main() {
    IFilesSystem x ;
    x.updateHeader(100,"Books.txt");
    x.updateOffset(80,"Books.txt");


    //To make Index Equation: headerSize +  i[previous record size] + [i*2]+2
    //To update index: offset from header + previous record size + 2

    return 0;
}
