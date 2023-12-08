#ifndef LIBRARY_FILE_SYSTEM_SECONDARYINDEX_H
#define LIBRARY_FILE_SYSTEM_SECONDARYINDEX_H
#include <bits/stdc++.h>
#include "IndexHelper.h"
using namespace std;

class SecondaryIndex: public IndexHelper{
public:
    void deleteFromSecondaryIndex(vector<pair<string, string>>& fileIndex,vector<pair<string, LinkedList<string>*>>& secondaryIndex,const string& targetString, const string& targetName);
    vector<pair<int, LinkedList<string>*>> loadLinkedListFile(string fileName);
    void processLinkedList(fstream& file, LinkedList<string>* linkedList, int thirdValue);
    vector<string> loadRecord(int offset,string fileName);
   bool addRecordToSecondaryIndex(vector<pair<string, int>>& fileIndex,vector<pair<int,
            LinkedList<string>*>>& secondaryIndex ,string data[],int &num);
    void writeToFile(const vector<pair<string, int>>& fileIndex,
                     const vector<pair<int, LinkedList<string>*>>& secondaryIndex,
                     const string& file1, const string& file2) ;
};


#endif //LIBRARY_FILE_SYSTEM_SECONDARYINDEX_H
