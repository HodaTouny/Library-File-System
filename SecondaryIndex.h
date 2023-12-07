#ifndef LIBRARY_FILE_SYSTEM_SECONDARYINDEX_H
#define LIBRARY_FILE_SYSTEM_SECONDARYINDEX_H
#include <bits/stdc++.h>
#include "IndexHelper.h"
using namespace std;

class SecondaryIndex: public IndexHelper{
    void deleteFromSecondaryIndex(vector<pair<string, string>>& fileIndex,vector<pair<string, LinkedList<string>*>>& secondaryIndex,const string& targetString, const string& targetName);
    vector<pair<int, LinkedList<string>*>> loadLinkedListFile(string fileName);
    void processLinkedList(fstream& file, LinkedList<string>* linkedList, int thirdValue);
    vector<string> loadRecord(int offset,string fileName);
    void addRecordToSecondaryIndex(string data[], string SKfile, string SKlistfile, vector<pair<string, int>>& myfile);

};


#endif //LIBRARY_FILE_SYSTEM_SECONDARYINDEX_H
