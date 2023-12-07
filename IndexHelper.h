#ifndef LIBRARY_FILE_SYSTEM_INDEXHELPER_H
#define LIBRARY_FILE_SYSTEM_INDEXHELPER_H
#include <bits/stdc++.h>
#include "AVAILSystem.h"
#include "LinkedList.h"
using namespace std;
class  IndexHelper {
private:
    AVAILSystem fileSystem;
protected:
    void sortPairs(vector<pair<string, int>> &FileIndex);
    string extractHeader(string fileName);
    void updateLastValue(string fileName, int offset);
    void writeHeader(string fileName);
    int calculateFixedOffset(int rnn);
    string writer(int integer,string number);
    void removeUnderscores(string& str);
    vector<string> parseString(const string& inputString);

};


#endif //LIBRARY_FILE_SYSTEM_INDEXHELPER_H