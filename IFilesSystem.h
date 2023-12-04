#ifndef LIBRARY_FILE_SYSTEM_IFILESSYSTEM_H
#define LIBRARY_FILE_SYSTEM_IFILESSYSTEM_H
#include "bits/stdc++.h"
#include "LinkedList.h"

using namespace std;

class  IFilesSystem {
protected:
public:
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

    string to_string(int value) {
        ostringstream oss;
        oss << value;
        return oss.str();
    }

    string concat(const string& str1, const string& str2) {
        return str1 + "|" + str2;
    }


    int extractFirstValueFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening file: " << filename << "\n";
            return -1;
        }

        string line;
        getline(file, line);
        file.close();

        size_t pipePos = line.find('|');
        if (pipePos != string::npos) {
            string numberStr = line.substr(0, pipePos);
            istringstream iss(numberStr);
            int firstValue;
            iss >> firstValue;
            if (iss.fail()) {
                cerr << "Invalid number format: " << numberStr << "\n";
                return -1;
            }
            return firstValue;
        }
        return -1;
    }

    int extractSecondValueFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening file: " << filename << "\n";
            return -1;
        }

        string line;
        getline(file, line);
        file.close();

        size_t pipePos = line.find('|');
        if (pipePos != string::npos) {
            string numberStr = line.substr(pipePos + 1);
            istringstream iss(numberStr);
            int secondValue;
            iss >> secondValue;
            if (iss.fail()) {
                cerr << "Invalid number format: " << numberStr << "\n";
                return -1;
            }
            return secondValue;
        }

        return 17;
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

    void updateOffset(int offset, const string& fileName) {
        fstream file(fileName, ios::in | ios::out);
        if (!file) {
            cerr << "Error opening file: " << fileName << "\n";
            return;
        }
        string existingHeader;
        getline(file, existingHeader);
        string LastDeletedOffset  = existingHeader.substr(0, 9);
        string formattedOffset = formatNumber(offset, 5);
        string newHeader = LastDeletedOffset + "|" +  formattedOffset;
        file.seekp(0, ios::beg);
        file <<newHeader<<"\n";
        file.close();
    }
    void updateHeader(int number, const string& fileName) {
        fstream file(fileName, ios::in | ios::out);
        if (!file) {
            cerr << "Error opening file: " << fileName << "\n";
            return;
        }
        string existingHeader;
        getline(file, existingHeader);
        string firstNineDigits = existingHeader.substr(10, 5);
        string formattedNumber  = formatNumber(number, 9);
        string newHeader = formattedNumber + "|" + firstNineDigits ;
        file.seekp(0, ios::beg);
        file <<newHeader<<"\n";
        file.close();
    }

    string deleteRecord(int offset, const string& fileName) {
        fstream file(fileName, ios::in | ios::out);
        if (!file) {
            std::cerr << "Error opening file: " << fileName << "\n";
            return "";
        }
        vector<string> record = loadRecord(offset, fileName);
        file.seekp(offset, std::ios::beg);
        string Soffset= to_string(offset);
        int header= extractFirstValueFromFile(fileName);
        string finalString = concat("*"+to_string(header), record[0]+"|");
        file << finalString;
        file.close();
        updateHeader(offset,fileName);
        return record[1];
    }

    LinkedList<string> readAvailFromFile(const string& fileName) {
        LinkedList<string> availList;
        ifstream file(fileName);
        if (!file.is_open()) {
            cerr << "Error opening file for reading: " << fileName << "\n";
            return availList;
        }
        string line;
        while (getline(file, line)) {
            availList.insertAtTail(line);
        }
        file.close();
        return availList;
    }


    string AvailCreator(const string& fileName, int offset) {
        LinkedList<string> availList;
        ifstream file(fileName, ios::in);
        if (!file.is_open()) {
            cerr << "Error opening file for reading: " << fileName << "\n";
            return "";
        }
        file.seekg(offset);
        string line;
        string extractedData;
        getline(file, line);
        size_t startPos = 1;
        cout<<line<<"\n";
        size_t firstPos = line.find('|', startPos);
        if (firstPos != string::npos) {
            size_t secondPos = line.find('|', firstPos + 1);
            if (secondPos != string::npos) {
                extractedData = line.substr(startPos, secondPos - startPos);
            }
        }
        cout << extractedData;
        file.close();
        return extractedData;
    }

    void writeAvailToFile(const LinkedList<string>& availList, const string& fileName) {
        ofstream file(fileName, ios::out);
        if (!file.is_open()) {
            cerr << "Error opening file for writing: " << fileName << "\n";
            return;
        }
        SLLNode<string>* current = availList.head;
        while (current) {
            file << current->data << "\n";
            current = current->next;
        }
        file.close();
    }
    vector<int> extractSize(LinkedList<string>& availList) {
        vector<int> sizes;
        SLLNode<string>* current = availList.head;
        while (current) {
            string availRecord = current->data;
            size_t pos = availRecord.find('|');
            if (pos != string::npos) {
                int size = stoi(availRecord.substr(pos+1));
                sizes.push_back(size);
            }
            current = current->next;
        }
        sort(sizes.begin(), sizes.end());
        return sizes;
    }

    int findRecordLength(string data[], int dataSize){
        int recordLength = 0;
        for (int i = 0; i < dataSize; i++) {
            recordLength += data[i].size();
        }
        recordLength += dataSize;
        return recordLength;
    }
    int findBestFit(LinkedList<string>&AVAIL,int recordLength){
        vector<int> sizes = extractSize(AVAIL);
        int bestFit = 0;
        for (int size : sizes) {
            if (recordLength <= size) {
                bestFit = size;
                break;
            }
        }
        return bestFit;
    }


    string extractValueBetweenBars(const string& input) {
        size_t startPos = input.find('|') + 1;
        if (startPos != string::npos ) {
            string valueStr = input.substr(startPos, input.size() - startPos);
            return valueStr;
        }
        return "";
    }
    string updateNextNodeData(string x, string secondString) {
        size_t pos = x.find('|');
        if (pos == string::npos) {
            return x;
        }
        size_t secondPos = secondString.find('|');
        if (secondPos != string::npos) {
            return x.substr(0, pos + 1) + secondString.substr(secondPos + 1);
        } else {
            return x;
        }
    }

    void addRecord(LinkedList<string>&AVAIL,string fileName,string data[],int dataSize=3){
        int recordL = findRecordLength(data,dataSize);
        int bestFit = findBestFit(AVAIL,recordL);
        int header = extractFirstValueFromFile(fileName);
        if (header == -1 || bestFit == 0) {
            appendToFile(data, dataSize, fileName);
        } else {
            auto current = AVAIL.head;
            while (current != nullptr) {
                string availRecord = current->data;
                string valueStr = extractValueBetweenBars(availRecord);
                int value = stoi(valueStr);
                if(value == bestFit) {
                    int offset;
                    size_t pos = availRecord.find("|");
                    offset = stoi(availRecord.substr(0, pos));
                    int size = stoi(availRecord.substr(pos + 1));
                    if (size == bestFit && current->next == nullptr) {
                        insertRecord(header, data, dataSize, fileName, size);
                        updateHeader(offset,"Books.txt");
                    }else if (size == bestFit) {
                        string nextNodeDataPtr =current->next->data;
                        if (!nextNodeDataPtr.empty()) {
                            string nextRecord =  nextNodeDataPtr;
                            offset = stoi(nextRecord.substr(0, pos));
                            insertRecord(offset, data, dataSize, fileName, size);
                            string newValue =  updateNextNodeData(current->data,current->next->data);
                            current->next->data = newValue;
                        }
                    }
                    AVAIL.removeNodeWithValue(availRecord);
                    return;
                }
                current = current->next;
            }

        }

    }

    void appendToFile(const string data[], int dataSize, const string &fileName) {
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

    void insertRecord(int offset, const string data[], int dataSize, const string &fileName, int oldSize) {
        fstream file(fileName, ios::in | ios::out);
        if (!file) {
            cerr << "Error opening file: " << fileName << endl;
            return;
        }
        file.seekp(offset, ios::beg);
        int recordLength = 0;
        for (int i = 0; i < dataSize; i++) {
            recordLength += data[i].size();
        }
        recordLength += dataSize;
        file << recordLength;
        for (int i = 0; i < dataSize; i++) {
            file << "|" << data[i];
        }
        int underscoresNeeded = oldSize - recordLength;
        string underscores;
        for (int i = 0; i <=underscoresNeeded; ++i) {
            underscores += "_";
        }
        file << underscores;
        file.close();
    }
};
#endif //LIBRARY_FILE_SYSTEM_IFILESSYSTEM_H
