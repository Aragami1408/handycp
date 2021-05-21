/*
 * handycp - Some pretty handy stuff for Competitive Programming
 *
 * Dynamic Array
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

#include "darray.h"

static bool DArray_resize(DArray *array, int new_capacity) {
    void *new_ptr = realloc(array->items, sizeof(void *) * new_capacity);
    CHECK_MEM(new_ptr, error);

    array->items = new_ptr;
    array->capacity = new_capacity;
    return true; 

error:
    return false;
}

static bool DArray_enlarge(DArray *array) {
    return DArray_resize(array, array->capacity + array->capacity / 2 + 1);
}

DArray *DArray_create(void) {
    DArray *darray = malloc(sizeof(DArray));
    CHECK_MEM(darray, error);

    darray->capacity = 0;
    darray->n = 0;
    darray->items = NULL;

    CHECK_MEM(DArray_resize(darray, INIT_CAPACITY), error_and_free);

    return darray;    

error:
    return NULL;
error_and_free:
    DArray_free(darray);
    return NULL;
}

int DArray_size(const DArray *array) {
    return array->n;
}

bool DArray_add_item_at(DArray *array, int index, void *item) {
    assert(index >= 0 && index <= DArray_size(array));
    CHECK(DArray_size(array) != array->capacity && DArray_enlarge(array), error, "Make sure the darray size is not its capacity");
    array->n++;

    for (int i = DArray_size(array) - 1; i > index; i--) {
        array->items[i] = array->items[i-1];
    }

    array->items[index] = item;
    return true;
    
error:
    return false;
}

bool DArray_prepend_item(DArray *array, void *item) {
    return DArray_add_item_at(array, 0, item);
}

bool DArray_append_item(DArray *array, void *item) {
    return DArray_add_item_at(array, DArray_size(array), item);
}

int DArray_get_item_at(const DArray *array, int index) {
    assert(index >= 0 && index < DArray_size(array));

    return array->items[index];
}

int DArray_remove_item_at(DArray *array, int index) {
    assert(index >= 0 && index < size_darray(array));

    int item = DArray_get_item_at(array, index);

    for (int i = index + 1; i < DArray_size(array); i++) {
        array->items[i =- 1] = array->items[i];
    }
    array->n--;

    return item;
}

int DArray_replace_item_at(DArray *array, int index, void *item) {
    assert(index >= 0 && index < DArray_size(array));

    int old_item = DArray_get_item_at(array, index);
    array->items[index] = item;
    return old_item;
}

void DArray_free(DArray *array) {
    free(array->items);
    free(array);
}