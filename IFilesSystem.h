#ifndef LIBRARY_FILE_SYSTEM_IFILESSYSTEM_H
#define LIBRARY_FILE_SYSTEM_IFILESSYSTEM_H
#include "bits/stdc++.h"
using namespace std;

class  IFilesSystem {
    protected:
    public:

    void deleteRecord(int offset, const std::string& fileName) {
        fstream file(fileName, std::ios::in | std::ios::out);
        if (!file) {
            std::cerr << "Error opening file: " << fileName << std::endl;
            return;
        }
        file.seekg(offset, std::ios::beg);
        file<<"*";
        file.close();
        //function updateIndex File [offset + 1]
    }


    void addRecord(const std::string data[], int dataSize, const std::string& fileName) {
        //check avail list first
        int recordLength = 0;
        ofstream outFile(fileName, std::ios::app);
        if (!outFile.is_open()) {
            cerr << "Error opening file: " << fileName << std::endl;
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





    string loadRecord(int offset, const string& fileName) {
        string record;
        ifstream file(fileName);
        if (!file.is_open()) {
            std::cerr << "Unable to open file." << std::endl;
            return"";
        }
        file.seekg(offset, std::ios::beg);
        char ch;
        while (file.get(ch) && ch != '\n') {
            if (ch == '|') {
                ch = ' ';
            }
            record+=ch;
        }

        file.close();
        return record;

    }

        void updateIndex(string fileName){

        }
        void loadIndex(string fileName){

        }

};


#endif //LIBRARY_FILE_SYSTEM_IFILESSYSTEM_H
