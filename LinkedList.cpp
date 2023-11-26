
#include "LinkedList.h"

template <class T>
SLLNode<T>::SLLNode (T element) {
    data = element;
    next = NULL;
}
template <class T>
LinkedList<T>::LinkedList() {
    head=NULL;
    size=0;
}

template <class T>
void LinkedList<T>:: insertAtHead(T element) {
    SLLNode<T>* newNode=new SLLNode<T>(element);
    newNode->next=head;
    head=newNode;
    size++;
}
template <class T>
void LinkedList<T>::insertAtTail(T element) {
    if (head==NULL) {
        insertAtHead(element);
        return;
    }

    SLLNode<T>* temp=head;
    while (temp->next!=NULL)
    {
        temp=temp->next;
    }
    SLLNode<T>* newnode=new SLLNode<T>(element);
    newnode->data=element;
    temp->next=newnode;
    newnode->next = NULL;
    size++;
}
template <class T>
void LinkedList<T>::insertAt(T element, int index) {
    if (index<0||index>size) {
        cout<<"out of range!!!";
        return;
    }
    if (index==0) {
        insertAtHead(element);
        return;
    }
    if (index==size) {
        insertAtTail(element);
        return;
    }
    SLLNode<T> *newNode=new SLLNode<T>(element);
    SLLNode<T> *curr=head;
    for (int i=0; i<index-1; i++) {
        curr=curr->next;
    }
    newNode->next=curr->next;
    curr->next=newNode;
    size++;
}
template <class T>
void LinkedList<T>::removeAtHead() {
    if (head==NULL) {
        cout<<"Empty list!!!"<<endl;
        return;
    }
    SLLNode<T> *ptr=head;
    if (head==tail) {
        head=NULL;
        tail=NULL;
    }
    else {
        head=head->next;
        delete ptr;
    }
    size--;
}
template <class T>
void LinkedList<T>:: removeAtTail() {
    if (head==NULL) {
        cout<<"Empty list!!!"<<endl;
        return;
    }
    SLLNode<T> *ptr=head;
    while (ptr->next->next != NULL) {
        ptr=ptr->next;
    }
    SLLNode<T> *target=ptr->next;
    ptr->next=NULL;
    delete target;
    size--;
}
template <class T>
void LinkedList<T>:: removeAt(int index) {
    if (index<0||index>=size) {
        cout<<"out of range!!!";
        return;
    }
    if (index==0) {
        removeAtHead();
        return;
    }
    if (index==size-1) {
        removeAtTail();
        return;
    }
    SLLNode<T> *curr=head;
    for (int i=0;i<index-1;i++) {
        curr= curr->next;
    }
    SLLNode<T> *target=curr->next;
    curr->next=curr->next->next;
    delete target;
    size--;
}
template <class T>
T LinkedList<T>::retrieveAt(int index) {
    if (index<0||index>=size) {
        cout<<"out of range!!!";
        return -1 ;
    }
    SLLNode<T> *curr = head;
    for (int i = 0; i < index; i++) {
        curr=curr->next;
    }
    return curr->data;
}
template <class T>
void LinkedList<T>:: replaceAt(T newElement, int index) {
    if (index<0||index>=size) {
        cout<<"out of range!!!";
        return ;
    }
    SLLNode<T> *curr=head;
    for (int i=0;i<index;i++) {
        curr=curr->next;
    }
    curr->data=newElement;
}
template <class T>
bool LinkedList<T>:: isExist(T element) {
    bool isExist=false;
    SLLNode<T>* curr=head;
    while (curr!=NULL) {
        if (curr->data==element)
            isExist = true;
        curr=curr->next;
    }
    return isExist;
}
template <class T>
bool LinkedList<T>::isItemAtEqual(T element, int index) {
    if (index<0||index>=size) {
        cout<<"Index out of range";
        return false ;
    }

    SLLNode<T> *curr=head;
    for (int i=0;i<index;i++) {
        curr= curr->next;
    }
    if( curr->data==element){
        return true;
    }
    else
        return false;
}
template <class T>
void LinkedList<T>:: swap( int firstItemIdx, int secondItemIdx) {
    if (firstItemIdx==secondItemIdx) {
        return;
    }
    SLLNode<T>* node1=head;
    SLLNode<T>* prev1=NULL;
    int i=0;
    while (node1&&i<firstItemIdx) {
        prev1=node1;
        node1=node1->next;
        i++;
    }
    SLLNode<T>* node2=head;
    SLLNode<T>* prev2=NULL;
    i=0;
    while (node2&&i<secondItemIdx) {
        prev2=node2;
        node2=node2->next;
        i++;
    }

    if (prev1!=NULL) {
        prev1->next = node2;
    } else {
        head=node2;
    }
    if (prev2!=NULL) {
        prev2->next=node1;
    } else {
        head=node1;
    }
    SLLNode<T>* temp=node1->next;
    node1->next=node2->next;
    node2->next=temp;
}
template <class T>
bool LinkedList<T>::isEmpty() {
    if(head==NULL){
        return true;
    }
    else
        return false;
}
template <class T>
int LinkedList<T>:: linkedListSize() {
    return size;
}
template <class T>
void LinkedList<T>:: clear() {
    while (!head==NULL) {
        removeAtHead();
    }

}
template <class T>
void LinkedList<T>:: print() {
    SLLNode<T> *temp=head;
    while (temp!=NULL) {
        cout<<temp->data << " ";
        temp=temp->next;
    }
    cout << endl;
}
