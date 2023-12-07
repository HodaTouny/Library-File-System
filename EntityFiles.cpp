#include "EntityFiles.h"
vector<string> EntityFiles :: loadRecord(int offset, string fileName) {
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
        if(ch == '*'){
            cout<<"This Record is deleted,You can't get it!!!\n";
        }
        do {
            if (ch == '|') {
                removeUnderscores(word);
                record.push_back(word);
                word = "";
            } else {
                word += ch;
            }
        } while (file >> ch && ch != '\n');
    }
    if (!word.empty()) {
        removeUnderscores(word);
        record.push_back(word);
    }
    file.close();
    return record;
}


string EntityFiles::deleteRecord(int offset, string fileName) {
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

void EntityFiles::addRecord(LinkedList<string>&AVAIL,string fileName,string data[],int dataSize){
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

void EntityFiles:: updateRecord(int offset,  string newValue, string fileName,  LinkedList<string>& availList) {
    vector<string> originalRecord = loadRecord(offset, fileName);
    if (originalRecord.size() >= 3) {
        originalRecord[2] = newValue;
        originalRecord.erase(originalRecord.begin());
        deleteRecord(offset, fileName);
        appendToFile(originalRecord.data(),originalRecord.size(),fileName);

    }
}

