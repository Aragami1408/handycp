/*
 * handycp - Some pretty handy stuff for Competitive Programming
 *
 * Doubly Linked List
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
#include "doublylinkedlist.h"

template<typename T>
handycp::DoublyLinkedList<T>::DoublyLinkedList() {

}

template<typename T>
handycp::DoublyLinkedList<T>::~DoublyLinkedList() {
    this->clear();
    this->destroy();
}

template<typename T>
void handycp::DoublyLinkedList<T>::clear() {
    LIST_FOREACH(this, first, next, cur) {
        delete cur->value;
    } 
}

template<typename T>
void handycp::DoublyLinkedList<T>::destroy() {
    LIST_FOREACH(this, first, next, cur) {
        if(cur->prev) {
            delete cur->prev;
        }
    }

    delete this->last;
    delete this;
}

template<typename T>
void handycp::DoublyLinkedList<T>::push(T value) {
    ListNode node = new ListNode();
    if(node == nullptr) return;
    node->value = value;

    if(this->last == nullptr) {
        this->first = node;
        this->last = node;
    }
    else {
        this->last->next = node;
        node->prev = this->last;
        this->last = node;
    }

    this->count++;
}

template<typename T>
void handycp::DoublyLinkedList<T>::unshift(T value) {
    ListNode node = new ListNode();
    if(node == nullptr) goto error;

    node->value = value;

    if (this->first == nullptr) {
        this->first = node;
        this->last = node;
    }
    else {
        node->next = this->first;
        this->first->prev = node;
        this->first = node;
    }

    this->count++;
    
error:
    return;
}

template<typename T>
void *handycp::DoublyLinkedList<T>::shift() {
    ListNode *node = this->last;
    return node != nullptr ? remove(node) : nullptr;
}

template<typename T>
void *handycp::DoublyLinkedList<T>::remove(ListNode *node) {
    void *result = nullptr;

    if(!(this->first && this->last) || !node) goto error;

    if(node == this->first && node == this->last) {
        this->first = nullptr;
        this->last = nullptr;
    }
    else if (node == this->first) {
        this->first = node->next;
        if(this->first == nullptr) goto error;
        this->first->prev = nullptr;
    }
    else if (node == this->last) {
        this->last = node->prev;
        if(this->last == nullptr) goto error;
        this->last->next = nullptr;
    }
    else {
        ListNode *after = node->next;
        ListNode *before = node->prev;
        after->prev = before;
        before->next = after;
    }

    this->count--;
    result = node->value;
    delete node;

error:
    return result;
}
