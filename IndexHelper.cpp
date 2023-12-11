#include "IndexHelper.h"
//sort primary
void IndexHelper:: sortPairs(vector<pair<string, int>> &FileIndex){
    sort(FileIndex.begin(), FileIndex.end(),
         [](const pair<string, int>& a, const pair<string, int>& b) {
             return a.first < b.first;
         });
}
//sort secondary
void IndexHelper:: sort_Pairs(vector<pair<int, LinkedList<string>*>> &FileIndex) {
    sort(FileIndex.begin(), FileIndex.end(),
              [](const pair<int, LinkedList<string>*>& a, const pair<int, LinkedList<string>*>& b) {
                  return a.first < b.first;
              });
}

//extract second file secondary index header
string IndexHelper:: extractHeader(string fileName) {
    ifstream inputFile(fileName);
    if (!inputFile) {
        cerr << "Error opening file: " << fileName << "\n";
        return "";
    }
    string line;
    while (getline(inputFile, line)) {
        size_t underscorePos = line.find('_');
        if (underscorePos != string::npos) {
            string numberStr = line.substr(0, underscorePos);
            return numberStr;
        }
        return "";
    }
}

// for secondary index
int IndexHelper:: calculateFixedOffset(int rnn) {
    return 5 + (rnn * 23) + (rnn *2) + 2;
}
//for primary index
int IndexHelper:: calculateVariableLengthOffset(int previousRecordSize,int LastOffset){
    return LastOffset + previousRecordSize + 2;
}


//add underscores
string IndexHelper:: writer(int integer,string number){
    int underscoresNeeded = integer- number.length();
    for (int i = 0; i < underscoresNeeded; ++i) {
        number += "_";
    }
    return number;
}


//remove extra underscores
void IndexHelper:: removeUnderscores(string& str) {
    str.erase(remove(str.begin(), str.end(), '_'), str.end());
}

//bt2sm al Line
vector<string> IndexHelper::parseString(const string& inputString) {
    vector<string> result;
    stringstream ss(inputString);
    string item;
    while (getline(ss, item, '|')) {
        result.push_back(item);
    }
    return result;
}



bool IndexHelper:: binarySearch( vector<pair<string, int>>& fileIndex, string target) {
    int low = 0;
    int high = fileIndex.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (fileIndex[mid].first == target) {
            return true;
        } else if (fileIndex[mid].first < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return false;
}

//binary search return offset
int IndexHelper:: binarySearchInt(vector<pair<string, int>>& vec, string key) {
    int left = 0;
    int right = vec.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (vec[mid].first == key) {
            return vec[mid].second;
        }
        else if (vec[mid].first > key) {
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }
    return -1;
}

