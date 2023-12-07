#include "IndexHelper.h"
void IndexHelper:: sortPairs(vector<pair<string, int>> &FileIndex){
    sort(FileIndex.begin(), FileIndex.end(),
         [](const pair<string, int>& a, const pair<string, int>& b) {
             return a.first < b.first;
         });
}

string IndexHelper:: extractHeader(string fileName) {
    ifstream inputFile(fileName);
    if (!inputFile) {
        std::cerr << "Error opening file: " << fileName << "\n";
        return "";
    }
    string line;
    while (getline(inputFile, line)) {
        std::size_t underscorePos = line.find('_');
        if (underscorePos != string::npos) {
            std::string numberStr = line.substr(0, underscorePos);
            return numberStr;
        }
        return "";
    }
}
void IndexHelper:: updateLastValue(string fileName, int offset) {
    fstream file(fileName, ios::in | ios::out);
    if (!file.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return;
    }
    vector<string> record= fileSystem.loadRecord(offset,fileName);
    vector<string> Temp = record;
    record[0] = writer( 3,Temp[0]);
    record[1] = writer(15,Temp[1]);

    if (record.empty()) {
        cerr << "Error: no record found at the given offset." << std::endl;
        return;
    }
    string integer = extractHeader(fileName);
    string str= writer(3, integer);
    record.back() = str;
    file.seekp(offset);
    for (int i = 0; i < record.size(); ++i) {
        file << record[i];
        if (i < record.size() - 1) {
            file << "|";
        }
    }
    file << endl;
}


void IndexHelper:: writeHeader(string fileName) {
    fstream file(fileName, ios::in | ios::out);
    if (!file) {
        cerr << "Error opening file: " << fileName << "\n";
        return;
    }
    string number= extractHeader(fileName);
    string firstLine;
    getline(file, firstLine);
    int newHeader = stoi(number)+1;
    string Nheader= to_string(newHeader);
    int underscoresNeeded = 5 - Nheader.length();

    for (int i = 0; i < underscoresNeeded; ++i) {
        Nheader += "_";
    }
    file.seekp(0, ios::beg);
    file << Nheader;
    file.close();
}


int IndexHelper:: calculateFixedOffset(int rnn) {
    return 5 + (rnn * 23) + (rnn *2) + 2;
}
int getValueAfterLastDelimiter(const string& filePath, int offset) {
    ifstream file(filePath);

    if (!file) {
        cerr << "Error opening file: " << filePath << std::endl;
        return -1;
    }
    file.seekg(offset);
    string line;
    getline(file, line);
    file.close();
    size_t lastDelimiterPos = line.find_last_of('|');
    string valueStr = line.substr(lastDelimiterPos + 1);
    try {
        return stoi(valueStr);
    } catch (const invalid_argument& e) {

        return -1;
    }
}
string IndexHelper:: writer(int integer,string number){
    int underscoresNeeded = integer- number.length();
    for (int i = 0; i < underscoresNeeded; ++i) {
        number += "_";
    }
    return number;
}



void IndexHelper:: removeUnderscores(string& str) {
    str.erase(remove(str.begin(), str.end(), '_'), str.end());
}

vector<string> IndexHelper::parseString(const string& inputString) {
    vector<string> result;
    stringstream ss(inputString);
    string item;
    while (getline(ss, item, '|')) {
        result.push_back(item);
    }
    return result;
}