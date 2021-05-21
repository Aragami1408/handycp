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
#ifndef DARRAY_H
#define DARRAY_H

#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dbg.h"

#define INIT_CAPACITY 0

typedef struct {
    int capacity;
    int n;
    void **items;
} DArray;

static bool DArray_resize(DArray *array, int new_capacity);

static bool DArray_enlarge(DArray *array);

DArray *DArray_create(void);

int DArray_size(const DArray *array);

bool DArray_add_item_at(DArray *array, int index, void *item);

bool DArray_prepend_item(DArray *array, void *item);

bool DArray_append_item(DArray *array, void *item);

int DArray_get_item_at(const DArray *array, int index);

int DArray_remove_item_at(DArray *array, int index);

int DArray_replace_item_at(DArray *array, int index, void *item);

void DArray_free(DArray *array);

#endif