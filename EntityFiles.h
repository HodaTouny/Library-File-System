#ifndef LIBRARY_FILE_SYSTEM_ENTITYFILES_H
#define LIBRARY_FILE_SYSTEM_ENTITYFILES_H
#include "bits/stdc++.h"
#include "LinkedList.h"
#include "FilesHelper.h"

using namespace std;

class EntityFiles : public  FilesHelper{
public:
    vector<string> loadRecord(int offset, string fileName);
    string deleteRecord(int offset, string fileName);
    void addRecord(LinkedList<string>&AVAIL,string fileName,string data[],int dataSize=3);



    void updateRecord(int offset, string newValue, string fileName, LinkedList<string> &availList,
                          vector<pair<string, int>> &fileIndex,string filename2);
};


#endif //LIBRARY_FILE_SYSTEM_ENTITYFILES_H
