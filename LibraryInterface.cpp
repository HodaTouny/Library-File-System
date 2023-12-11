#include "LibraryInterface.h"
#include "PrimaryIndex.h"
#include "SecondaryIndex.h"
using namespace std;
AVAILSystem availSystem;
PrimaryIndex primaryIndex;
SecondaryIndex secondary;
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
                handleUpdateAuthorAddress();
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
    int found = primaryIndex.insertIntoIndex(AuthorPK,AuthorData[0],"Authors.txt");
    if (found != -1) {
        entityFiles.addRecord(AvailListAuthor, "Authors.txt", AuthorData);
        FilesHelper k; k.updateOffset(found,"Authors.txt");
        secondary.addRecordToSecondaryIndex(AuthorSKFirst, AuthorSKSecond, AuthorData, Authorsheader);
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
    int found =primaryIndex.insertIntoIndex(BookPK,BookData[0],"Books.txt");
    if (found != -1) {
        entityFiles.addRecord(AvailListBook, "Books.txt", BookData);
        FilesHelper k; k.updateOffset(found,"Books.txt");
        secondary.addRecordToSecondaryIndex(BookSKFirst, BookSKSecond, BookData, Booksheader);
    }
    else{
        cout<<" this user exist!!!";
    }
}

void LibraryInterface::handleUpdateBookTitle() {

    cout << "Book ID of Book To Update: ";
    cin.ignore();
    getline(cin, ISBN);
    do {
        cout << "New Book Title (up to 30 characters): ";
        getline(cin, Book_Title);
        if (Book_Title.length() > 30) {
            cout << "Error: Book name should not exceed 30 characters. Please re-enter." << endl;
        }
    } while (Book_Title.length() > 30);

    int offset = indexHelper.binarySearchInt(BookPK,ISBN);
    entityFiles.updateRecord(offset,Book_Title,"Books.txt",AvailListBook,BookPK,"BooksPK.txt");

}

void LibraryInterface::handleUpdateAuthorAddress() {
    cout << "Author ID To Update his name : ";
    cin.ignore();
    getline(cin, Author_ID);

    do {
        cout << "New Author Address (up to 30 characters): ";
        getline(cin, Author_Name);
        if (Author_Name.length() > 30) {
            cout << "Error: Author Address should not exceed 30 characters. Please re-enter." << endl;
        }
    } while (Author_Name.length() > 30);

    int offset = indexHelper.binarySearchInt(AuthorPK,Author_ID);
    entityFiles.updateRecord(offset,Author_Name,"Authors.txt",AvailListAuthor,AuthorPK,"Authors.txt");

}

void LibraryInterface::handleDeleteBook() {
    cout << "Book ID to delete: ";
    cin.ignore();
    getline(cin, ISBN);
    int offset = indexHelper.binarySearchInt(BookPK,ISBN);
    if(offset == -1){
        cout<<"This Book is not available now,it may be deleted before or doesn't add\n";
    }else {
        vector<string> record = entityFiles.loadRecord(offset, "Books.txt");
        entityFiles.deleteRecord(offset, "Books.txt",AvailListBook);
        secondary.deleteFromSecondaryIndex(BookSKFirst, BookSKSecond, ISBN, record[2]);
        primaryIndex.deleteFromIndex(BookPK, ISBN);
    }
}



void LibraryInterface::handleDeleteAuthor() {

    cout << "Author ID to delete: ";
    cin.ignore();
    getline(cin, Author_ID);
    int offset = indexHelper.binarySearchInt(AuthorPK,Author_ID);
    if(offset == -1){
        cout<<"This Author is not available now,it may be deleted before or doesn't add\n";
    }else {
        vector<string> record = entityFiles.loadRecord(offset, "Authors.txt");
        secondary.deleteFromSecondaryIndex(AuthorSKFirst, AuthorSKSecond, Author_ID, record[3]);
        entityFiles.deleteRecord(offset, "Authors.txt",AvailListAuthor);
        primaryIndex.deleteFromIndex(AuthorPK, Author_ID);
    }
}



void LibraryInterface::handleWriteQuery() {
    string query;
    cout<<"Enter your query: ";
    cin.ignore();
    getline(cin,query);
    queryProcessor.processQuery(query,AuthorPK,BookPK,AuthorSKFirst,AuthorSKSecond,BookSKFirst,BookSKSecond);
}

void LibraryInterface::handlePrintAuthor() {
    string authorID;
    cout << "Enter Author ID: ";
    cin >> authorID;
    string project = "*";
    string query = "SELECT * FROM Authors WHERE AuthorID = '"+ authorID+"'";
    queryProcessor.processQuery(query,AuthorPK,BookPK,AuthorSKFirst,AuthorSKSecond,BookSKFirst,BookSKSecond);
}

void LibraryInterface::handlePrintBook() {
    string ISBN;
    cout << "Enter ISBN: ";
    cin >> ISBN;
    string query = "SELECT * FROM Books WHERE ISBN = '"+ ISBN+"'";
    queryProcessor.processQuery(query,AuthorPK,BookPK,AuthorSKFirst,AuthorSKSecond,BookSKFirst,BookSKSecond);
}



LibraryInterface::LibraryInterface() {
    AvailListAuthor = availSystem.readAvailFromFile("AVAILAuthor.txt");
    AvailListBook = availSystem.readAvailFromFile("AVAILBook.txt");

    AuthorPK = primaryIndex.LoadIndexFile("AuthorPK.txt");
    BookPK = primaryIndex.LoadIndexFile("BookPK.txt");

    AuthorSKFirst = primaryIndex.LoadIndexFile("AuthorsSKFirst.txt");
    BookSKFirst = primaryIndex.LoadIndexFile("BookSKFirst.txt");

    AuthorSKSecond = secondary.loadLinkedListFile("AuthorsSKSecond.txt");
    BookSKSecond = secondary.loadLinkedListFile("BookSKSecond.txt");
    Authorsheader = stoi(indexHelper.extractHeader("AuthorsSKSecond.txt"));
    Booksheader = stoi(indexHelper.extractHeader("BookSKSecond.txt"));
}

LibraryInterface::~LibraryInterface() {
    primaryIndex.uploadIndexFile(AuthorPK,"AuthorPK.txt");
    primaryIndex.uploadIndexFile(BookPK,"BookPK.txt");

    availSystem.writeAvailToFile(AvailListBook,"AVAILBook.txt");
    availSystem.writeAvailToFile(AvailListAuthor,"AVAILAuthor.txt");

    secondary.writeToFile(AuthorSKFirst,AuthorSKSecond,"AuthorsSKFirst.txt","AuthorsSKSecond.txt",Authorsheader);
    secondary.writeToFile(BookSKFirst,BookSKSecond,"BookSKFirst.txt","BookSKSecond.txt",Booksheader);

    vector<pair<int,string>> Author= secondary.readAndSortFile("AuthorsSKSecond.txt");
    secondary.writeToToFile("AuthorsSKSecond.txt",Author);
    vector<pair<int,string>> Book= secondary.readAndSortFile("BookSKSecond.txt");
    secondary.writeToToFile("BookSKSecond.txt",Book);

}