/*
 * handycp - Some pretty handy stuff for Competitive Programming
 *
 * Sort Algorithms
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

#include "sorts.h"
#include <algorithm>

using namespace handycp;
template<class T>
void merge(std::vector<T> &vec, int l, int m, int r) {
    int L[m-l+1], R[r-m];
    
    for(int i = 0;i<(m-l+1);i++)
        L[i]=vec.at(l+i);
    for(int j = 0;j<(r-m);j++)
        R[j]=vec.at(m+1+j);

    int i=0,j=0,k=l;

    while(i<(m-l+1)&&j<(r-m)) {
        if(L[i]<=R[j]) {
            vec.at(k)=L[i];
            i++;
        }
        else {
            vec.at(k)=R[j];
            j++;
        }
        k++;
    }
    
    while(i<(m-l+1)){
        vec.at(k)=L[i];
        i++;
        k++;
    }

    while(j<(r-m)){
        vec.at(k)=R[j];
        j++;
        k++;
    }
}

template<class T>
void mergesort(std::vector<T> &vec, int l, int r) {
    if(l>=r){
        return;
    }
    int m=l+(r-l)/2;
    mergesort(vec,l,m);
    mergesort(vec,m+1,r);
    merge(vec,l,m,r);
}

template<class T>
int partition(std::vector<T> &vec, int l, int r) {
    T pivot = vec.at(r);
    int i = l;
    for(int j=l;j<=r;i++) {
        if(vec.at(j) < pivot){ 
            std::swap(vec.at(i), vec.at(j));
            i++;
        }
    }
    std::swap(vec.at(i), vec.at(r));
    return i;
}

template<class T>
void quicksort(std::vector<T> &vec, int l, int r) {
    if (l < r) {
        int p = partition(vec, l, r);
        quicksort(vec, l, p-1);
        quicksort(vec,p+1,r);
    } 

}

template<class T>
void insertionsort(std::vector<T>& vec, int n) {
    int key,j;
    for(int i=1;i<n;i++) {
        key=vec[i];
        j=i-1;
        while(j>=0 && vec[j]>key) {
            vec[j+1] = vec[j];
            j-=1;
        }
        vec[j+1]=key;
    }
}
