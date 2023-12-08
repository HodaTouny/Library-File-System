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
private:
    vector<pair<string,int>>AuthorPK;
    vector<pair<string,int>>BookPK;
    vector<pair<string,int>>AuthorSKFirst;
    vector<pair<int,LinkedList<string>*>>AuthorSKSecond;
    vector<pair<string,int>>BookSKFirst;
    vector<pair<int,LinkedList<string>*>>BookSKSecond;
public:
    void processQuery(string query,vector<pair<string,int>>AuthorPK,vector<pair<string,int>>BookPK,vector<pair<string,int>>AuthorSKFirst,vector<pair<int,LinkedList<string>*>>AuthorSKSecond,vector<pair<string,int>>BookSKFirst,vector<pair<int,LinkedList<string>*>>BookSKSecond);
    void searchFunction(string &tableName, string &project,  string &columnName,  string &value) ;
    void searchAuthors(string &project, string columnName,  string &value);
    void searchBooks( string &project,  string &columnName,  string &value) ;
    void parseQuery(const string& query,string& command, string& project,string& tableName, string& columnName, string& value);
    int binarySearch(const vector<pair<string, int>> arr, const string key);
    int binarySearch(const vector<pair<int, LinkedList<string>*>> arr, const int key);
    void printBookDetails(vector<string>& record,string project);
    void printAuthorDetails(vector<string>& record, string project);
};



#endif //LIBRARY_FILE_SYSTEM_QUERYPROCESSOR_H