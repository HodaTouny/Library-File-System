#include <bits/stdc++.h>
#include "IFilesSystem.cpp"
using namespace std;

int main() {
    ifstream file("myfile.txt");
    char ch;
    if (file.is_open()) {
        int offset = 65;  // Number of characters in the first line plus newline character
        file.seekg(offset, ios::beg);
        file.get(ch);
        cout << "the sixth character from the beginning of the file 0-based index: " << ch << endl;
    }
        return 0;
}
