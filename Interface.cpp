#include "Interface.h"
IFilesSystem fileSystemClass;
IndexSystem indexSystem;


int LibraryInterface::menu() {
    while (true) {
        std::cout << "Menu:\n"
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
                cout<<"Operation Done Successfully\n";
                break;
            }
            case 2: {
                handleAddBook();
                cout<<"Operation Done Successfully\n";
                break;
            }
            case 3: {
                handleUpdateAuthorName();
                cout<<"Operation Done Successfully\n";
                break;
            }
            case 4: {
                handleUpdateBookTitle();
                cout<<"Operation Done Successfully\n";
                break;
            }
            case 5: {
                handleDeleteBook();
                cout<<"Operation Done Successfully\n";
                break;
            }
            case 6: {
                handleDeleteAuthor();
                cout<<"Operation Done Successfully\n";
                break;
            }
            case 7: {
                handlePrintAuthor();
                cout<<"Operation Done Successfully\n";
                break;
            }
            case 8: {
                handlePrintBook();
                cout<<"Operation Done Successfully\n";
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

void LibraryInterface::handlePrintAuthor() {

}

void LibraryInterface::handleDeleteAuthor() {

}

void LibraryInterface::handleWriteQuery() {

}

void LibraryInterface::handlePrintBook() {

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
