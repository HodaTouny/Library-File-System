#include "Interface.h"
#include <bits/stdc++.h>
using namespace std;
IFilesSystem fileSystemClass;
IndexSystem indexSystem;
QueryProcessor queryProcessor;
int LibraryInterface::menu() {
    while (true) {
        cout << "Menu:\n"
                  << "1. Add New Author\n"
                  << "2. Add New Book\n"
                  << "3. Update Author Name (Author ID)\n"
                  << "4. Update Book Title (ISBN)\n"
                  << "5. Delete Book (ISBN)\n"
                  << "6. Delete Author (Author ID)\n"
                  << "7. Print Author (Author ID)\n"
                  << "8. Print Book (ISBN)\n"
                  << "9. Write Query\n"
                  << "10. Exit\n";

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: {
                handleAddAuthor();
                break;
            }
            case 2: {
                handleAddBook();
                break;
            }
            case 3: {
                handleUpdateAuthorName();
                break;
            }
            case 4: {
                handleUpdateBookTitle();
             break;
            }
            case 5: {
                handleDeleteBook();
                break;
            }
            case 6: {
                handleDeleteAuthor();
                break;
            }
            case 7: {
                handlePrintAuthor();
                break;
            }
            case 8: {
                handlePrintBook();
                break;
            }
            case 9: {
                handleWriteQuery();
                cout<<"Operation Done Successfully\n";
                break;
            }
            case 10: {
                cout << "Exiting the program.\n";
                return 0;
            }
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

}

void LibraryInterface::handleAddAuthor() {

}

void LibraryInterface::handleAddBook() {

}

void LibraryInterface::handleUpdateBookTitle() {

}

void LibraryInterface::handleUpdateAuthorName() {

}

void LibraryInterface::handleDeleteBook() {

}



void LibraryInterface::handleDeleteAuthor() {

}

void LibraryInterface::handleWriteQuery() {
    string query;
    cout<<"Enter your query: ";
    cin.ignore();
    getline(cin,query);
    queryProcessor.processQuery(query);
}
void LibraryInterface::handlePrintAuthor() {
    string authorID;
    cout << "Enter Author ID: ";
    cin >> authorID;
    string project = "*";
    string columnName = "AuthorID";
    transform(columnName.begin(), columnName.end(), columnName.begin(), ::tolower);
    queryProcessor.searchAuthors(project,columnName,authorID);
}
void LibraryInterface::handlePrintBook() {
    string ISBN;
    cout << "Enter ISBN: ";
    cin >> ISBN;
    string project = "*";
    string columnName = "ISBN";
    transform(columnName.begin(), columnName.end(), columnName.begin(), ::tolower);
    queryProcessor.searchBooks(project,columnName,ISBN);

}

LibraryInterface::LibraryInterface() {
    AvailListAuthor = fileSystemClass.readAvailFromFile("Authors.txt");
    AvailListBook = fileSystemClass.readAvailFromFile("Books.txt");
    AuthorPK = indexSystem.LoadIndexFile("Authors.txt");
    BookPK = indexSystem.LoadIndexFile("Books.txt");
}

LibraryInterface::~LibraryInterface() {
    indexSystem.uploadIndexFile(AuthorPK,"Authors.txt");
    indexSystem.uploadIndexFile(BookPK,"Books.txt");
    fileSystemClass.writeAvailToFile(AvailListBook,"AVAILBook.txt");
    fileSystemClass.writeAvailToFile(AvailListAuthor,"AVAILAuthor.txt");

}
