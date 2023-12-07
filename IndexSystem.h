
#ifndef LIBRARY_FILE_SYSTEM_INDEXSYSTEM_H
#define LIBRARY_FILE_SYSTEM_INDEXSYSTEM_H
#include <bits/stdc++.h>
#include "IFilesSystem.h"
#include "LinkedList.h"
using namespace std;
class IndexSystem {
private:
    void sortPairs(vector<pair<string, int>> &FileIndex){
        sort(FileIndex.begin(), FileIndex.end(),
             [](const pair<string, int>& a, const pair<string, int>& b) {
                 return a.first < b.first;
             });
    }

public:
    //Load Index File Into Vector [main memory to use it easily]
    vector<pair<string, int>> LoadIndexFile(const string& filename) {
        vector<pair<string, int>> FileIndex;
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening file: " << filename << endl;
            return FileIndex;
        }
        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            string key;
            int value;
            if (getline(iss, key, '|') && (iss >> value)) {
                FileIndex.push_back(pair<string, int>(key, value));
            }
        }
        file.close();
        sortPairs(FileIndex);
        return FileIndex;
    }

    //upload index file after all edits
    void uploadIndexFile(vector<pair<string, int>>& FileIndex, const string& filename) {
        ofstream indexFile(filename);
        if (!indexFile.is_open() || !indexFile.good()) {
            cerr << "Error opening file for writing: " << filename << endl;
            return;
        }
        for (const auto& record : FileIndex) {
            indexFile << record.first << "|" << record.second << "\n";
        }
        indexFile.close();
    }

    //remove deleted record from the index
    void deleteFromIndex(vector<pair<string, int>>& fileIndex,string targetString) {
        auto it = remove_if(fileIndex.begin(), fileIndex.end(),
                            [targetString](const pair<string, int>& element) {
                                return element.first == targetString;
                            });

        fileIndex.erase(it, fileIndex.end());
    }



    //insert record into the index
    bool insertIntoIndex(vector<pair<string, int>>& FileIndex,string key,int offset){
        FileIndex.push_back(pair<string ,int>{key,offset});
        sortPairs(FileIndex);
        return true;
    }



//if record begin with asterisk dont put
    vector<vector<string>>loadFileIntoVector(const string& fileName) {
        vector<vector<string>>data;
        ifstream file(fileName);
        string line;
        while (std::getline(file, line)) {
            istringstream iss(line);
            vector<std::string> tokens;
            string token;
            while (std::getline(iss, token, '|')) {
                tokens.push_back(token);
            }
            data.push_back(tokens);
        }
        data.erase(data.begin());
        file.close();
        return data;
    }


    vector<pair<int, LinkedList<string>>> loadIndexList(const string& fileName) {
        vector<pair<int, LinkedList<string>>> result;
        ifstream file(fileName);
        if (!file.is_open()) {
            cerr << "Error opening file: " << fileName << endl;
            return result;
        }
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string token;
            vector<string> tokens;
            while (getline(ss, token, '|')) {
                tokens.push_back(token);
            }
            for(int i=0;i<tokens.size();i++){
                cout<<tokens[i]<<" ";
            }
            if (tokens.size() == 3) {
                int RRN = stoi(tokens[0]);
                string bookName = tokens[1];
                int pointer = stoi(tokens[2]);

                auto it = find_if(result.begin(), result.end(), [RRN](const pair<int, LinkedList<string>>& element) {
                    return element.first == RRN;
                });

                if (it == result.end()) {
                    LinkedList<string> newList;
                    newList.insertAtTail(bookName);
                    result.emplace_back(RRN, newList);
                } else {
                    it->second.insertAtTail(bookName);
                }

                // Find the corresponding pair for the pointer
                auto pointerIt = find_if(result.begin(), result.end(), [pointer](const pair<int, LinkedList<string>>& element) {
                    return element.first == pointer;
                });

                // If the pair exists for the pointer, append the book to its linked list
                if (pointerIt != result.end()) {
                    pointerIt->second.insertAtTail(bookName);
                }
            }
        }

        file.close();
        return result;
    }

    void deleteFromSecondaryIndex(vector<pair<string, string>>& fileIndex,
                                  vector<pair<string, LinkedList<string>*>>& secondaryIndex,
                                  const string& targetString, const string& targetName) {
        for (int i = 0; i < fileIndex.size(); i++) {
            if (fileIndex[i].first == targetName) {
                string rnn = fileIndex[i].second;
                for (int j = 0; j < secondaryIndex.size(); j++) {
                    int index = secondaryIndex[j].second->indexOf(targetString);
                    if (index != -1) {
                        secondaryIndex[j].second->markDeleted(index);
                        if (secondaryIndex[j].first == rnn && secondaryIndex[j].second->head->next == nullptr) {
                            fileIndex.erase(fileIndex.begin() + i);
                        }
                    }
                }
            }
        }
    }






    string extractHeader(const string& fileName) {
        std::ifstream inputFile(fileName);
        if (!inputFile) {
            std::cerr << "Error opening file: " << fileName << "\n";
            return "";
        }
        string line;
        while (getline(inputFile, line)) {
            std::size_t underscorePos = line.find('_');
            if (underscorePos != string::npos) {
                std::string numberStr = line.substr(0, underscorePos);
                return numberStr;
            }
            return "";
        }
    }
    string to_string(int value) {
        ostringstream oss;
        oss << value;
        return oss.str();
    }
    void writeHeader( const string& fileName) {
        fstream file(fileName, ios::in | ios::out);
        if (!file) {
            cerr << "Error opening file: " << fileName << "\n";
            return;
        }
        string number= extractHeader(fileName);
        string firstLine;
        getline(file, firstLine);
        int newHeader = stoi(number)+1;
        string Nheader= to_string(newHeader);
        int underscoresNeeded = 5 - Nheader.length();

        for (int i = 0; i < underscoresNeeded; ++i) {
            Nheader += "_";
        }
        file.seekp(0, ios::beg);
        file << Nheader;
        file.close();
    }
    vector<string> loadRecord(int offset, const string& fileName) {
        vector<string> record;
        ifstream file(fileName);
        if (!file.is_open()) {
            cerr << "Unable to open file.\n";
            return record;
        }
        file.seekg(offset,ios::beg);
        if (!file) {
            std::cerr << "Error seeking to offset.\n";
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

    void updateLastValue(const string& fileName, int offset) {
        std::fstream file(fileName, std::ios::in | std::ios::out);
        if (!file.is_open()) {
            std::cerr << "Error opening file." << std::endl;
            return;
        }
        vector<string> record=loadRecord(offset,fileName);

        if (record.empty()) {
            std::cerr << "Error: no record found at the given offset." << std::endl;
            return;
        }
        string integer = extractHeader(fileName);
        string str= writer(3, integer);
        record.back() = str;
        file.seekp(offset);
        for (int i = 0; i < record.size(); ++i) {
            file << record[i];
            if (i < record.size() - 1) {
                file << "|";
            }
        }
        file << endl;
    }



    int calculateOffset(int rnn) {
        return 5 + (rnn * 23) + (rnn *2) + 2;
    }
    int getValueAfterLastDelimiter(const string& filePath, int offset) {
        ifstream file(filePath);

        if (!file) {
            cerr << "Error opening file: " << filePath << std::endl;
            return -1;
        }
        file.seekg(offset);
        string line;
        getline(file, line);
        file.close();
        size_t lastDelimiterPos = line.find_last_of('|');
        string valueStr = line.substr(lastDelimiterPos + 1);
        try {
            return stoi(valueStr);
        } catch (const invalid_argument& e) {

            return -1;
        }
    }
    string  writer(int integer,string number){
        int underscoresNeeded = integer- number.length();
        for (int i = 0; i < underscoresNeeded; ++i) {
            number += "_";
        }
        return number;
    }

    void addSecondaryIndex(string data[], const string& SKfile, const string& SKlistfile) {
        ofstream outFile(SKfile, ios::app);
        ofstream outFile2(SKlistfile, ios::app);
        vector<pair<string, int>> myfile = LoadIndexFile(SKfile);
        bool found = false;
        int rnn;
        for (const auto& entry : myfile) {
            if (data[2] == entry.first) {
                found = true;
                rnn=entry.second;
                break;
            }
        }

        string firstSkValue = extractHeader(SKlistfile);
        if (found) {
            int offset = calculateOffset(rnn);
            int lastValue = getValueAfterLastDelimiter(SKlistfile, offset);
            if (lastValue == -1) {
                updateLastValue(SKlistfile, offset);
            } else {
                while (lastValue != -1) {
                    //cout<<"hello maya";
                    int newOffset = calculateOffset(lastValue);
                    lastValue = getValueAfterLastDelimiter(SKlistfile, newOffset);
                    if (lastValue == -1) {
                        updateLastValue(SKlistfile, newOffset);
                    }
                }
            }
            outFile2 << writer(3, firstSkValue) << "|" << writer(15, data[0]) << "|" << writer(3, "-1") << endl;
            writeHeader(SKlistfile);

        } else {
            outFile << data[2] << "|"<< firstSkValue << endl;
            outFile.close();
            outFile2 << writer(3,firstSkValue) << "|"  << writer(15,data[0]) << "|"<< writer(3,"-1") << endl;
            writeHeader(SKlistfile);
        }
    }


    void removeUnderscores(string& str) {
        str.erase(remove(str.begin(), str.end(), '_'), str.end());
    }

    vector<string> parseString(const string& inputString) {
        vector<string> result;
        stringstream ss(inputString);
        string item;
        while (getline(ss, item, '|')) {
            result.push_back(item);
        }
        return result;
    }

    vector<pair<int, LinkedList<string>*>> loadLinkedListFile(string fileName) {
        vector<pair<int, LinkedList<string>*>> data;
        fstream file(fileName, ios::in | ios::out);
        if (!file.is_open()) {
            cerr << "Error opening file!" << endl;
            return data;
        }
        string liney = extractHeader(fileName);
        int numRecords = stoi(liney);
        string line;
        getline(file, line);

        for (int i = 0; i < numRecords; i++) {
            int offset = calculateOffset(i);
            file.seekg(offset,ios::beg);
            getline(file, line);
            if (line[0] == '#') {
                continue;
            }
            removeUnderscores(line);
            vector<string> Data = parseString(line);
            string RNN, PKValue, NextValue;
            RNN = Data[0];
            int firstValue = stoi(RNN);

            PKValue = Data[1];
            LinkedList<string>* linkedList = new LinkedList<string>();
            linkedList->insertAtTail(PKValue);

            NextValue = Data[2];
            int thirdValue = stoi(NextValue);
            processLinkedList(file, linkedList, thirdValue);
            data.push_back({firstValue, linkedList});
        }
        int offs;
        for(int i=0;i<numRecords;i++){
            offs = calculateOffset(i);
            file.seekg(offs, ios::beg);
            file<<to_string(i);
        }
        file.close();
        return data;
    }

    void processLinkedList(fstream& file, LinkedList<string>* linkedList, int thirdValue) {
        if (thirdValue == -1) {
            return;
        }
        int offset = calculateOffset(thirdValue);
        file.seekg(offset, ios::beg);
        file<<'#';
        string line;
        getline(file, line);
        removeUnderscores(line);
        vector<string> Data = parseString(line);
        string PKValue, NextValue;
        if (Data.size() >= 3) {
            PKValue = Data[1];
            linkedList->insertAtTail(PKValue);
            NextValue = Data[2];
            int newThirdValue = stoi(NextValue);
            processLinkedList(file, linkedList, newThirdValue);
        }
    }


    string AddUnderscores(string inputString, int Size) {
        if (inputString.size() >= Size) {
            return inputString;
        }
        string paddedString = inputString;
        paddedString.append(Size - inputString.size(), '_');
        return paddedString;
    }

    void writeHeaderToLinkedListFile(int num, string filename) {
        string numStr = to_string(num);
        string paddedNumStr = AddUnderscores(numStr,5);
        ofstream file(filename,ios ::out);
        if (file.is_open()) {
            file.seekp(0,ios::beg);
            file << paddedNumStr << "\n";
        }
    }
};


#endif //LIBRARY_FILE_SYSTEM_INDEXSYSTEM_H