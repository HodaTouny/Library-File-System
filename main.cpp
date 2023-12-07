#include <iostream>
#include <vector>
#include "SecondaryIndex.h"
using namespace std;

int main() {
    SecondaryIndex x;
    vector<pair<int, LinkedList<string>*>> ll = x.loadLinkedListFile("BookSKList.txt");
    for (auto& pair : ll) {
        cout << pair.first << " ";
        pair.second->print();
        cout << endl;
    }
    for (auto& pair : ll) {
        delete pair.second;
    }


    return 0;
}
