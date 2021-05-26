#undef NDEBUG
#include "sarray.h"
#include "dbg.h"
#include <stdlib.h>

int SuffixArray_compare(void *thunk, const void *a, const void *b)
{
    SuffixArray *sarray = thunk;
    int a_at = *(int *)a;
    int b_at = *(int *)b;
    char *a_str = sarray->source + a_at;
    char *b_str = sarray->source + b_at;

    int a_len = sarray->length - a_at;
    int b_len = sarray->length - b_at;
    int len = a_len < b_len ? a_len : b_len;

    int cmp = strncmp(a_str, b_str, len);

    return cmp;
}

SuffixArray *SuffixArray_create(char *data, int length) {
    SuffixArray *sarray = calloc(1, sizeof(SuffixArray));
    CHECK_MEM(sarray, error);

    sarray->source = malloc(length + 1);
    CHECK_MEM(sarray->source, error);
    memcpy(sarray->source, data, length);
    sarray->source[length] = '\0';

    sarray->length = length;

    sarray->indices = malloc(length * sizeof(int));
    CHECK_MEM(sarray->indices, error);

    int i = 0;
    for(i = 0; i < length; i++) {
        sarray->indices[i] = i;
    }

    qsort_r(sarray->indices, length, sizeof(int), sarray, SuffixArray_compare);

    return sarray;

error:
    if(sarray) {
        SuffixArray_destroy(sarray);
    }

    return NULL;
}

void SuffixArray_destroy(SuffixArray *sarray) {
    if (sarray) {
        free(sarray->source);
        free(sarray->indices);
        free(sarray);
    }
}

int SuffixArray_find_suffix(SuffixArray *sarray, char *data, int length) {
    int min = 0;
    int max = sarray->length;
    int cmp = 0;
    int mid = 0;

    do {
        mid = (min + max) / 2;
        // BUG: wrong, need to use the minimum length
        cmp = strncmp(SuffixArray_substr(sarray, mid), data, length);

        if(cmp < 0) {
            min = mid + 1;
        } else {
            max = mid - 1;
        }
    } while(cmp != 0 && min < max);

    if(cmp == 0) {
        return mid;
    } else {
        return -1;
    }
}
