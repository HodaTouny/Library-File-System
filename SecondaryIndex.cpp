#include "SecondaryIndex.h"

void deleteFromSecondaryIndex(vector<pair<string, int>>& fileIndex,vector<pair<int, LinkedList<string>*>>& secondaryIndex,
                              const string& targetString, const string& targetName) {
    for (int i = 0; i < fileIndex.size(); i++) {
        if (fileIndex[i].first == targetName) {
            int rnn = fileIndex[i].second;
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


void SecondaryIndex:: processLinkedList(fstream& file, LinkedList<string>* linkedList, int thirdValue) {
    if (thirdValue == -1) {
        return;
    }
    int offset = calculateFixedOffset(thirdValue);
    file.seekg(offset, ios::beg);
    file<<'#';
    string line;
    getline(file, line);
    removeUnderscores(line);
    vector<string> Data = parseString(line);
    string PKValue, NextValue,Rnn;
    if (Data.size() >= 3) {
        Rnn = Data[0];
        PKValue = Data[1];
        linkedList->insertAtTail(PKValue, false,Rnn);
        NextValue = Data[2];
        int newThirdValue = stoi(NextValue);
        processLinkedList(file, linkedList, newThirdValue);
    }
}

vector<pair<int, LinkedList<string>*>> SecondaryIndex::loadLinkedListFile(string fileName) {
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
        int offset = calculateFixedOffset(i);
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
        if(line[20] == '#'){
            LinkedList<string>* linkedList = new LinkedList<string>();
            linkedList->insertAtTail(Data[1], true, RNN);
            data.push_back({firstValue, linkedList});
            continue;
        }

        PKValue = Data[1];
        LinkedList<string>* linkedList = new LinkedList<string>();
        linkedList->insertAtTail(PKValue,false, to_string(firstValue));

        NextValue = Data[2];
        int thirdValue = stoi(NextValue);
        processLinkedList(file, linkedList, thirdValue);
        data.push_back({firstValue, linkedList});
    }
    int offs;
    for(int i=0;i<numRecords;i++){
        offs = calculateFixedOffset(i);
        file.seekg(offs, ios::beg);
        file<<to_string(i);
    }
    file.close();
    sort_Pairs(data);
    return data;
}
bool SecondaryIndex:: addRecordToSecondaryIndex(vector<pair<string, int>>& fileIndex,vector<pair<int,
        LinkedList<string>*>>& secondaryIndex ,string data[],int& num){
    if(binarySearch(fileIndex,data[2])){
        return false;
    }
    bool found = false;
    int rnn;
    for (const auto& entry : fileIndex) {
        if (entry.first == data[2]) {
            found = true;
            rnn = entry.second;
            break;
        }
    }

    if (found) {
        for (auto& secondaryEntry : secondaryIndex) {
            if (secondaryEntry.first == rnn) {
                secondaryEntry.second->insertAtTail(data[0],false, to_string(rnn));
                num++;
                break;

            }
        }
    } else {
        LinkedList<string>* newLinkedList = new LinkedList<string>();
        fileIndex.push_back({data[2], num});
        newLinkedList->insertAtTail(data[0], false, to_string(num));
        secondaryIndex.push_back({ num++, newLinkedList });
    }
    sort_Pairs(secondaryIndex);
    return true;
}
void SecondaryIndex:: writeToFile(const vector<pair<string, int>>& fileIndex,
                 const vector<pair<int, LinkedList<string>*>>& secondaryIndex,
                 const string& file1, const string& file2) {
    fstream File1(file1, ios::out);
    if (!File1.is_open()) {
        cerr << "Error opening file: " << file1 << endl;
        return;
    }

    for (const auto &entry: fileIndex) {
        File1 << entry.first << "|" << entry.second << endl;
    }
    File1.close();

    fstream File2(file2, ios::out);
    if (!File2.is_open()) {
        cerr << "Error opening file: " << file2 << endl;
        return;
    }
    for (const auto &secondaryEntry: secondaryIndex) {
        LinkedList<string> *linkedList = secondaryEntry.second;
        SLLNode<string> *currentNode = linkedList->getHead();
        while (currentNode != nullptr) {
            File2 << linkedList->getRecordNum(currentNode) << "|" << currentNode->data;

            if (currentNode->next == nullptr) {
                File2 << "|-1" << endl;
            } else {
                File2 <<"|"<< linkedList->getRecordNum(linkedList->getNext(currentNode)) << endl;
            }
            currentNode = linkedList->getNext(currentNode);
        }
    }
}





