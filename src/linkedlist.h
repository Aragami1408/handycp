/*
 * handycp - Some pretty handy stuff for Competitive Programming
 *
 * Singly Linked List
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


#pragma once

#include <iostream>

namespace handycp {
    
    template<class T>
    struct Node {
        T data;
        Node *next;
    };

    template<class T>
    void push(Node<T> **head_ref, T new_data);

    template<class T>
    void insertAfter(Node<T> *prev_node, T new_data);

    template<class T>
    void append(Node<T> **head_ref, T new_data);

    template<class T>
    void traverse(Node<T> *node);

    template<class T>
    void deleteNode(Node<T> **head_ref, T key);

    template<class T>
    void deleteAt(Node<T> **head_ref, int pos);

    template<class T>
    void deleteList(Node<T> **head_ref);

    template<class T>
    int getCount(Node<T> *head);

    template<class T>
    bool search(Node<T> *head, T x);

    template<class T>
    T GetNth(Node<T> *head, int index);

    template<class T>
    T GetNthFromLast(Node<T> *head);

    template<class T>
    int count(Node<T> *head, int search_for); 
};

