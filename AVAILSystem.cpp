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
        availList.insertAtTail(line,false,"");
    }
    file.close();
    return availList;
}

void AVAILSystem::writeAvailToFile(LinkedList<string>& availList, string fileName) {
    ofstream file(fileName, ios::out);
    if (!file.is_open()) {
        cerr << "Error opening file for writing: " << fileName << "\n";
        return;
    }
    SLLNode<string>* current = availList.head;
    while (current != nullptr) {
        file << current->data << "\n";
        current = current->next;
    }
    file.close();
}
