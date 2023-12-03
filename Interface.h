#ifndef LIBRARY_FILE_SYSTEM_INTERFACE_H
#define LIBRARY_FILE_SYSTEM_INTERFACE_H
#include "LinkedList.h"
#include "IFilesSystem.h"
#include "IndexSystem.h"
class LibraryInterface{
private:
    LinkedList<string>AvailListAuthor;
    LinkedList<string>AvailListBook;
    vector<pair<string,int>>AuthorPK;
    vector<pair<string,int>>BookPK;
    void handleAddAuthor();
    void handleAddBook();
    void handleUpdateAuthorName();
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

#endif //LIBRARY_FILE_SYSTEM_INTERFACE_H
