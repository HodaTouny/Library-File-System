#include "QueryProcessor.h"
#include <algorithm>
#include <iostream>
#include <sstream>
IFilesSystem filesSystem1;
IndexSystem indexSystem1;
vector<pair<string, int>> AuthorPK = indexSystem1.LoadIndexFile("AuthorPK.txt");
//vector<pair<string, int>> AuthorName = indexSystem.LoadIndexFile("AuthorName.txt");
vector<pair<string, int>> BookPK = indexSystem1.LoadIndexFile("BookPK.txt");
//vector<pair<string, int>> AuthorID = indexSystem.LoadIndexFile("AuthorID.txt");
void QueryProcessor::processQuery(string &query) {
    string command, project,tableName, columnName, value;
    transform(query.begin(), query.end(), query.begin(), ::tolower);
//    cout<<"query:"<<query<<endl;
    parseQuery(query, command,project, tableName, columnName, value);
//    cout<<"command:"<<command<<endl;
//    cout<<"project:"<<project<<endl;
//    cout<<"tableName:"<<tableName<<endl;
//    cout<<"columnName:"<<columnName<<endl;
//    cout<<"value:"<<value<<endl;
    if (command == "select") {
        searchFunction(tableName,project,columnName,value);
    } else {
        cout << "Unsupported command: " << command << endl;
    }
}

void QueryProcessor::searchFunction( string &tableName, string &project,  string &columnName, string &value)  {
    string lowercaseTableName = tableName;
    transform(lowercaseTableName.begin(), lowercaseTableName.end(), lowercaseTableName.begin(), ::tolower);
    if (lowercaseTableName == "authors") {
        searchAuthors(project,columnName,value);
    } else if (lowercaseTableName == "books") {
        searchBooks(project,columnName,value);
    } else {
        cout << "Unsupported table: " << tableName << endl;
    }
}


void QueryProcessor::searchAuthors( string &project, string columnName,  string &value) {
    columnName.erase(std::remove_if(columnName.begin(), columnName.end(), ::isspace), columnName.end());
    if (columnName == "authorid") {
        int index = binarySearch(AuthorPK, value);
        if (index != -1) {
            int offset = AuthorPK[index].second;
            vector<string> record = filesSystem1.loadRecord(offset, "Authors.txt");
            printAuthorDetails(record, project);
        } else {
            cout << "Author with AuthorID '" << value << "' not found." << endl;
        }
    }
//    else if (columnName == "authorname") {
//        int index = binarySearch(AuthorName, value);
//        if (index != -1) {
//            int offset = AuthorName[index].second;
//            vector<string> record = filesSystem1.loadRecord(offset, "Authors.txt");
//            printAuthorDetails(record, project);
//        } else {
//            cout << "Author with AuthorName '" << value << "' not found." << endl;
//        }
//    }
    else {
        cout << "Unsupported column for Authors: " << columnName << endl;
    }
}

void QueryProcessor::searchBooks( string &project,  string &columnName,  string &value) {
    columnName.erase(remove_if(columnName.begin(), columnName.end(), ::isspace), columnName.end());
    if (columnName == "isbn") {
        int index = binarySearch(BookPK, value);
        if (index != -1) {
            int offset = BookPK[index].second;
            vector<string> record = filesSystem1.loadRecord(offset, "Books.txt");
            printBookDetails(record, project);
        } else {
            cout << "Book with ISBN '" << value << "' not found." << endl;
        }
    }
//    else if (columnName == "authorid") {
//        int index = binarySearch(AuthorID, value);
//        if (index != -1) {
//            int offset = AuthorID[index].second;
//            vector<string> record = filesSystem1.loadRecord(offset, "Books.txt");
//            printBookDetails(record, project);
//        } else {
//            cout << "Books with AuthorID '" << value << "' not found." << endl;
//        }
//    }
    else {
        cout << "Unsupported column for Books: " << columnName << endl;
    }
}


void QueryProcessor::parseQuery(const string &query, string &command,string & project, string &tableName, string &columnName,
                                string &value) {
    size_t pos = query.find(" ");
    command = query.substr(0, pos);

    pos = query.find("select") + 7;
    size_t pos2 = query.find("from");
    project = query.substr(pos, pos2 - pos);

    pos = query.find("from") + 4;
    pos2 = query.find("where");
    tableName = query.substr(pos, pos2 - pos);

    size_t startPos = tableName.find_first_not_of(" ");
    size_t endPos = tableName.find_last_not_of(" ");

    if (startPos != string::npos && endPos != string::npos) {
        tableName = tableName.substr(startPos, endPos - startPos + 1);
    } else {
        tableName = "";
    }

    pos = query.find(" ", pos2) + 1;
    pos2 = query.find("=", pos);
    columnName = query.substr(pos, pos2 - pos);

    pos = query.find("'") +1;
    value = query.substr(pos, query.length() - pos-1);
}



int QueryProcessor::binarySearch(const vector<pair<string, int>> &arr, const string &key) {
    int left = 0;
    int right = arr.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid].first == key) {
            return mid;
        } else if (arr[mid].first < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1;
}
void QueryProcessor::printBookDetails(vector<string> &record, string project) {
    project.erase(remove_if(project.begin(), project.end(), ::isspace), project.end());
    if (project == "all" || project == "*") {
        cout << "ISBN: " << record[1] << endl;
        cout << "Title: " << record[2] << endl;
        cout << "Author ID: " << record[3] << endl;
    } else {
        istringstream iss(project);
        string attribute;
        while (getline(iss, attribute, ',')) {
            if (attribute == "isbn") {
                cout << "ISBN: " << record[1] << endl;
            } else if (attribute == "title") {
                cout << "Title: " << record[2] << endl;
            } else if (attribute == "authorid") {
                cout << "Author ID: " << record[3] << endl;
            } else {
                cout << "Unsupported attribute for Books: " << attribute << endl;
            }
        }
    }
}

void QueryProcessor::printAuthorDetails(vector<string> &record, string project) {
    project.erase(remove_if(project.begin(), project.end(), ::isspace), project.end());
    if (project == "all" || project == "*") {
        cout << "Author ID: " << record[1] << endl;
        cout << "Author Name: " << record[2] << endl;
        cout << "Author Address: " << record[3] << endl;
    } else {
        istringstream iss(project);
        string attribute;
        while (getline(iss, attribute, ',')) {
            if (attribute == "authorid") {
                cout << "Author ID: " << record[1] << endl;
            } else if (attribute == "authorname") {
                cout << "Author Name: " << record[2] << endl;
            } else if (attribute == "address") {
                cout << "Author Address: " << record[3] << endl;
            } else {
                cout << "Unsupported attribute for Authors: " << attribute << endl;
            }
        }
    }
}
