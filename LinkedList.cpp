#include "LinkedList.h"

template <class T>
SLLNode<T>::SLLNode(T element,bool marked,string Rnum) {
    data = element;
    next = nullptr;
    markedForDeletion = marked;
    recordNum="";
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
T LinkedList<T>::removeAtHead() {
    if (head == nullptr) {
        std::cout << "Empty list!!!" << std::endl;
        return T();  // Return a default-constructed value for the type T
    }

    T removedData;
    SLLNode<T>* ptr = head;

    if (head->next == nullptr) {
        removedData = head->data;
        delete head;
        head = nullptr;
    } else {
        removedData = head->data;
        head = head->next;
        delete ptr;
    }

    size--;
    return removedData;
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
LinkedList<T>::~LinkedList() {
    while (head != nullptr) {
        SLLNode<T>* temp = head;
        head = head->next;
        delete temp;
    }
    size = 0;
}


template class LinkedList<std::string>;
