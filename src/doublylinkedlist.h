#pragma once

#include <memory>
namespace handycp {
    template<typename T>
    class DoublyLinkedList {
    private:
        int count;
        struct ListNode {
            ListNode *next;
            ListNode *prev;
            T value;
        };
        ListNode *first;
        ListNode *last;
    public:
        DoublyLinkedList();
        ~DoublyLinkedList();
        void destroy();
        void clear();
        void push(T value);
        void *pop();
        void unshift(T value);
        void *shift();
        void *remove(ListNode *node);
        
        #define LIST_FOREACH(L, S, M, V) \
            ListNode *_node = nullptr;\
            ListNode *V = nullptr;\
            for(V = _node = L->S; _node != nullptr; V = _node = _node->M)
    };
};

