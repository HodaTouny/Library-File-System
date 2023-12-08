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
    if(binarySearch(FileIndex,key)){
        return false;
    }
    int LastOffset = fileHelper.extractSecondValueFromFile(fileName);
    int previousSize = previousRecordSize(fileName);
    int offset = calculateVariableLengthOffset(previousSize,LastOffset);
    FileIndex.push_back(pair<string ,int>{key,offset});
    sortPairs(FileIndex);
    fileHelper.updateOffset(offset,fileName);
    return true;
}
int PrimaryIndex:: previousRecordSize(string filename){
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file." << std::endl;
        return 1;
    }
    string lastLine,firstValue;
    string currentLine;
    getline(file,currentLine);
    while (getline(file, currentLine)) {
        lastLine = currentLine;
    }
    file.close();
    if(lastLine == ""){
        return 15;
    }
    for(int i=0;i<lastLine.size();i++){
        if(lastLine[i] == '|'){
            break;
        }
        firstValue+=lastLine[i];
    }
    file.close();
    return stoi(firstValue)+2;
}


