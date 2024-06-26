#ifndef LIBRARY_FILE_SYSTEM_INDEXHELPER_H
#define LIBRARY_FILE_SYSTEM_INDEXHELPER_H
#include <bits/stdc++.h>
#include "AVAILSystem.h"
#include "LinkedList.h"
#include "EntityFiles.h"
using namespace std;

class  IndexHelper {
protected:
    EntityFiles fileSystem;
    FilesHelper fileHelper;
public:
    void sortPairs(vector<pair<string, int>> &FileIndex);
    void updateLastValue(string fileName, int offset);
    void writeHeader(string fileName,int num);
    int calculateFixedOffset(int rnn);
    string writer(int integer,string number);
    void removeUnderscores(string& str);
    vector<string> parseString(const string& inputString);
    int getValueAfterLastDelimiter(const string& filePath, int offset);
    int calculateVariableLengthOffset(int previousRecordSize,int LastOffset);
    bool binarySearch(vector<pair<string, int>> &fileIndex, string target);
    string extractHeader(string fileName);
    int binarySearchInt(vector<pair<string, int>> &vec, string key);
    void sort_Pairs(vector<std::pair<int, LinkedList<string> *>> &FileIndex);
};


#endif //LIBRARY_FILE_SYSTEM_INDEXHELPER_H