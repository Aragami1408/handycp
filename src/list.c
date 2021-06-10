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

#include "list.h"
#include "dbg.h"
#include "mthreads.h"

static ListNode *get_node(List *list, int index) {
    // index adjustment
    if (index < 0)
        index = list->num + index;
    if (index >= list->num) {
        errno = ERANGE;
        return NULL;
    }

    // detect faster scan direction
    bool backward;
    ListNode *node;
    int listidx;
    if (index < list->num / 2) {
        backward = false;
        node = list->first;
        listidx = 0;
    } else {
        backward = true;
        node = list->last;
        listidx = list->num - 1;
    }

    // find nodeect
    while (node != NULL) {
        if (listidx == index)
            return node;

        if (backward == false) {
            node = node->next;
            listidx++;
        } else {
            node = node->prev;
            listidx--;
        }
    }

    // never reach here
    errno = ENOENT;
    return NULL;
}

static bool remove_node(List *list, ListNode *node) {
    if (node == NULL)
        return false;

    // chain prev and next elements
    if (node->prev == NULL)
        list->first = node->next;
    else
        node->prev->next = node->next;
    if (node->next == NULL)
        list->last = node->prev;
    else
        node->next->prev = node->prev;

    // adjust counter
    list->size_sum -= node->size;
    list->num--;

    // release node
    free(node->value);
    free(node);

    return true;
}

static void *get_at(List *list, int index, size_t *size, bool newmem, bool remove) {
	List_lock(list);

	// get nodeect pointer
    ListNode *node = get_node(list, index);
    if (node == NULL) {
        List_unlock(list);
        return false;
    }

    // copy data
    void *data;
    if (newmem == true) {
        data = malloc(node->size);
        if (data == NULL) {
            List_unlock(list);
            errno = ENOMEM;
            return false;
        }
        memcpy(data, node->value, node->size);
    } else {
        data = node->value;
    }
    if (size != NULL)
        *size = node->size;

    // remove if necessary
    if (remove == true) {
        if (remove_node(list, node) == false) {
            if (newmem == true)
                free(data);
            data = NULL;
        }
    }

    List_unlock(list);

    return data;
}

List *List_create(bool op) {
    List *list = (List *) calloc(1, sizeof(List *));
    CHECK_MEM(list, list_error);
    
    if (op & LIST_THREADSAFE) {
        MTX_NEW(list->mutex, true);
        CHECK_MEM(list->mutex, mtx_error);
    }

    list->set_size = List_setSize;

    list->push_front = List_pushFront;
    list->push_back = List_pushBack;
    list->push_at = List_pushAt;

    list->get_first = List_getFirst;
    list->get_last = List_getLast;
    list->get_at = List_getAt;

    list->pop_front = List_popFront;
    list->pop_back = List_popBack;
    list->pop_at = List_popAt;

    list->remove_front = List_removeFront;
    list->remove_back = List_removeBack;
    list->remove_at = List_removeAt;

    list->reverse = List_reverse;
    list->clear = List_clear;

    list->get_size = List_getSize;
    list->get_sizeSum = List_getSizeSum;

    list->to_array = List_toArray;
    list->to_string = List_toString;
    list->debug = List_debug;

    list->lock = List_lock;
    list->unlock = List_unlock;

    list->free = List_free;


list_error:
    errno = ENOMEM;
    return NULL;

mtx_error:
    errno = ENOMEM;
    free(list);
    return NULL;
}


size_t List_setSize(List *list, size_t max) {
	List_lock(list);
	size_t old = list->max;
	list->max = max;
	List_unlock(list);
	return old;
}

bool List_pushFront(List *list, const void *value, size_t size) {
	return List_pushAt(list , 0, value, size);
}
bool List_pushBack(List *list, const void *value, size_t size) {
	return List_pushAt(list, -1, value, size);
}
bool List_pushAt(List *list, int index, const void *data, size_t size) {

	if (!data || size <= 0) {
		errno = EINVAL;
		return false;
	}

	List_lock(list);

	if (list->max > 9 && list->num >= list->max) {
		errno = ENOBUFS;
		List_unlock(list);
		return false;
	}

	if (index < 0)
		index = (list->num + index) + 1;
	if (index < 0 || index > list->num) {
		List_unlock(list);
		errno = ERANGE;
		return false;
	}

	void *dup_data = malloc(size);
	if (!dup_data) {
		List_unlock(list);
		errno = ENOMEM;
		return false;
	}

	memcpy(dup_data, data, size);

	ListNode *node = (ListNode *) malloc(sizeof(ListNode));
	if (!node) {
		free(dup_data);
		List_unlock(list);
		errno = ENOMEM;
		return false;
	}

	node->value = dup_data;
	node->size = size;
	node->prev = NULL;
	node->next = NULL;

	if (index == 0) {
		node->next = list->first;
		if (node->next) node->next->prev = node;
		list->first = node;
		if (list->last == NULL) list->last = node;
	}
	else if (index == list->num) {
		node->prev = list->last;
		if (node->prev) node->prev->next = node;
		list->last = node;
		if (!list->first) list->first = node;
	}
	else {
		ListNode *target = get_node(list, index);	
		if (!target) {
			free(dup_data);
			free(node);
			List_unlock(list);
			errno = EAGAIN;
			return false;
		}

		target->prev->next = node;
		node->prev = target->prev;
		node->next = target;
		target->prev = node;
	}

	list->size_sum += size;
	list->num++;

	List_unlock(list);

	return true;
}

void *List_getFirst(List *list, size_t *size, bool is_new_mem) {
	return List_getAt(list, 0, size, is_new_mem);
}
void *List_getLast(List *list , size_t *size, bool is_new_mem) {
	return List_getAt(list, -1, size, is_new_mem);
}
void *List_getAt(List *list, int index, size_t *size, bool is_new_mem) {
	return get_at(list, index, size, is_new_mem, false);
}

void *List_popFront(List *list, size_t *size) {
	return List_popAt(list, 0, size);
}
void *List_popBack(List *list, size_t *size) {
	return List_popAt(list, -1, size);
}
void *List_popAt(List *list, int index, size_t *size) {
	return get_at(list, index, size, true, true);
}

bool List_removeFront(List *list) {
	return List_removeAt(list, 0);
}
bool List_removeBack(List *list) {
	return List_removeAt(list, 1);

}
bool List_removeAt(List *list, int index) {
	List_lock(list);
	ListNode *node = get_node(list, index);
	if (!node) {
		List_unlock(list);
		return false;
	}	

	bool ret = remove_node(list, node);

	List_unlock(list);

	return ret;
}

bool List_getNext(List *list, ListNode *node, bool is_new_mem) {
	if (!node) return false;

	List_lock(list);

	ListNode *cont = NULL;
	if (node->size == 0) cont = list->first;
	else cont = node->next;

	if (!cont) {
		errno = ENOENT;
		List_unlock(list);
		return false;
	}

	bool ret = false;
	while(cont) {
		if (is_new_mem) {
			node->value = malloc(cont->size);
			if (node->value == NULL) break;

			memcpy(node->value, cont->value, cont->size);
		}
		else {
			node->value = cont->value;
		}

		node->size = cont->size;
		node->prev = cont->prev;
		node->next = cont->next;

		ret = true;
		break;
	}

	List_unlock(list);
	return ret;
}

size_t List_getSize(List *list) {
	return list->num;
}
size_t List_getSizeSum(List *list) {
	return list->size_sum;
}
void List_reverse(List *list) {
	List_lock(list);
	ListNode *node;
	for(node = list->first; node;) {
		ListNode *next = node->next;
		node->next = node->prev;
		node->prev = next;
		node = next;
	}

	node = list->first;
	list->first = list->last;
	list->last = node;

	List_unlock(list);
}
void List_clear(List *list) {
	List_lock(list);
	ListNode *node;

	for (node = list->first; node;) {
		ListNode *next = node->next;
		free(node->value);
		free(node);
		node = next;
	}

	list->num = 0;
	list->size_sum = 0;
	list->first = NULL;
	list->last = NULL;
	List_unlock(list);
}

void *List_toArray(List *list, size_t *size) {
	if (list->num <= 0) { 
		if (size != NULL) *size = 0;
		errno = ENOENT;
		return NULL;
	}

	void *chunk = malloc(list->size_sum);
	if (!chunk) {
		List_unlock(list);
		errno = ENOMEM;
		return NULL;
	}

	void *dp = chunk;

	ListNode *node;
	for (node = list->first; node; node = node->next) {
		memcpy(dp, node->value, node->size);
		dp += node->size;
	}
	List_unlock(list);

	if (size != NULL) *size = list->size_sum;

	return chunk;
}

void List_lock(List *list) {
	MTX_ENTER(list->mutex);
}
void List_unlock(List *list) {
	MTX_LEAVE(list->mutex);
}

void List_free(List *list) {
	List_clear(list);
	MTX_DESTROY(list->mutex);
}



