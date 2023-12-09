#ifndef LIBRARY_FILE_SYSTEM_FILESHELPER_H
#define LIBRARY_FILE_SYSTEM_FILESHELPER_H
#include <bits/stdc++.h>
#include "LinkedList.h"
using namespace std;

class FilesHelper{
protected:
public:
    void removeUnderscores(string& str);
    string to_string(int value);
    string concat(string str1,string str2);
    int extractFirstValueFromFile(string filename);
    int extractSecondValueFromFile(string filename);
    string formatNumber(int value, int digits);
    void updateOffset(int offset,string fileName);
    void updateHeader(int number, string fileName);
    vector<int> extractSize(LinkedList<string>& availList);
    int findRecordLength(string data[], int dataSize);
    int findBestFit(LinkedList<string>&AVAIL,int recordLength);
    string extractValueBetweenBars( string input);
    string updateNextNodeData(string x, string secondString);
    int appendToFile(const string data[], int dataSize,  string fileName);
    void insertRecord(int offset, const string data[], int dataSize,  string fileName, int oldSize);

};

#endif //LIBRARY_FILE_SYSTEM_FILESHELPER_H
