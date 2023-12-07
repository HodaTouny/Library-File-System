#include "SecondaryIndex.h"
void SecondaryIndex::deleteFromSecondaryIndex(vector<pair<string, string>>& fileIndex,
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

vector<pair<int, LinkedList<string>*>>SecondaryIndex:: loadLinkedListFile(string fileName) {
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
        offs = calculateFixedOffset(i);
        file.seekg(offs, ios::beg);
        file<<to_string(i);
    }
    file.close();
    return data;
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
    string PKValue, NextValue;
    if (Data.size() >= 3) {
        PKValue = Data[1];
        linkedList->insertAtTail(PKValue);
        NextValue = Data[2];
        int newThirdValue = stoi(NextValue);
        processLinkedList(file, linkedList, newThirdValue);
    }
}

void SecondaryIndex:: addRecordToSecondaryIndex(string data[], string SKfile, string SKlistfile, vector<pair<string, int>>& myfile) {
    ofstream outFile(SKfile, ios::app);
    ofstream outFile2(SKlistfile, ios::app);
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
        int offset = calculateFixedOffset(rnn);
        int lastValue = getValueAfterLastDelimiter(SKlistfile, offset);
        if (lastValue == -1) {
            updateLastValue(SKlistfile, offset);
        } else {
            while (lastValue != -1) {
                int newOffset = calculateFixedOffset(lastValue);
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
