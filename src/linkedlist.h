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

#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <stdio.h>

typedef struct ListNode {
    struct ListNode *next;      // next node
    struct ListNode *prev;      // previous node
    void *value;                // generic value
    size_t size;                // generic value's size
} ListNode;

typedef struct List {
    size_t num;                 // number of elements
    size_t max;                 // max num of elems, set max to 0 for no limitation
    size_t size_sum;            // sum of data size
    ListNode *first;            // first node of the list
    ListNode *last;             // last node of the list

    size_t (*set_size)(List *, size_t);

    bool (*push_front)(List *, const void *, size_t);
    bool (*push_back)(List *, int, const void *, size_t);
    bool (*push_at)(List *, int, const void *, size_t);

    void *(*get_first)(List *, size_t *, bool);
    void *(*get_last)(List *, size_t *, bool);
    void *(*get_at)(List *, int, size_t *, bool);

    void *(*pop_front)(List *, size_t *);
    void *(*pop_back)(List *, size_t *);
    void *(*pop_at)(List *, int index, size_t *);

    bool (*remove_front)(List *);
    bool (*remove_back)(List *list);
    bool (*remove_at)(List *, int);

    bool (*get_next)(List *, ListNode *, bool);
    
    size_t (*get_size)(List *);
    size_t (*get_sizeSum)(List *);
    void (*reverse)(List *);
    void (*clear)(List *);

    void *(*to_array)(List *, size_t);
    void *(*to_string)(List*);
    bool (*debug)(List *, FILE *);

    void (*free)(List *);

} List;

extern List *List_create();
extern size_t List_setSize(List *list, size_t max);

extern bool List_pushFront(List *list, const void *value, size_t size);
extern bool List_pushBack(List *list, const void *value, size_t size);
extern bool List_pushAt(List *list, int index, const void *data, size_t size);

extern void *List_getFirst(List *list, size_t *size, bool is_new_mem);
extern void *List_getLast(List *list , size_t *size, bool is_new_mem);
extern void *List_getAt(List *list, int index, size_t *size, bool is_new_mem);

extern void *List_popFront(List *list, size_t *size);
extern void *List_popBack(List *list, size_t *size);
extern void *List_popAt(List *list, int index, size_t *size);

extern bool List_removeFront(List *list);
extern bool List_removeBack(List *list);
extern bool List_removeAt(List *list, int index);

extern bool List_getNext(List *list, ListNode *node, bool is_new_mem);

extern size_t List_size(List *list);
extern size_t List_sizeSum(List *list);
extern void List_reverse(List *list);
extern void List_clear(List *list);

extern void *List_toArray(List *list, size_t size);
extern void *List_toString(List *list);
extern bool List_debug(List *list, FILE *out);

extern void List_free(List *list);

#endif
