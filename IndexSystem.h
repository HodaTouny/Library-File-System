
#ifndef LIBRARY_FILE_SYSTEM_INDEXSYSTEM_H
#define LIBRARY_FILE_SYSTEM_INDEXSYSTEM_H


class IndexSystem {
private:
    void sortPairs(vector<pair<string, int>> &FileIndex){
        sort(FileIndex.begin(), FileIndex.end(),
             [](const pair<string, int>& a, const pair<string, int>& b) {
                 return a.first < b.first;
             });
    }

public:
    //Load Index File Into Vector [main memory to use it easily]
    vector<pair<string, int>> LoadIndexFile(const string& filename) {
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

    //upload index file after all edits
    void uploadIndexFile(vector<pair<string, int>>& FileIndex, const string& filename) {
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

    //remove deleted record from the index
    void deleteFromIndex(vector<pair<string, int>>& fileIndex,string targetString) {
        auto it = remove_if(fileIndex.begin(), fileIndex.end(),
                                 [targetString](const pair<string, int>& element) {
                                     return element.first == targetString;
                                 });

        fileIndex.erase(it, fileIndex.end());
    }



    //insert record into the index
    bool insertIntoIndex(vector<pair<string, int>>& FileIndex,string key,int offset){
        FileIndex.push_back(pair<string ,int>{key,offset});
        sortPairs(FileIndex);
        return true;
    }



};


#endif //LIBRARY_FILE_SYSTEM_INDEXSYSTEM_H
