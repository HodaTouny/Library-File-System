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
    return data;
}

void SecondaryIndex:: addRecordToSecondaryIndex(vector<pair<string, int>>& fileIndex,vector<pair<int,
        LinkedList<string>*>>& secondaryIndex ,string data[],int num){
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
        newLinkedList->insertAtTail(data[0], false, to_string(num));
        secondaryIndex.push_back({ ++num, newLinkedList });
    }
}
//void SecondaryIndex:: addRecordToSecondaryIndex(string data[], string SKfile, string SKlistfile, vector<pair<string, int>>& myfile) {
//    ofstream outFile(SKfile, ios::app);
//    ofstream outFile2(SKlistfile, ios::app);
//    bool found = false;
//    int rnn;
//    for (const auto& entry : myfile) {
//        if (data[2] == entry.first) {
//            found = true;
//            rnn=entry.second;
//            break;
//        }
//    }
//
//    string firstSkValue = extractHeader(SKlistfile);
//    if (found) {
//        int offset = calculateFixedOffset(rnn);
//        int lastValue = getValueAfterLastDelimiter(SKlistfile, offset);
//        if (lastValue == -1) {
//            updateLastValue(SKlistfile, offset);
//        } else {
//            while (lastValue != -1) {
//                int newOffset = calculateFixedOffset(lastValue);
//                lastValue = getValueAfterLastDelimiter(SKlistfile, newOffset);
//                if (lastValue == -1) {
//                    updateLastValue(SKlistfile, newOffset);
//                }
//            }
//        }
//        outFile2 << writer(3, firstSkValue) << "|" << writer(15, data[0]) << "|" << writer(3, "-1") << endl;
//        writeHeader(SKlistfile);
//
//    } else {
//        outFile << data[2] << "|"<< firstSkValue << endl;
//        outFile.close();
//        outFile2 << writer(3,firstSkValue) << "|"  << writer(15,data[0]) << "|"<< writer(3,"-1") << endl;
//        writeHeader(SKlistfile);
//    }

//////////////////////////
//void addSecondaryIndex(string data[], const string& SKfile, const string& SKlistfile) {
//    ofstream outFile(SKfile, ios::app);
//    ofstream outFile2(SKlistfile, ios::app);
//    vector<pair<string, int>> myfile = LoadIndexFile(SKfile);
//    bool found = false;
//    int rnn;
//    for (const auto& entry : myfile) {
//        if (data[2] == entry.first) {
//            found = true;
//            rnn=entry.second;
//            break;
//        }
//    }
//
//    string firstSkValue = extractHeader(SKlistfile);
//    if (found) {
//        int offset = calculateOffset(rnn);
//        int lastValue = getValueAfterLastDelimiter(SKlistfile, offset);
//        if (lastValue == -1) {
//            updateLastValue(SKlistfile, offset);
//        } else {
//            while (lastValue != -1) {
//                //cout<<"hello maya";
//                int newOffset = calculateOffset(lastValue);
//                lastValue = getValueAfterLastDelimiter(SKlistfile, newOffset);
//                if (lastValue == -1) {
//                    updateLastValue(SKlistfile, newOffset);
//                }
//            }
//        }
//        outFile2 << writer(3, firstSkValue) << "|" << writer(15, data[0]) << "|" << writer(3, "-1") << endl;
//        writeHeader(SKlistfile);
//
//    } else {
//        outFile << data[2] << "|"<< firstSkValue << endl;
//        outFile.close();
//        outFile2 << writer(3,firstSkValue) << "|"  << writer(15,data[0]) << "|"<< writer(3,"-1") << endl;
//        writeHeader(SKlistfile);
//    }


