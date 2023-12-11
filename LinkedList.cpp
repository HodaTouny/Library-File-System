#include "LinkedList.h"

template <class T>
SLLNode<T>::SLLNode(T element,bool marked,string Rnum) {
    data = element;
    next = nullptr;
    markedForDeletion = marked;
    recordNum=Rnum;
}

template <class T>
LinkedList<T>::LinkedList() {
    head = nullptr;
    size = 0;
}


template <class T>
void LinkedList<T>::insertAtHead(T element ,bool marked,string Rnum) {
    SLLNode<T>* newNode = new SLLNode<T>(element,marked,Rnum);
    newNode->next = head;
    head = newNode;
    size++;
}

template <class T>
void LinkedList<T>::insertAtTail(T element,bool marked,string Rnum) {
    if (head == nullptr) {
        insertAtHead(element,marked,Rnum);
        return;
    }

    SLLNode<T>* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }

    SLLNode<T>* newNode = new SLLNode<T>(element,marked,Rnum);
    temp->next = newNode;
    newNode->next = nullptr;
    size++;
}

template <class T>
std::string LinkedList<T>::getRecordNum(SLLNode<T>* currentNode) const {
    if (currentNode == nullptr) {
        return "";
    }
    return currentNode->recordNum;
}


template <class T>
SLLNode<T>* LinkedList<T>::getHead() const {
    return head;
}

template <class T>
SLLNode<T>* LinkedList<T>::getNext(SLLNode<T>* currentNode) const {
    if (currentNode == nullptr) {
        return nullptr;
    }
    return currentNode->next;
}
template <class T>
void LinkedList<T>::markDeleted(int index) {
    if (index < 0 || index >= size) {
        cout << "Index out of range!!!" << endl;
        return;
    }

    SLLNode<T>* curr = head;
    for (int i = 0; i < index; i++) {
        curr = curr->next;
    }

    if (curr != nullptr) {
        curr->markedForDeletion = true;
    }
}

template <class T>
void LinkedList<T>::print()  {
    SLLNode<T>* temp = head;
    while (temp != nullptr) {
        cout << temp->data <<" ";
        temp = temp->next;
    }
    cout << endl;
}

template <class T>
T * LinkedList<T>::getNextNodeDataPtr(){
    if (head == nullptr || head->next == nullptr) {
        return nullptr;
    }

    return &(head->next->data);
}

template <class T>
int LinkedList<T>::indexOf(T element) {
    SLLNode<T>* curr = head;
    int index = 0;
    while (curr != nullptr) {
        if (curr->data == element) {
            return index;
        }
        curr = curr->next;
        index++;
    }
    return -1;
}

template <class T>
void LinkedList<T>::removeNodeWithValue(T value) {
    SLLNode<T> *current = head;
    SLLNode<T> *prev = nullptr;
    while (current != nullptr && current->data != value) {
        prev = current;
        current = current->next;
    }
    if (current == nullptr) {
        cout << "Node not found!" << endl;
        return;
    }
    if (prev == nullptr) {
        head = current->next;
    } else {
        prev->next = current->next;
    }

    delete current;
    size--;
}
template <class T>
SLLNode<T> * LinkedList<T>::getNode(int index) {
    if (index < 0 || index >= size) {
        cout << "Index out of range!!!" << endl;
        return nullptr;
    }

    SLLNode<T>* curr = head;
    for (int i = 0; i < index; i++) {
        curr = curr->next;
    }

    return curr;
}

template <class T>
LinkedList<T>::~LinkedList() {
    while (head != nullptr) {
        SLLNode<T>* temp = head;
        head = head->next;
        delete temp;
    }
    size = 0;
}

template class LinkedList<std::string>;