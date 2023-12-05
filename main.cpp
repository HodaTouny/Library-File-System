#include <bits/stdc++.h>
#include "Interface.h"
#include "QueryProcessor.h"
using namespace std;

int main() {
    //put inside Books.txt header :  -1_______|0___   first line offset: 17
//    IFilesSystem x;
//    QueryProcessor y;
//    string query = "SELECT authorid,autHORname,address FROM Authors WHERE AuthorID = '00003'";
//    y.processQuery(query);
//    string maya[] ={"00001","Hoda","Hoda@gmail.com"};
//    string maya2[] ={"00002","nada","Nada2@yahoo.com"};
//    string maya3[] ={"00003","Nour","Nour@gmail.com"};
//    string shahd[] ={"A001","hoda's_book","00001"};
//    string shahd2[] ={"A002","nada's_book","00002"};
//    string shahd3[] ={"A003","nada's_book","00002"};
//
//    LinkedList<string >ll = x.readAvailFromFile("AVAILBook.txt");
//    x.addRecord(ll,"Books.txt",shahd);
//    x.addRecord(ll,"Books.txt",shahd2);
//    x.addRecord(ll,"Books.txt",shahd3);
//    x.addRecord(ll,"Authors.txt",maya);
//    x.addRecord(ll,"Authors.txt",maya2);
//    x.addRecord(ll,"Authors.txt",maya3);
    //  x.writeAvailToFile(ll,"AVAILBook.txt");
    //To make Index Equation: headerSize +  i[previous record size] + [i*2]+2
    //To update index: offset from header + previous record size + 2
//    LibraryInterface libraryInterface;
//    libraryInterface.menu();
//IndexSystem x;
    string fileName = "BookSKList.txt";
   // vector<pair<int, LinkedList<string>>> result = x.loadIndexList(fileName);

//    for (const auto& pair : result) {
//        cout << "Index: " << pair.first << " - Books: ";
//        pair.second.print();
//        cout << endl;
//    }
 IndexSystem x;
 x.updateLastValue("BookSKList.txt",7);
//IFilesSystem x;
//vector <string> vec=x.loadRecord(17,"BooksSKist.txt");
//for(int i=0;i < vec.size();i++){
//    cout<<vec[i]<<" ";
//}




    return 0;
}