#pragma once

#include <iostream>
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
