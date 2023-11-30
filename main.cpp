#include <bits/stdc++.h>
#include "IFilesSystem.h"
#include "IndexSystem.h"
using namespace std;

int main() {
    IFilesSystem x ;
    string data[3] = {"Hoda","Maya","Shahd"};
    x.addRecord(data,3,"Books.txt");
    x.addRecord(data,3,"Books.txt");
    x.deleteRecord(20,"Books.txt");
//     IndexSystem x;
//    vector<pair<string, int>> result = x.LoadIndexFile("BooksIndex.txt");
//    for (const auto& entry : result) {
//        cout << entry.first << ": " << entry.second << endl;
//    }




    return 0;
}
