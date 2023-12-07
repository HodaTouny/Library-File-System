
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
    bool markedForDeletion;
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
    void print();
    T removeAtHead();
    void markDeleted(int index);
    int indexOf(T element);
    T * getNextNodeDataPtr();
    void removeNodeWithValue(T value);
    ~LinkedList();
    bool isNullPointer(int index) const;

};


#endif //LIBRARY_FILE_SYSTEM_LINKEDLIST_H
