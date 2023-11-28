
#ifndef LIBRARY_FILE_SYSTEM_INDEXSYSTEM_H
#define LIBRARY_FILE_SYSTEM_INDEXSYSTEM_H


class IndexSystem {
private:
public:
//    void deleteIndexRecord(map<string, int>& index, const string& pkey) {
//       auto it = index.find(pkey);
//        if (it != index.end()) {
//            int value = it->second;
//            index.erase(it);
//            for (auto& pair : index) {
//                if (pair.second > value) {
//                    pair.second++;
//                }
//            }
//        }
//    }

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
        file.close();

        sort(FileIndex.begin(), FileIndex.end(),
             [](const pair<string, int>& a, const pair<string, int>& b) {
                 return a.first < b.first;
             });

        return FileIndex;
    }

    };


#endif //LIBRARY_FILE_SYSTEM_INDEXSYSTEM_H
