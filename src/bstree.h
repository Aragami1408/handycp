/*
 * handycp - Some pretty handy stuff for Competitive Programming
 *
 * Binary Search Tree
 *
 *
 * Copyright © 2021 Aragami1408/D6E093 <vucaominh1408@gmail.com>

 * Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the “Software”),
 * to deal in the Software without restriction, including without limitation the
 rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 */

#ifndef BSTREE_H
#define BSTREE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef int (*BSTree_compare)(void *a, void *b);

typedef struct BSTreeNode {
		void *key;
		void *data;

		struct BSTreeNode *left;
		struct BSTreeNode *right;
		struct BSTreeNode *parent;

} BSTreeNode;

typedef int (*BSTree_traverse_cb)(BSTreeNode *node);

typedef struct BSTree {
	int count;
	BSTree_compare compare;
	BSTreeNode *root;

	void (*destroy)(struct BSTree *map);
	int (*BSTree_set)(struct BSTree *map, void *key, void *data);

	int (*set)(struct BSTree *map, void *key, void *data);
	void *(*BSTree_get)(struct BSTree *map, void *key);

	int (*BSTree_traverse)(struct BSTree *map, BSTree_traverse_cb traverse_cb);

	void *(*BSTree_delete)(struct BSTree *map, void *key);
} BSTree;

extern BSTree *BSTree_create(BSTree_compare compare);
extern void BSTree_destroy(BSTree *map);

extern int BSTree_set(BSTree *map, void *key, void *data);
extern void *BSTree_get(BSTree *map, void *key);

extern int BSTree_traverse(BSTree *map, BSTree_traverse_cb traverse_cb);

extern void *BSTree_delete(BSTree *map, void *key);

#endif
