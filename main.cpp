#include <bits/stdc++.h>
#include "IFilesSystem.h"
#include "IndexSystem.h"
using namespace std;
IFilesSystem x ;
//void addRecord(LinkedList<string>&AVAIL,string fileName,string data[],int dataSize){
//    int recordL = findRecordLength(data,dataSize);
//    int bestFit = findBestFit(AVAIL,recordL);
//    int header = x.extractFirstValueFromFile(fileName);
//
//    if (header == -1 || bestFit == 0) {
//        x.appendToFile(data, dataSize, fileName);
//    } else {
//        auto current = AVAIL.head;
//        while (current != nullptr) {
//            string availRecord = current->data;
//            string valueStr = extractValueBetweenBars(availRecord);
//            int value = stoi(valueStr);
//            if(value == bestFit) {
//                int offset;
//                size_t pos = availRecord.find("|");
//                offset = stoi(availRecord.substr(0, pos));
//                int size = stoi(availRecord.substr(pos + 1));
//                if (size == bestFit && AVAIL.getNextNodeDataPtr() == nullptr) {
//                    x.insertRecord(header, data, dataSize, fileName, size);
//                    x.updateHeader(offset,"Books.txt");
//                }else if (size == bestFit) {
//                    string *nextNodeDataPtr =AVAIL.getNextNodeDataPtr();
//                    if (nextNodeDataPtr != nullptr) {
//                        string nextRecord =  *nextNodeDataPtr;
//                        offset = stoi(nextRecord.substr(0, pos));
//                        x.insertRecord(offset, data, dataSize, fileName, size);
//                    }
//                }
//                AVAIL.removeNodeWithValue(availRecord);
//                return;
//            }
//            current = current->next;
//        }
//
//        }
//
//}


int main() {
    LinkedList<string > kk = x.AvailCreator("Books.txt");
    string maya[] = {"lemmm","tall","smmML"};
    string maya2[] = {"kem","ta","sm"};
    addRecord(kk,"Books.txt",maya,3);









    //To make Index Equation: headerSize +  i[previous record size] + [i*2]+2
    //To update index: offset from header + previous record size + 2

    return 0;
}
