#ifndef LIBRARY_FILE_SYSTEM_INTERFACE_H
#define LIBRARY_FILE_SYSTEM_INTERFACE_H
#include "LinkedList.h"
#include "AVAILSystem.h"
#include "IndexHelper.h"
#include"QueryProcessor.h"
class LibraryInterface{
private:
    LinkedList<string>AvailListAuthor;
    LinkedList<string>AvailListBook;
    vector<pair<string,int>>AuthorPK;
    vector<pair<string,int>>BookPK;
    vector<pair<string,int>>AuthorSKFirst;
<<<<<<< HEAD
    vector<pair<string,int>>BookSKFirst;
    vector<pair<int, LinkedList<string>*>>  AuthorSKSecond;
    vector<pair<int, LinkedList<string>*>> BookSKSecond;
    int Authorsheader;
    int Booksheader;

=======
    vector<pair<int,LinkedList<string>*>>AuthorSKSecond;
    vector<pair<string,int>>BookSKFirst;
    vector<pair<int,LinkedList<string>*>>BookSKSecond;
>>>>>>> 4b0f23ef48c179d38044e1bddf37fd63d8d6359e
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
