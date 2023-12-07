#include "AVAILSystem.h"

LinkedList<string> AVAILSystem:: readAvailFromFile(string fileName) {
    LinkedList<string> availList;
    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "Error opening file for reading: " << fileName << "\n";
        return availList;
    }
    string line;
    while (getline(file, line)) {
        availList.insertAtTail(line);
    }
    file.close();
    return availList;
}


string AVAILSystem::AvailCreator(string fileName, int offset) {
    LinkedList<string> availList;
    ifstream file(fileName, ios::in);
    if (!file.is_open()) {
        cerr << "Error opening file for reading: " << fileName << "\n";
        return "";
    }
    file.seekg(offset);
    string line;
    string extractedData;
    getline(file, line);
    size_t startPos = 1;
    cout<<line<<"\n";
    size_t firstPos = line.find('|', startPos);
    if (firstPos != string::npos) {
        size_t secondPos = line.find('|', firstPos + 1);
        if (secondPos != string::npos) {
            extractedData = line.substr(startPos, secondPos - startPos);
        }
    }
    cout << extractedData;
    file.close();
    return extractedData;
}

void AVAILSystem::writeAvailToFile(const LinkedList<string>& availList, const string& fileName) {
    ofstream file(fileName, ios::out);
    if (!file.is_open()) {
        cerr << "Error opening file for writing: " << fileName << "\n";
        return;
    }
    SLLNode<string>* current = availList.head;
    while (current) {
        file << current->data << "\n";
        current = current->next;
    }
    file.close();
}