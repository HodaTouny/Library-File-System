
#ifndef LIBRARY_FILE_SYSTEM_LIBRARYINTERFACE_H
#define LIBRARY_FILE_SYSTEM_LIBRARYINTERFACE_H

#include "LinkedList.h"
#include "AVAILSystem.h"
#include "IndexHelper.h"
#include"QueryProcessor.h"
class LibraryInterface{
public:
    LinkedList<string>AvailListAuthor;
    LinkedList<string>AvailListBook;
    vector<pair<string,int>>AuthorPK;
    vector<pair<string,int>>BookPK;
    vector<pair<string,int>>AuthorSKFirst;
    vector<pair<string,int>>BookSKFirst;
    vector<pair<int, LinkedList<string>*>>  AuthorSKSecond;
    vector<pair<int, LinkedList<string>*>> BookSKSecond;
    int Authorsheader;
    int Booksheader;
    void handleAddAuthor();
    void handleAddBook();
    void handleUpdateAuthorAddress();
    void handleUpdateBookTitle();
    void handleDeleteAuthor();
    void handleDeleteBook();
    void handlePrintAuthor();
    void handlePrintBook();
    void handleWriteQuery();


public:
    LibraryInterface();
    int menu();
    ~LibraryInterface();
};

#endif //LIBRARY_FILE_SYSTEM_LIBRARYINTERFACE_H
