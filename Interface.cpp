#include "Interface.h"
#include <bits/stdc++.h>
#include "PrimaryIndex.h"
#include "SecondaryIndex.h"
using namespace std;
AVAILSystem availSystem;
PrimaryIndex primaryIndex;
SecondaryIndex secondaryIndex;
EntityFiles entityFiles;
IndexHelper indexHelper;
string Author_ID ;
string Author_Name ;
string Address ;
string ISBN;
string Book_Title;
string AuthorData[]={Author_ID,Author_Name,Address};
string BookData[]={Author_ID,Book_Title,ISBN};
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
    do {
        cout << "Author ID (up to 15 characters): ";
        cin.ignore();
        getline(cin, Author_ID);
        if (Author_Name.length() > 15) {
            cout << "Error: Author ID should not exceed 15 characters. Please re-enter." << endl;
        }
    } while (Author_ID.length() > 15);

    do {
        cout << "Author Name (up to 30 characters): ";

        getline(cin, Author_Name);
        if (Author_Name.length() > 30) {
            cout << "Error: Author name should not exceed 30 characters. Please re-enter." << endl;
        }
    } while (Author_Name.length() > 30);

    do {
        cout << "Author Address (up to 30 characters): ";

        getline(cin, Address);
        if (Author_Name.length() > 30) {
            cout << "Error: Address should not exceed 30 characters. Please re-enter." << endl;
        }
    } while (Address.length() > 30);
    AuthorData[0] = Author_ID;
    AuthorData[2] = Author_Name;
    AuthorData[1] = Address;
    bool found =primaryIndex.insertIntoIndex(AuthorPK,AuthorData[0],"Authors.txt");
    if (found) {
        entityFiles.addRecord(AvailListAuthor, "Authors.txt", AuthorData);
        secondaryIndex.addRecordToSecondaryIndex(AuthorSKFirst, AuthorSKSecond, AuthorData, Authorsheader);
        cout<<"\n";
        for (const auto& pair : AuthorSKSecond) {
            std::cout << "F: " << pair.first << ",L: ";
            pair.second->print();
            std::cout << std::endl;
        }
    }
    else{
        cout<<" this user exist!!!";
    }


}

void LibraryInterface::handleAddBook() {
    do {
        cout << "Book ID (up to 15 characters): ";
        cin.ignore();
        getline(cin, ISBN);
        if (ISBN.length() > 15) {
            cout << "Error: Book ID should not exceed 15 characters. Please re-enter." << endl;
        }
    } while (ISBN.length() > 15);

    do {
        cout << "Book Title (up to 30 characters): ";

        getline(cin, Book_Title);
        if (Book_Title.length() > 30) {
            cout << "Error: Book name should not exceed 30 characters. Please re-enter." << endl;
        }
    } while (Book_Title.length() > 30);

    do {
        cout << "Author ID (up to 30 characters): ";

        getline(cin, Author_ID);
        if (Author_ID.length() > 15) {
            cout << "Error: Author ID should not exceed 30 characters. Please re-enter." << endl;
        }
    } while (Author_ID.length() > 15);

    BookData[0] = ISBN;
    BookData[1] = Book_Title;
    BookData[2] = Author_ID;
    bool found =primaryIndex.insertIntoIndex(BookPK,BookData[0],"Books.txt");
    if (found) {
        entityFiles.addRecord(AvailListBook, "Books.txt", BookData);
        secondaryIndex.addRecordToSecondaryIndex(BookSKFirst, BookSKSecond, BookData, Booksheader);
        cout<<"\n";
        for (const auto& pair : BookSKSecond) {
            std::cout << "F: " << pair.first << ",L: ";
            pair.second->print();
            std::cout << std::endl;
        }
    }
    else{
        cout<<" this user exist!!!";
    }
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
            //    string query;
            //    cout<<"Enter your query: ";
            //    cin.ignore();
            //    getline(cin,query);
            //    queryProcessor.processQuery(query,AuthorPK,BookPK);

//    cout<<"Enter your query: ";
//    cin.ignore();
//    getline(cin,query);
//    queryProcessor.processQuery(query,AuthorPK,BookPK,AuthorSKFirst,AuthorSKSecond,BookSKFirst,BookSKSecond);
}
void LibraryInterface::handlePrintAuthor() {
//    string authorID;
//    cout << "Enter Author ID: ";
//    cin >> authorID;
//    string project = "*";
//    string columnName = "AuthorID";
//    transform(columnName.begin(), columnName.end(), columnName.begin(), ::tolower);
//    queryProcessor.searchAuthors(project,columnName,authorID);
}
void LibraryInterface::handlePrintBook() {
//    string ISBN;
//    cout << "Enter ISBN: ";
//    cin >> ISBN;
//    string project = "*";
//    string columnName = "ISBN";
//    transform(columnName.begin(), columnName.end(), columnName.begin(), ::tolower);
//    queryProcessor.searchBooks(project,columnName,ISBN);

}
//
LibraryInterface::LibraryInterface() {
    AvailListAuthor = availSystem.readAvailFromFile("AVAILAuthors.txt");
    AvailListBook = availSystem.readAvailFromFile("AVAILBook.txt");
    AuthorPK = primaryIndex.LoadIndexFile("AuthorPK.txt");
    BookPK = primaryIndex.LoadIndexFile("BookPK.txt");
    AuthorSKFirst = primaryIndex.LoadIndexFile("AuthorsSKFirst.txt");
    BookSKFirst = primaryIndex.LoadIndexFile("BookSKFirst.txt");
    AuthorSKSecond = secondaryIndex.loadLinkedListFile("AuthorsSKSecond.txt");
    BookSKSecond = secondaryIndex.loadLinkedListFile("BookSKSecond.txt");
    Authorsheader = stoi(indexHelper.extractHeader("AuthorsSKSecond.txt"));
    Booksheader = stoi(indexHelper.extractHeader("BookSKSecond.txt"));
}
//
LibraryInterface::~LibraryInterface() {
    primaryIndex.uploadIndexFile(AuthorPK,"AuthorPK.txt");
    primaryIndex.uploadIndexFile(BookPK,"BookPK.txt");
    availSystem.writeAvailToFile(AvailListBook,"AVAILBook.txt");
    availSystem.writeAvailToFile(AvailListAuthor,"AVAILAuthor.txt");


}