
#ifndef LIBRARY_FILE_SYSTEM_LINKEDLIST_H
#define LIBRARY_FILE_SYSTEM_LINKEDLIST_H


#include <bits/stdc++.h>

using namespace std;
template <class T>
class SLLNode {
public:
    T data;
    SLLNode* next;
    SLLNode(T element) ;
};

template <class T>
class LinkedList {
public:
    SLLNode<T> *head;
    SLLNode<T> *tail;
    int size;
    LinkedList();
    void insertAtHead(T element) ;
    void insertAtTail(T element) ;
    void insertAt(T element, int index);
    void removeAtTail();
    void removeAt(int index) ;
    T retrieveAt(int index) ;
    void replaceAt(T newElement, int index);
    bool isExist(T element);
    bool isItemAtEqual(T element, int index);
    void swap( int firstItemIdx, int secondItemIdx);
    bool isEmpty();
    int linkedListSize();
    void clear();
    //void print();
    void print() const {
        SLLNode<T> *current = head;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
    }
    T removeAtHead();
    T * getNextNodeDataPtr();
    void removeNodeWithValue(T value);
    ~LinkedList();


};


#endif //LIBRARY_FILE_SYSTEM_LINKEDLIST_H
