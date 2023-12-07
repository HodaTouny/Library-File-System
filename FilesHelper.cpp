#include "FilesHelper.h"

void FilesHelper:: removeUnderscores(string& str) {
    str.erase(remove(str.begin(), str.end(), '_'), str.end());
}


string FilesHelper:: to_string(int value) {
    ostringstream oss;
    oss << value;
    return oss.str();
}

string FilesHelper:: concat(string str1,string str2) {
    return str1 + "|" + str2;
}


int FilesHelper::extractFirstValueFromFile(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << "\n";
        return -1;
    }

    string line;
    getline(file, line);
    file.close();

    size_t pipePos = line.find('|');
    if (pipePos != string::npos) {
        string numberStr = line.substr(0, pipePos);
        istringstream iss(numberStr);
        int firstValue;
        iss >> firstValue;
        if (iss.fail()) {
            cerr << "Invalid number format: " << numberStr << "\n";
            return -1;
        }
        return firstValue;
    }
    return -1;
}

int FilesHelper::extractSecondValueFromFile(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << "\n";
        return -1;
    }

    string line;
    getline(file, line);
    file.close();

    size_t pipePos = line.find('|');
    if (pipePos != string::npos) {
        string numberStr = line.substr(pipePos + 1);
        istringstream iss(numberStr);
        int secondValue;
        iss >> secondValue;
        if (iss.fail()) {
            cerr << "Invalid number format: " << numberStr << "\n";
            return -1;
        }
        return secondValue;
    }

    return 17;
}



string FilesHelper::formatNumber(int value, int digits) {
    string formatted = to_string(value);
    if (formatted.length() < digits) {
        formatted = formatted + string(digits - formatted.length(), '_');
    } else if (formatted.length() > digits) {
        formatted = formatted.substr(0, digits);
    }
    return formatted;
}

void FilesHelper::updateOffset(int offset,string fileName) {
    fstream file(fileName, ios::in | ios::out);
    if (!file) {
        cerr << "Error opening file: " << fileName << "\n";
        return;
    }
    string existingHeader;
    getline(file, existingHeader);
    string LastDeletedOffset  = existingHeader.substr(0, 9);
    string formattedOffset = formatNumber(offset, 5);
    string newHeader = LastDeletedOffset + "|" +  formattedOffset;
    file.seekp(0, ios::beg);
    file <<newHeader<<"\n";
    file.close();
}
void FilesHelper:: updateHeader(int number, string fileName) {
    fstream file(fileName, ios::in | ios::out);
    if (!file) {
        cerr << "Error opening file: " << fileName << "\n";
        return;
    }
    string existingHeader;
    getline(file, existingHeader);
    string firstNineDigits = existingHeader.substr(10, 5);
    string formattedNumber  = formatNumber(number, 9);
    string newHeader = formattedNumber + "|" + firstNineDigits ;
    file.seekp(0, ios::beg);
    file <<newHeader<<"\n";
    file.close();
}


vector<int> FilesHelper::extractSize(LinkedList<string>& availList) {
    vector<int> sizes;
    SLLNode<string>* current = availList.head;
    while (current) {
        string availRecord = current->data;
        size_t pos = availRecord.find('|');
        if (pos != string::npos) {
            int size = stoi(availRecord.substr(pos+1));
            sizes.push_back(size);
        }
        current = current->next;
    }
    sort(sizes.begin(), sizes.end());
    return sizes;
}

int FilesHelper::findRecordLength(string data[], int dataSize){
    int recordLength = 0;
    for (int i = 0; i < dataSize; i++) {
        recordLength += data[i].size();
    }
    recordLength += dataSize;
    return recordLength;
}
int FilesHelper:: findBestFit(LinkedList<string>&AVAIL,int recordLength){
    vector<int> sizes = extractSize(AVAIL);
    int bestFit = 0;
    for (int size : sizes) {
        if (recordLength <= size) {
            bestFit = size;
            break;
        }
    }
    return bestFit;
}


string FilesHelper::extractValueBetweenBars( string input) {
    size_t startPos = input.find('|') + 1;
    if (startPos != string::npos ) {
        string valueStr = input.substr(startPos, input.size() - startPos);
        return valueStr;
    }
    return "";
}
string FilesHelper::updateNextNodeData(string x, string secondString) {
    size_t pos = x.find('|');
    if (pos == string::npos) {
        return x;
    }
    size_t secondPos = secondString.find('|');
    if (secondPos != string::npos) {
        return x.substr(0, pos + 1) + secondString.substr(secondPos + 1);
    } else {
        return x;
    }
}


void FilesHelper:: appendToFile(const string data[], int dataSize,  string fileName) {
    int recordLength = 0;
    ofstream outFile(fileName, ios::app);
    if (!outFile.is_open()) {
        cerr << "Error opening file: " << fileName << "\n";
        return;
    }
    for (int i = 0; i < dataSize; i++) {
        recordLength += data[i].size();
    }
    recordLength += dataSize;
    outFile << recordLength;
    for (int i = 0; i < dataSize; i++) {
        outFile << "|" << data[i];
    }
    outFile << "\n";
    outFile.close();
}

void FilesHelper:: insertRecord(int offset, const string data[], int dataSize,  string fileName, int oldSize) {
    fstream file(fileName, ios::in | ios::out);
    if (!file) {
        cerr << "Error opening file: " << fileName << endl;
        return;
    }
    file.seekp(offset, ios::beg);
    int recordLength = 0;
    for (int i = 0; i < dataSize; i++) {
        recordLength += data[i].size();
    }
    recordLength += dataSize;
    file << recordLength;
    for (int i = 0; i < dataSize; i++) {
        file << "|" << data[i];
    }
    int underscoresNeeded = oldSize - recordLength;
    string underscores;
    for (int i = 0; i <=underscoresNeeded; ++i) {
        underscores += "_";
    }
    file << underscores;
    file.close();
}

