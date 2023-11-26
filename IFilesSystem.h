#ifndef LIBRARY_FILE_SYSTEM_IFILESSYSTEM_H
#define LIBRARY_FILE_SYSTEM_IFILESSYSTEM_H
#include "bits/stdc++.h"
using namespace std;

class  IFilesSystem {
    protected:
    public:

         void deleteRecord(string data[],string fileName){

         }


    void addRecord(const std::string data[], int dataSize, const std::string& fileName) {
        int recordLength = 0;
        std::ofstream outFile(fileName, std::ios::app);
        if (!outFile.is_open()) {
            std::cerr << "Error opening file: " << fileName << std::endl;
            return;
        }
        for (int i = 0; i < dataSize; i++) {
            recordLength += data[i].size();
        }
        recordLength += dataSize;
        outFile << recordLength;
        for (int i = 0; i < dataSize; i++) {
            outFile << "|" << data[i];
        }
        outFile << "\n";
        outFile.close();
    }




    string loadRecord(int offset,string fileName){

        }

        void updateIndex(string fileName){

        }
        void loadIndex(string fileName){

        }

};


#endif //LIBRARY_FILE_SYSTEM_IFILESSYSTEM_H
