
#ifndef LIBRARY_FILE_SYSTEM_LINKEDLIST_H
#define LIBRARY_FILE_SYSTEM_LINKEDLIST_H


#include <bits/stdc++.h>

using namespace std;
template <class T>
class SLLNode {
public:
    T data;
    SLLNode* next;
    SLLNode(T element,bool marked,string Rnum);
    bool markedForDeletion= false;
    string recordNum;
};

template <class T>
class LinkedList {
public:
    SLLNode<T> *head;
    SLLNode<T> *tail;
    int size;
    LinkedList();
    void insertAtHead(T element ,bool marked,string Rnum) ;
    void insertAtTail(T element,bool marked,string Rnum) ;
    void print();
    T removeAtHead();
    void markDeleted(int index);
    int indexOf(T element);
    T * getNextNodeDataPtr();
    void removeNodeWithValue(T value);
    ~LinkedList();

    string getRecordNum(SLLNode<T> *currentNode) const;

    SLLNode<T> *getHead() const;

    SLLNode<T> *getNext(SLLNode<T> *currentNode) const;

    SLLNode<T> *getNode(int index);
};


#endif //LIBRARY_FILE_SYSTEM_LINKEDLIST_H
