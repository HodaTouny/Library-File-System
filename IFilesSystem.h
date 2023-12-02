#ifndef LIBRARY_FILE_SYSTEM_IFILESSYSTEM_H
#define LIBRARY_FILE_SYSTEM_IFILESSYSTEM_H
#include "bits/stdc++.h"
#include "LinkedList.h"

using namespace std;

class  IFilesSystem {
protected:
public:
    vector<std::string> loadRecord(int offset, const std::string& fileName) {
        vector<std::string> record;
        ifstream file(fileName);
        if (!file.is_open()) {
            std::cerr << "Unable to open file." << std::endl;
            return record;
        }
        file.seekg(offset, std::ios::beg);
        if (!file) {
            std::cerr << "Error seeking to offset." << std::endl;
            file.close();
            return record;
        }
        char ch;
        string word;
        if (file >> noskipws >> ch) {
            do {
                if (ch == '|') {
                    record.push_back(word);
                    word = "";
                } else {
                    word += ch;
                }
            } while (file >> ch && ch != '\n');
        }
        if (!word.empty()) {
            record.push_back(word);
        }
        file.close();
        return record;
    }


    string to_string(int value) {
        ostringstream oss;
        oss << value;
        return oss.str();
    }

    std::string concat(const string& str1, const string& str2) {
        return str1 + "|" + str2;
    }
    //int header=-1;
    int extractHeader(const string& fileName) {
        std::ifstream inputFile(fileName);
        if (!inputFile) {
            std::cerr << "Error opening file: " << fileName << "\n";
            return -1;
        }

        string line;
        while (getline(inputFile, line)) {
            std::size_t underscorePos = line.find('_');

            if (underscorePos != string::npos) {
                std::string numberStr = line.substr(0, underscorePos);

                try {
                    return stoi(numberStr);
                } catch (const invalid_argument& e) {
                    cerr << "Invalid number format: " << numberStr << "\n";
                } catch (const out_of_range& e) {
                    cerr << "Number out of range: " << numberStr << "\n";
                }
            }
        }

        return -1;
    }
    void writeHeader(int number, const string& fileName) {
        fstream file(fileName, ios::in | ios::out);
        if (!file) {
            cerr << "Error opening file: " << fileName << "\n";
            return;
        }
        string firstLine;
        getline(file, firstLine);
        int underscoresNeeded = 20 - to_string(number).length();
        string newHeader = to_string(number);
        for (int i = 0; i < underscoresNeeded; ++i) {
            newHeader += "_";
        }
        file.seekp(0, ios::beg);
        file << newHeader;
        file.close();
    }


    string deleteRecord(int offset, const string& fileName) {
        fstream file(fileName, ios::in | ios::out);
        if (!file) {
            std::cerr << "Error opening file: " << fileName << "\n";
            return "";
        }
        vector<string> record = loadRecord(offset, fileName);
        int totalSize = 0;
        for (const string& str : record) {
            totalSize += str.length();
        }
        for (const string& str : record) {
            cout<<str<<" ";
        }
        cout<<endl;
        cout<<totalSize<<endl;
        file.seekp(offset, std::ios::beg);
        string Soffset= to_string(offset);
        int header= extractHeader(fileName);
        string finalString = concat("*"+to_string(header), to_string(totalSize+1)+"|");
        file << finalString;
        file.close();
        // writeHeader(offset,fileName);
        return record[1];
    }

    LinkedList<string> AvailCreator(string& fileName) {
        LinkedList<string> availList;

        fstream file(fileName, ios::in);
        if (!file) {
            cerr << "Error opening file: " << fileName << "\n";
            return availList;
        }

        string line;
        while (getline(file, line)) {
            if (line.size() > 0 && line[0] == '*') {
                size_t startPos = 1;
                size_t firstPos = line.find('|', startPos);

                if (firstPos != string::npos) {
                    size_t secondPos = line.find('|', firstPos + 1);

                    if (secondPos != string::npos) {
                        string extractedData = line.substr(startPos, secondPos - startPos);
                        availList.insertAtTail("" + extractedData + "|");
                    }
                }
            }
        }

        file.close();
        return availList;
    }
//    vector<int> extractSize (LinkedList<string> availList) {
//        vector<int> sizes;
//        char delimiter='|';
//        LinkedList<string> tempAVAILList = availList;
//        bool recordInserted = false;
//        while (!tempAVAILList.isEmpty() && !recordInserted) {
//            string availRecord = tempAVAILList.removeFirst();
//            size_t pos = availRecord.find("|");
//            if (pos != string::npos) {
//                int size = stoi(availRecord.substr(pos + 1));
//                sizes.push_back(size);
//                }
//
//        }
//
//    }
//
//    void addRecord(const string data[], int dataSize, const string& fileName, LinkedList<string>& AVAILList) {
//        int header= extractHeader(fileName);
//        if (header == -1) {
//            appendToFile(data, dataSize, fileName);
//        } else {
//            LinkedList<string> tempAVAILList = AVAILList;
//            bool recordInserted = false;
//
//            while (!tempAVAILList.isEmpty() && !recordInserted) {
//                string availRecord = tempAVAILList.removeFirst();
//                size_t pos = availRecord.find("|");
//                if (pos != string::npos) {
//                    int offset = stoi(availRecord.substr(1, pos - 1));
//                    int size = stoi(availRecord.substr(pos + 1));
//                    if (size >= dataSize) {
//                        insertRecord(offset, data, dataSize, fileName);
//                        recordInserted = true;
//                    }
//                }
//            }
//            if (!recordInserted) {
//                appendToFile(data, dataSize, fileName);
//            }
//        }
//    }
    void addRecord(const string data[], int dataSize, const string& fileName) {
        // Check if the file can be opened
        ofstream outFile(fileName, ios::app);
        if (!outFile.is_open()) {
            cerr << "Error opening file: " << fileName << "\n";
            return;
        }

        int recordLength = 0;
        for (int i = 0; i < dataSize; i++) {
            recordLength += data[i].size();
        }
        recordLength += dataSize - 1;
        outFile << recordLength;
        for (int i = 0; i < dataSize; i++) {
            outFile << "|" << data[i];
        }
        outFile << "\n";

        outFile.close();
    }

//
//
//    void appendToFile(const string data[], int dataSize, const string& fileName) {
//        int recordLength = 0;
//        ofstream outFile(fileName, ios::app);
//        if (!outFile.is_open()) {
//            cerr << "Error opening file: " << fileName << "\n";
//            return;
//        }
//        for (int i = 0; i < dataSize; i++) {
//            recordLength += data[i].size();
//        }
//        recordLength += dataSize;
//        outFile << recordLength;
//        for (int i = 0; i < dataSize; i++) {
//            outFile << "|" << data[i];
//        }
//        outFile << "\n";
//        outFile.close();
//    }
    void insertRecord(int offset, const string data[], int dataSize, const string& fileName) {
        std::fstream file(fileName, std::ios::in | std::ios::out);

        if (!file) {
            std::cerr << "Error opening file: " << fileName << std::endl;
            return;
        }
        file.seekp(offset, std::ios::beg);
        int recordLength = 0;
        for (int i = 0; i < dataSize; i++) {
            recordLength += data[i].size();
        }
        recordLength += dataSize;
        file << recordLength;
        for (int i = 0; i < dataSize; i++) {
            file << "|" << data[i];
        }
        file.close();

    }

};

#endif //LIBRARY_FILE_SYSTEM_IFILESSYSTEM_H
