/*
 * handycp - Some pretty handy stuff for Competitive Programming
 *
 * Ternary Search Tree
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
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dbg.h"
#include "tstree.h"

static inline TSTree *TSTree_insert_base(TSTree *root, TSTree *node, const char *key, size_t len, void *value) {
    if (node == NULL) {
        node = (TSTree *) calloc(1, sizeof(TSTree));

        if (root == NULL) {
            root = node;
        }

        node->splitchar = *key;
    }

    if (*key < node->splitchar) {
        node->low = TSTree_insert_base(root, node->low, key, len, value);
    }
    else if (*key == node->splitchar) {
        if (len > 1) {
            node->equal = TSTree_insert_base(root, node->equal, key + 1, len - 1, value);
        }
        else {
            assert(node->value == NULL && "Duplicate insert into tst.");
        }
    }
    else {
        node->high = TSTree_insert_base(root, node->high, key, len, value);
    }

    return node;
}


TSTree *TSTree_insert(TSTree *node, const char *key, size_t len, void *value) {
    return TSTree_insert_base(node, node, key, len, value);
}

void *TSTree_search(TSTree * root, const char *key, size_t len) {
    TSTree *node = root;

    size_t i = 0;

    while (i < len && node) {
        if (key[i] < node->splitchar) {
            node = node->low;
        }
        else if (key[i] == node->splitchar) {
            i++;
            if (i < len)
                node = node->equal;
        }
        else {
            node = node->high;
        }
    }

    if (node) {
        return node->value;
    }
    else {
        return NULL;
    }
}

void *TSTree_search_prefix(TSTree * root, const char *key, size_t len) {
    if (len == 0) return NULL;

    TSTree *node = root;
    TSTree *last = NULL;
    size_t i = 0;

    while (i < len && node) {
        if (key[i] < node->splitchar) {
        }
    }
}

void TSTree_traverse(TSTree * node, TSTree_traverse_cb cb, void *data) {
    if (!node) return;
    if (node->low) TSTree_traverse(node->low, cb, data);
    if (node->equal) TSTree_traverse(node->equal, cb, data);
    if (node->high) TSTree_traverse(node->high, cb, data);
    if (node->value) cb(node->value, data);
}

void TSTree_destroy(TSTree * root) {
    if(root == NULL) return;
    if(root->low) TSTree_destroy(root->low);
    if(root->equal) TSTree_destroy(root->equal);
    if(root->high) TSTree_destroy(root->high);
    free(root);

}
