#include "sorts.h"
#include "handycp.h"
#include <algorithm>
template<typename T>
void sorts::merge(std::vector<T> &vec, int l, int m, int r) {
    int L[m-l+1], R[r-m];
    FOR(i,0,(m-l+1))
        L[i]=vec.at(l+i);
    FOR(j,0,(r-m))
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

template<typename T>
void sorts::mergesort(std::vector<T> &vec, int l, int r) {
    if(l>=r){
        return;
    }
    int m=l+(r-l)/2;
    mergesort(vec,l,m);
    mergesort(vec,m+1,r);
    merge(vec,l,m,r);
}

template<typename T>
int sorts::partition(std::vector<T> &vec, int l, int r) {
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

template<typename T>
void sorts::quicksort(std::vector<T> &vec, int l, int r) {
    if (l < r) {
        int p = partition(vec, l, r);
        quicksort(vec, l, p-1);
        quicksort(vec,p+1,r);
    } 

}
