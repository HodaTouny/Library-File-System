#ifndef LIBRARY_FILE_SYSTEM_IFILESSYSTEM_H
#define LIBRARY_FILE_SYSTEM_IFILESSYSTEM_H
#include "bits/stdc++.h"
using namespace std;

class  IFilesSystem {
    protected:
    public:

    string deleteRecord(int offset, const string& fileName) {
        fstream file(fileName, ios::in | ios::out);
        if (!file) {
            std::cerr << "Error opening file: " << fileName << "\n";
            return"";
        }
        vector<string> record = loadRecord(offset,fileName);
        file.seekg(offset, ios::beg);
        file<<"*";
        file.close();
        return record[1];
    }


    void addRecord(const string data[], int dataSize, const string& fileName) {
        //check avail list first
        int recordLength = 0;
        ofstream outFile(fileName, ios::app);
        if (!outFile.is_open()) {
            cerr << "Error opening file: " << fileName << "\n";
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





    vector<string> loadRecord(int offset, const string& fileName) {
        vector<string> record;
        ifstream file(fileName);
        if (!file.is_open()) {
            std::cerr << "Unable to open file." << std::endl;
            return record;
        }
        file.seekg(offset,ios::beg);
        char ch;
        string word;
        while (file.get(ch) && ch != '\n') {
            if (ch == '|') {
                record.push_back(word);
                word = "";
            } else {
                word += ch;
            }
        }
        if (!word.empty()) {
            record.push_back(word);
        }
        file.close();
        return record;
    }

};


#endif //LIBRARY_FILE_SYSTEM_IFILESSYSTEM_H
