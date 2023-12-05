
#ifndef LIBRARY_FILE_SYSTEM_INDEXSYSTEM_H
#define LIBRARY_FILE_SYSTEM_INDEXSYSTEM_H
#include <bits/stdc++.h>
#include "IFilesSystem.h"
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

    string formatNumber(int value, int digits) {
        string formatted = to_string(value);
        if (formatted.length() < digits) {
            formatted = formatted + string(digits - formatted.length(), '_');
        } else if (formatted.length() > digits) {
            formatted = formatted.substr(0, digits);
        }
        return formatted;
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

    void updateLastValue(const string& fileName, int offset) {
        std::fstream file(fileName, std::ios::in | std::ios::out);
        if (!file.is_open()) {
            std::cerr << "Error opening file." << std::endl;
            return;
        }
        IFilesSystem load;
        vector<string> record=load.loadRecord(offset,fileName);
        for( int i = 0; i <record.size(); i++){
            cout<<record[i]<<" ";
        }
        cout<<endl;
        if (record.empty()) {
            std::cerr << "Error: no record found at the given offset." << std::endl;
            return;
        }
        string integer = extractHeader(fileName);
         cout<<"i: "<<integer;
        record.back() = integer;
        file.seekp(offset);
        for (int i = 0; i < record.size(); ++i) {
            file << record[i];
            if (i < record.size() - 1) {
                file << "|";
            }
        }
        file << endl;
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


};


#endif //LIBRARY_FILE_SYSTEM_INDEXSYSTEM_H