//#include <bits/stdc++.h>
//#include "QueryProcessor.h"
//#include "FilesHelper.h"
//#include "EntityFiles.h"
//#include "IndexHelper.h"
//#include "PrimaryIndex.h"
//#include "SecondaryIndex.h"
//EntityFiles entityFiles;
//
//void QueryProcessor::processQuery(string query,vector<pair<string,int>>authorPK,vector<pair<string,int>>bookPK) {
//    if (query.empty()) {
//        cout << "Query is empty." << endl;
//        return;
//    }
//    AuthorPK= authorPK;
//    BookPK= bookPK;
//    string command, project,tableName, columnName, value;
//    transform(query.begin(), query.end(), query.begin(), ::tolower);
//    parseQuery(query, command,project, tableName, columnName, value);;
//}
//void QueryProcessor::parseQuery(const string &query, string &command, string &project, string &tableName, string &columnName, string &value) {
//    size_t pos = query.find_first_not_of(" ");
//    command = query.substr(pos, query.find(" ", pos) - pos);
//    command.erase(remove_if(command.begin(), command.end(), ::isspace), command.end());
//    pos = query.find("select", pos) + 7;
//    size_t pos2 = query.find("from", pos);
//    if (pos2 == string::npos) {
//        cout << "Error: 'from' not found in the query." << endl;
//        return;
//    }
//    project = query.substr(pos, pos2 - pos);
//    project.erase(remove_if(project.begin(), project.end(), ::isspace), project.end());
//    if (project.empty()) {
//        cout << "Column to project is empty." << endl;
//        return;
//    }
//    pos = pos2 + 4;
//    pos2 = query.find("where", pos);
//
//    if (pos2 == string::npos) {
//        cout << "Error: 'where' not found in the query." << endl;
//        return;
//    }
//    tableName = query.substr(pos, pos2 - pos);
//    tableName.erase(remove_if(tableName.begin(), tableName.end(), ::isspace), tableName.end());
//    if (tableName.empty()) {
//        cout << "Table name is empty." << endl;
//        return;
//    }
//
//    pos = query.find(" ", pos2) + 1;
//    pos2 = query.find(" ", pos);
//    columnName = query.substr(pos, pos2 - pos);
//    if (columnName.empty()) {
//        cout << "Column name to search with is empty." << endl;
//        return;
//    }
//    pos = query.find("=", pos2) + 1;
//    size_t startQuote = query.find_first_of("\"'", pos);
//    size_t endQuote = query.find_first_of("\"'", startQuote + 1);
//
//    if (startQuote != string::npos && endQuote != string::npos) {
//        value = query.substr(startQuote + 1, endQuote - startQuote - 1);
//        if (value.empty()) {
//            cout << "Value to search with is empty." << endl;
//            return;
//        }
//        columnName.erase(remove_if(columnName.begin(), columnName.end(), ::isspace), columnName.end());
//        value.erase(remove_if(value.begin(), value.end(), ::isspace), value.end());
//        searchFunction(tableName, project, columnName, value);
//    } else {
//        cout << "Value to search with is not enclosed in double quotes." << endl;
//        return;
//    }
//}
//
//
//void QueryProcessor::searchFunction(string &tableName, string &project,  string &columnName, string &value)  {
//    string lowercaseTableName = tableName;
//    transform(lowercaseTableName.begin(), lowercaseTableName.end(), lowercaseTableName.begin(), ::tolower);
//    if (lowercaseTableName == "authors") {
//        searchAuthors(project,columnName,value);
//    } else if (lowercaseTableName == "books") {
//        searchBooks(project,columnName,value);
//    } else {
//        cout << "Unsupported table: " << tableName << endl;
//    }
//}
//
//
//void QueryProcessor::searchAuthors(string &project, string columnName,  string &value) {
//    columnName.erase(std::remove_if(columnName.begin(), columnName.end(), ::isspace), columnName.end());
//    if (columnName == "authorid") {
//        int index = binarySearch(AuthorPK, value);
//        if (index != -1) {
//            int offset = AuthorPK[index].second;
//            vector<string> record = entityFiles.loadRecord(offset, "Authors.txt");
//            printAuthorDetails(record, project);
//        } else {
//            cout << "Author with AuthorID '" << value << "' not found." << endl;
//        }
//    }
//    else {
//        cout << "Unsupported column for Authors: " << columnName << endl;
//    }
//}
//
//void QueryProcessor::searchBooks(string &project,  string &columnName,  string &value) {
//    columnName.erase(remove_if(columnName.begin(), columnName.end(), ::isspace), columnName.end());
//    if (columnName == "isbn") {
//        int index = binarySearch(BookPK, value);
//        if (index != -1) {
//            int offset = BookPK[index].second;
//            vector<string> record = entityFiles.loadRecord(offset, "Books.txt");
//            printBookDetails(record, project);
//        } else {
//            cout << "Book with ISBN '" << value << "' not found." << endl;
//        }
//    }
//    else {
//        cout << "Unsupported column for Books: " << columnName << endl;
//    }
//}
//
//
//int QueryProcessor::binarySearch(const vector<pair<string, int>> arr, const string key) {
//    int left = 0;
//    int right = arr.size() - 1;
//
//    while (left <= right) {
//        int mid = left + (right - left) / 2;
//
//        if (arr[mid].first == key) {
//            return mid;
//        } else if (arr[mid].first < key) {
//            left = mid + 1;
//        } else {
//            right = mid - 1;
//        }
//    }
//
//    return -1;
//}
//void QueryProcessor::printBookDetails(vector<string> &record, string project) {
//    project.erase(remove_if(project.begin(), project.end(), ::isspace), project.end());
//    if (project == "all" || project == "*") {
//        cout << "ISBN: " << record[1] << endl;
//        cout << "Title: " << record[2] << endl;
//        cout << "Author ID: " << record[3] << endl;
//    } else {
//        istringstream iss(project);
//        string attribute;
//        while (getline(iss, attribute, ',')) {
//            if (attribute == "isbn") {
//                cout << "ISBN: " << record[1] << endl;
//            } else if (attribute == "title") {
//                cout << "Title: " << record[2] << endl;
//            } else if (attribute == "authorid") {
//                cout << "Author ID: " << record[3] << endl;
//            } else {
//                cout << "Unsupported attribute for Books: " << attribute << endl;
//            }
//        }
//    }
//}
//
//void QueryProcessor::printAuthorDetails(vector<string> &record, string project) {
//    project.erase(remove_if(project.begin(), project.end(), ::isspace), project.end());
//    if (project == "all" || project == "*") {
//        cout << "Author ID: " << record[1] << endl;
//        cout << "Author Name: " << record[2] << endl;
//        cout << "Author Address: " << record[3] << endl;
//    } else {
//        istringstream iss(project);
//        string attribute;
//        while (getline(iss, attribute, ',')) {
//            if (attribute == "authorid") {
//                cout << "Author ID: " << record[1] << endl;
//            } else if (attribute == "authorname") {
//                cout << "Author Name: " << record[2] << endl;
//            } else if (attribute == "address") {
//                cout << "Author Address: " << record[3] << endl;
//            } else {
//                cout << "Unsupported attribute for Authors: " << attribute << endl;
//            }
//        }
//    }
//}