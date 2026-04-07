#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int *data;
    int size;
    int capacity;
} Heap;

// Helper to create a heap
Heap* createHeap(int capacity) {
    Heap* h = (Heap*)malloc(sizeof(Heap));
    h->data = (int*)malloc(sizeof(int) * (capacity + 1));
    h->size = 0;
    h->capacity = capacity;
    return h;
}

// Push into Max-Heap
void pushMax(Heap* h, int val) {
    h->data[++h->size] = val;
    int i = h->size;
    while (i > 1 && h->data[i] > h->data[i/2]) {
        int tmp = h->data[i]; h->data[i] = h->data[i/2]; h->data[i/2] = tmp;
        i /= 2;
    }
}

// Pop from Max-Heap
int popMax(Heap* h) {
    int res = h->data[1];
    h->data[1] = h->data[h->size--];
    int i = 1;
    while (i * 2 <= h->size) {
        int child = i * 2;
        if (child + 1 <= h->size && h->data[child+1] > h->data[child]) child++;
        if (h->data[i] >= h->data[child]) break;
        int tmp = h->data[i]; h->data[i] = h->data[child]; h->data[child] = tmp;
        i = child;
    }
    return res;
}

// Push into Min-Heap
void pushMin(Heap* h, int val) {
    h->data[++h->size] = val;
    int i = h->size;
    while (i > 1 && h->data[i] < h->data[i/2]) {
        int tmp = h->data[i]; h->data[i] = h->data[i/2]; h->data[i/2] = tmp;
        i /= 2;
    }
}

// Pop from Min-Heap
int popMin(Heap* h) {
    int res = h->data[1];
    h->data[1] = h->data[h->size--];
    int i = 1;
    while (i * 2 <= h->size) {
        int child = i * 2;
        if (child + 1 <= h->size && h->data[child+1] < h->data[child]) child++;
        if (h->data[i] <= h->data[child]) break;
        int tmp = h->data[i]; h->data[i] = h->data[child]; h->data[child] = tmp;
        i = child;
    }
    return res;
}

typedef struct {
    Heap* small; // Max-Heap
    Heap* large; // Min-Heap
} MedianFinder;

MedianFinder* medianFinderCreate() {
    MedianFinder* mf = (MedianFinder*)malloc(sizeof(MedianFinder));
    mf->small = createHeap(50000); 
    mf->large = createHeap(50000);
    return mf;
}

void medianFinderAddNum(MedianFinder* obj, int num) {
    // 1. Add to Max-Heap (small half)
    pushMax(obj->small, num);
    
    // 2. Balancing: move largest of small to large
    pushMin(obj->large, popMax(obj->small));
    
    // 3. Maintain size property: small can have at most 1 more than large
    if (obj->large->size > obj->small->size) {
        pushMax(obj->small, popMin(obj->large));
    }
}

double medianFinderFindMedian(MedianFinder* obj) {
    if (obj->small->size > obj->large->size) {
        return (double)obj->small->data[1];
    }
    return (obj->small->data[1] + obj->large->data[1]) / 2.0;
}

void medianFinderFree(MedianFinder* obj) {
    free(obj->small->data);
    free(obj->small);
    free(obj->large->data);
    free(obj->large);
    free(obj);
}
