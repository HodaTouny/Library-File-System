#ifndef LIBRARY_FILE_SYSTEM_PRIMARYINDEX_H
#define LIBRARY_FILE_SYSTEM_PRIMARYINDEX_H
#include <bits/stdc++.h>
#include "IndexHelper.h"
using namespace std;

class PrimaryIndex : public IndexHelper{
public:
    bool insertIntoIndex(vector<pair<string, int>>& FileIndex,string key,int offset);
    void deleteFromIndex(vector<pair<string, int>>& fileIndex,string targetString);
    vector<pair<string,int>>LoadIndexFile(string filename);
    void uploadIndexFile(vector<pair<string, int>>& FileIndex, const string& filename);

};


#endif //LIBRARY_FILE_SYSTEM_PRIMARYINDEX_H