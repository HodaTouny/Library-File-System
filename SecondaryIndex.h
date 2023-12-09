#ifndef LIBRARY_FILE_SYSTEM_SECONDARYINDEX_H
#define LIBRARY_FILE_SYSTEM_SECONDARYINDEX_H
#include <bits/stdc++.h>
#include "IndexHelper.h"
#include"QueryProcessor.h"
using namespace std;

class SecondaryIndex: public IndexHelper{
public:
    vector<pair<int, LinkedList<string>*>> loadLinkedListFile(string fileName);
    void processLinkedList(fstream& file, LinkedList<string>* linkedList, int thirdValue);
    vector<string> loadRecord(int offset,string fileName);
    bool addRecordToSecondaryIndex(vector<pair<string, int>>& fileIndex,vector<pair<int,
            LinkedList<string>*>>& secondaryIndex ,string data[],int &num);
    void writeToFile(const vector<pair<string, int>>& fileIndex,
                                      const vector<pair<int, LinkedList<string>*>>& secondaryIndex,
                                      const string& file1, const string& file2,int num);

    void writeToToFile(const string &filename, const vector<std::pair<int, std::string>> &data);
    void deleteFromSecondaryIndex(vector<pair<string, int>>& fileIndex,vector<pair<int, LinkedList<string>*>>& secondaryIndex,
                                  const string& targetString, const string& targetName);

    vector<pair<int, std::string>> readAndSortFile(const string &filename);
};


#endif //LIBRARY_FILE_SYSTEM_SECONDARYINDEX_H
