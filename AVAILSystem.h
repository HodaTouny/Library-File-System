#ifndef LIBRARY_FILE_SYSTEM_AVAILSYSTEM_H
#define LIBRARY_FILE_SYSTEM_AVAILSYSTEM_H
#include "bits/stdc++.h"
#include "LinkedList.h"

using namespace std;

class  AVAILSystem {
public:
    LinkedList<string> readAvailFromFile(string fileName);
    void writeAvailToFile(const LinkedList<string> &availList, const string &fileName);
    string AvailCreator(string fileName, int offset);
};
#endif //LIBRARY_FILE_SYSTEM_AVAILSYSTEM_H
