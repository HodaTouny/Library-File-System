#include "SecondaryIndex.h"

void SecondaryIndex::deleteFromSecondaryIndex(vector<pair<string, int>>& fileIndex,vector<pair<int, LinkedList<string>*>>& secondaryIndex,
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
    string line;
    getline(file, line);
    cout<<"\n"<<line<<"\n";
    file.seekg(offset, ios::beg);
    file<<'#';
    removeUnderscores(line);
    vector<string> Data = parseString(line);
    string PKValue, NextValue,Rnn;
    if (Data.size() >= 3) {
        Rnn = Data[0];
        PKValue = Data[1];
        NextValue = Data[2];
        int newThirdValue = stoi(NextValue);
        linkedList->insertAtTail(PKValue, false,Rnn);
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
    file.close();
    return data;
}


bool SecondaryIndex::addRecordToSecondaryIndex(vector<pair<string, int>>& fileIndex,
                                               vector<pair<int, LinkedList<string>*>>& secondaryIndex,
                                               string data[], int& num) {
    bool found = false;
    int rnn;
    QueryProcessor qp;
    int index =qp.binarySearch(fileIndex,data[2]);
    if(index!=-1) {
        found=true;
        rnn=fileIndex[index].second;
    }
    if (found) {
        for (auto& secondaryEntry : secondaryIndex) {
            if (secondaryEntry.first == rnn) {
                secondaryEntry.second->insertAtTail(data[0], false, to_string(num));
                break;
            }
        }
    } else {
        LinkedList<string>* newLinkedList = new LinkedList<string>();
        fileIndex.push_back({data[2], num});
        newLinkedList->insertAtTail(data[0], false, to_string(num));
        secondaryIndex.push_back({num, newLinkedList});

    }
    num++;
    sort_Pairs(secondaryIndex);
    return true;
}

void SecondaryIndex:: writeToFile(const vector<pair<string, int>>& fileIndex,
                                  const vector<pair<int, LinkedList<string>*>>& secondaryIndex,
                                  const string& file1, const string& file2,int num) {
    fstream File1(file1, ios::out);
    if (!File1.is_open()) {
        cerr << "Error opening file: " << file1 << endl;
        return;
    }
    fstream File2(file2, ios::out);
    if (!File2.is_open()) {
        cerr << "Error opening file: " << file2 << endl;
        return;
    }
    for (const auto &entry: fileIndex) {
        File1 << entry.first << "|" << entry.second << "\n";
    }
    File1.close();
    string header = writer(5, to_string(num));
    File2 <<header << endl;
    for (const auto &secondaryEntry: secondaryIndex) {
        LinkedList<string> *linkedList = secondaryEntry.second;
        SLLNode<string> *currentNode = linkedList->getHead();
        while (currentNode != nullptr) {
            File2 << writer(3,linkedList->getRecordNum(currentNode) )<< "|" << writer(15,currentNode->data);
            if(currentNode->markedForDeletion==true){
                File2<< "|#__"<<"\n";
            }else if (currentNode->next == nullptr) {

                File2 << "|-1_" << "\n";
            } else {

                File2 <<"|"<< writer(3,linkedList->getRecordNum(linkedList->getNext(currentNode))) <<"\n";
            }
            currentNode = linkedList->getNext(currentNode);
        }
    }
}


std::string firstLine;
vector<std::pair<int, std::string>> SecondaryIndex::  readAndSortFile(const std::string& filename) {
    std::vector<std::pair<int, std::string>> data;
    IndexHelper x;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return data;
    }

    std::getline(file, firstLine);
    std::string line;
    while (std::getline(file, line)) {
        string val = line;
        string value ;
        x.removeUnderscores(line);
        cout<<line<<"\n";
        for(int i=0;i<line.size();i++){
            if(line[i] =='|'){
                break;
            }
            value+=line[i];
        }
        cout<<value<<"\n";
        int mm = stoi(value);
        data.push_back({mm,val});
    }
    file.close();
    sort(data.begin(), data.end(), [](const auto& a, const auto& b) {
        return a.first < b.first;
    });

    return data;
}

void SecondaryIndex::  writeToToFile(const std::string& filename, const std::vector<std::pair<int, std::string>>& data) {
    // Open the file
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }
    file<<firstLine<<"\n";
    for (const auto& pair : data) {
        file << pair.second << "\n";
    }
    file.close();
}
