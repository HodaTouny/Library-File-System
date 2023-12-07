#include <iostream>
#include <vector>
#include "Interface.h"
#include "QueryProcessor.h"

using namespace std;

int main() {
    IndexSystem indexSystem;

    vector<pair<string, int>> firstFileIndex = {{"m", 0}, {"ahmed", 2}, {"yasser", 4}};

    LinkedList<string>* ll = new LinkedList<string>();
    LinkedList<string>* ll2 = new LinkedList<string>();
    LinkedList<string>* ll3 = new LinkedList<string>();
    ll->insertAtHead("book1");
    ll->insertAtTail("book2");
    ll->insertAtTail("book3");

    ll2->insertAtTail("book4");

    ll2->insertAtHead("book5");
    ll3->insertAtHead("book6");

    vector<pair<int, LinkedList<string>*>> secondFileIndex = {
            {0, ll},
            {2, ll2},
            {4, ll3}
    };

    string target = "book4";
    string targetName = "ahmed";
    indexSystem.deleteFromSecondaryIndex(firstFileIndex,secondFileIndex,target, targetName);
    for (auto& pair : firstFileIndex) {
        cout << pair.first << " " << pair.second << endl;
    }
    for (auto& pair : secondFileIndex) {
        cout << pair.first << " ";
        pair.second->print();
        cout << endl;
    }
    for (auto& pair : secondFileIndex) {
        delete pair.second;
    }

    return 0;
}
