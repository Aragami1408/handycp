/*
 * handycp - Some pretty handy stuff for Competitive Programming
 *
 * Radix Map
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
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "radixmap.h"
#include "dbg.h"


RadixMap *RadixMap_create(size_t max) {
    RadixMap *map = calloc(sizeof(RadixMap),1);
    CHECK_MEM(map, error);

    map->contents = calloc(sizeof(RMElement), max + 1);
    CHECK_MEM(map->contents, error);

    map->temp = calloc(sizeof(RMElement), max + 1);
    CHECK_MEM(map->contents, error);

    map->max = max;
    map->end = 0;

    return map;

error:
    return NULL;
}

void RadixMap_destroy(RadixMap *map) {
    if (map) {
        free(map->contents);
        free(map->temp);
        free(map);
    }
}

#define ByteOf(x,y) (((uint8_t *)x)[(y)])

static inline void radix_sort(short offset, uint64_t max, uint64_t *source, uint64_t *dest) {
    uint64_t count[256] = {0};
    uint64_t *cp = NULL;
    uint64_t *sp = NULL;
    uint64_t *end = NULL;
    uint64_t s = 0;
    uint64_t c = 0;

    for (sp = source, end = source + max; sp < end; sp++) {
        count[ByteOf(sp, offset)]++;
    }

    for (s = 0, cp = count, end = count + 256; cp < end; cp++) {
        c = *cp;
        *cp = s;
        s += c;
    }

    for (sp = source, end = source + max; sp < end; sp++) {
        cp = count + ByteOf(sp, offset);
        dest[*cp] = *sp;
        ++(*cp);
    }
}

void RadixMap_sort(RadixMap *map) {
    uint64_t *source = &map->contents[0].raw;
    uint64_t *temp = &map->temp[0].raw;

    radix_sort(0, map->end, source, temp);
    radix_sort(1, map->end, source, temp);
    radix_sort(2, map->end, source, temp);
    radix_sort(3, map->end, source, temp);
}

RMElement *RadixMap_find(RadixMap *map, uint32_t to_find) {
    int low = 0;
    int high = map->end - 1;
    RMElement *data= map->contents;

    while (low <= high) {
        int middle = low + (high - low) / 2;
        uint32_t key = data[middle].data.key;

        if (to_find < key) {
            high = middle - 1;
        }
        else if (to_find > key) {
            low = middle + 1;
        }
        else {
            return &data[middle];
        }
    }

    return NULL;
}

int RadixMap_add(RadixMap *map, uint32_t key, uint32_t value) {
    CHECK(key < UINT32_MAX, error, "Key can't be equal to UINT32_MAX");

    RMElement element = {.data = {.key = key, .value = value}};
    CHECK(map->end + 1 < map->max, error, "RadixMap is full.");

    map->contents[map->end++] = element;

    RadixMap_sort(map);

    return 0;


error:
    return -1;
}

int RadixMap_delete(RadixMap *map, RMElement *el) {
    CHECK(map->end > 0, error, "There is nothing to delete.");
    CHECK(el != NULL, error, "Can't delete a NULL element");

    el->data.key = UINT32_MAX;

    if (map->end > 1) {
        RadixMap_sort(map);
    }

    map->end--;

    return 0;
error:
    return -1;
}
