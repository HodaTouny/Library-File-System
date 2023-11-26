
#ifndef LIBRARY_FILE_SYSTEM_INDEXSYSTEM_H
#define LIBRARY_FILE_SYSTEM_INDEXSYSTEM_H


class IndexSystem {
private:
public:
    void deleteIndexRecord(map<string, int>& index, const string& pkey) {
       auto it = index.find(pkey);
        if (it != index.end()) {
            int value = it->second;
            index.erase(it);
            for (auto& pair : index) {
                if (pair.second > value) {
                    pair.second++;
                }
            }
        }
    }



};


#endif //LIBRARY_FILE_SYSTEM_INDEXSYSTEM_H
