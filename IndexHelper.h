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
protected:
    void sortPairs(vector<pair<string, int>> &FileIndex);
    string extractHeader(string fileName);
    void updateLastValue(string fileName, int offset);
    void writeHeader(string fileName);
    int calculateFixedOffset(int rnn);
    string writer(int integer,string number);
    void removeUnderscores(string& str);
    vector<string> parseString(const string& inputString);
    int getValueAfterLastDelimiter(const string& filePath, int offset);
    int calculateVariableLengthOffset(int previousRecordSize,int LastOffset);

};


#endif //LIBRARY_FILE_SYSTEM_INDEXHELPER_H