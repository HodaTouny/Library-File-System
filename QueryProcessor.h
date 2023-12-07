#ifndef LIBRARY_FILE_SYSTEM_QUERYPROCESSOR_H
#define LIBRARY_FILE_SYSTEM_QUERYPROCESSOR_H



#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include"IndexHelper.h"
#include "AVAILSystem.h"
#include "bits/stdc++.h"
using namespace std;

class QueryProcessor {
public:
    void processQuery( string& query);
    void searchFunction( string &tableName, string &project,  string &columnName,  string &value) ;
    void searchAuthors( string &project, string columnName,  string &value);
    void searchBooks( string &project,  string &columnName,  string &value) ;
    void parseQuery(const string& query,string& command, string& project,string& tableName, string& columnName, string& value);
    int binarySearch(const vector<pair<string, int>>& arr, const string& key);
    void printBookDetails(vector<string>& record,string project);
    void printAuthorDetails(vector<string>& record, string project);
};



#endif //LIBRARY_FILE_SYSTEM_QUERYPROCESSOR_H
