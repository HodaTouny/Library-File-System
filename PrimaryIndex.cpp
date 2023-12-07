#include "PrimaryIndex.h"

vector<pair<string, int>> PrimaryIndex :: LoadIndexFile(string filename) {
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

void PrimaryIndex::uploadIndexFile(vector<pair<string, int>>& FileIndex, const string& filename) {
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

void PrimaryIndex:: deleteFromIndex(vector<pair<string, int>>& fileIndex, string targetString) {
    auto it = remove_if(fileIndex.begin(), fileIndex.end(),
                        [targetString](const pair<string, int>& element) {
                            return element.first == targetString;
                        });

    fileIndex.erase(it, fileIndex.end());
}

bool PrimaryIndex:: insertIntoIndex(vector<pair<string, int>>& FileIndex, string key,string fileName){
    int LastOffset = fileHelper.extractSecondValueFromFile(fileName);
    int offS = FileIndex[FileIndex.size()-1].second;
    int previousSize = previousRecordSize(fileName,offS);
    int offset = calculateVariableLengthOffset(previousSize,LastOffset);
    FileIndex.push_back(pair<string ,int>{key,offset});
    sortPairs(FileIndex);
    fileHelper.updateOffset(offset,fileName);
    return true;
}

int PrimaryIndex:: previousRecordSize(string filename,int offset){
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file." << "\n";
        return 1;
    }
    file.seekg(offset,ios::beg);
    string Line;
    getline(file,Line);
    string firstValue;
    for(int i=0;i<Line.size();i++){
        if(Line[i] == '|'){
            break;
        }
        firstValue+=Line[i];
    }
    file.close();
    return stoi(firstValue);
}

