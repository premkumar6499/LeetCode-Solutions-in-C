#include <stdio.h>
#include <stdlib.h>

// Comparison function for qsort
int compare(const void* a, const void* b) {
    int* env1 = *(int**)a;
    int* env2 = *(int**)b;
    if (env1[0] != env2[0]) {
        return env1[0] - env2[0]; // Width ascending
    }
    return env2[1] - env1[1]; // Height descending for same width
}

int maxEnvelopes(int** envelopes, int envelopesSize, int* envelopesColSize) {
    if (envelopesSize == 0) return 0;

    // 1. Sort the envelopes
    qsort(envelopes, envelopesSize, sizeof(int*), compare);

    // 2. Find LIS of the heights using binary search (Patience Sorting)
    int* tails = (int*)malloc(sizeof(int) * envelopesSize);
    int size = 0;

    for (int i = 0; i < envelopesSize; i++) {
        int height = envelopes[i][1];
        
        // Binary search for the first element in tails >= height
        int left = 0, right = size;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (tails[mid] < height) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        
        tails[left] = height;
        if (left == size) size++;
    }

    free(tails);
    return size;
}
