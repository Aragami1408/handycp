/*
 * handycp - Some pretty handy stuff for Competitive Programming
 *
 * Linked List
 *
 *
 * Copyright © 2021 Aragami1408/D6E093 <vucaominh1408@gmail.com>

 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”),
 * to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
 * DEALINGS IN THE SOFTWARE.
 *
 */

#include "linkedlist.h"

using namespace handycp;

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
    return nullptr;
}

template<class T>
T GetNthFromLast(Node<T> *head) {
    Node<T> *slow_ptr = head;
    Node<T> *fast_ptr = head;

    if(head != nullptr) {
        while(fast_ptr != nullptr && fast_ptr->next != nullptr) {
            fast_ptr = fast_ptr->next->next;
            slow_ptr = slow_ptr->next;
        }
        return slow_ptr->data;
    }
}

template<class T>
int count(Node<T> *head, int search_for) {
    Node<T> *current = head;
    int count = 0;
    while(current != nullptr) {
        if(current->data == search_for) {
            count++;
        }
        current = current->next;
    }
    return count;
}
