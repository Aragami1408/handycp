#include "linkedlist.h"

template<class T>
void push(Node<T> **head_ref, T new_data) {
    Node<T>* new_node = new Node<T>();
 
    new_node->data = new_data;
 
    new_node->next = (*head_ref);
 
    (*head_ref) = new_node;
}

template<class T>
void insertAfter(Node<T> *prev_node, T new_data) {
    if(prev_node == nullptr) {
        std::cout<<"the given previous node cannot be nullptr";
        return;
    }

    Node<T> *new_node = new Node<T>();
    new_node->data = new_data;
    new_node->next = prev_node->next;
    prev_node->next = new_node;
}

template<class T>
void append(Node<T> **head_ref, T new_data) {
    Node<T> *new_node = new Node<T>();

    Node<T> *last = *head_ref;

    new_node->data = new_data;

    new_node->next = nullptr; 

    if (*head_ref == nullptr) { 
        *head_ref = new_node; 
        return; 
    } 

    while (last->next != nullptr) 
        last = last->next; 

    last->next = new_node;

    return;
}

template<class T>
void traverse(Node<T> *node) {
    while(node != nullptr) {
        std::cout<<" "<<node->data;
        node = node->next;
    }
}

template<class T>
void deleteNode(Node<T> **head_ref, T key) {
    Node<T> *temp = *head_ref;
    Node<T> *prev = nullptr;

    if(temp != nullptr && temp->data == key) {
        *head_ref = temp->next;
        delete temp;
        return;
    }
    else {
        while(temp != nullptr && temp->data != key) {
            prev=temp;
            temp=temp->next;
        }

        if(temp == nullptr) {
            return;
        }

        prev->next = temp->next;

        delete temp;
    }
}

template<class T>
void deleteAt(Node<T> **head_ref, int pos) {
    if(*head_ref == nullptr) {
        return;
    }

    Node<T> *temp = *head_ref;

    if(pos == 0) {
        *head_ref = temp->next;
        free(temp);
        return;
    } 

    for (int i=0; temp!=nullptr && i<pos-1; i++)
         temp = temp->next;

    if (temp == nullptr || temp->next == nullptr)
         return;

    Node<T> *next = temp->next->next;

    free(temp->next);

    temp->next = next;
}

template<class T>
void deleteList(Node<T> **head_ref) {
    Node<T> *current = *head_ref;
    Node<T> *next = nullptr;

    while(current != nullptr) {
        next = current->next;
        free(current);
        current = next;
    }

    *head_ref = nullptr;
}

template<class T>
int getCount(Node<T> *head) {
    int count = 0;
    Node<T> *current = head;
    while(current != nullptr) {
        count++;
        current=current->next;
    }
    return count;
}

template<class T>
bool search(Node<T> *head, T x) {
    Node<T> *current = head;
    while(current != nullptr) {
        if(current->key == x) {
            return true;
        } 
        current = current->next;
    }
    return false;
}

template<class T>
T GetNth(Node<T> *head, int index) {
    Node<T> *current = head;
    int count = 0;
    while(current != nullptr) {
        if(count == index) {
            return (current->data);
        }
        count++;
        current = current->next;
    }

    assert(0);
