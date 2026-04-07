#include <stdbool.h>
#include <stdlib.h>

// Helper to get bucket ID, handling negative numbers correctly
long getBucketID(long val, long w) {
    return val < 0 ? (val + 1) / w - 1 : val / w;
}

// Simple hash map entry for buckets
typedef struct {
    long key;
    long value;
    bool occupied;
} Bucket;

bool containsNearbyAlmostDuplicate(int* nums, int numsSize, int indexDiff, int valueDiff) {
    if (numsSize < 2 || indexDiff < 1 || valueDiff < 0) return false;

    // Use a hash table to store buckets (size approx. numsSize for safety)
    int tableSize = numsSize;
    Bucket* table = (Bucket*)calloc(tableSize, sizeof(Bucket));
    long w = (long)valueDiff + 1;

    for (int i = 0; i < numsSize; i++) {
        long val = nums[i];
        long id = getBucketID(val, w);
        int h = abs(id % tableSize);

        // Linear probing to find/insert bucket
        while (table[h].occupied && table[h].key != id) {
            h = (h + 1) % tableSize;
        }

        // Check current bucket
        if (table[h].occupied) return true;

        // Check neighbor buckets
        int prevH = abs((id - 1) % tableSize);
        while (table[prevH].occupied && table[prevH].key != id - 1) prevH = (prevH + 1) % tableSize;
        if (table[prevH].occupied && abs(val - table[prevH].value) < w) return true;

        int nextH = abs((id + 1) % tableSize);
        while (table[nextH].occupied && table[nextH].key != id + 1) nextH = (nextH + 1) % tableSize;
        if (table[nextH].occupied && abs(val - table[nextH].value) < w) return true;

        // Insert current value into bucket
        table[h].key = id;
        table[h].value = val;
        table[h].occupied = true;

        // Remove the element outside the sliding window
        if (i >= indexDiff) {
            long oldId = getBucketID(nums[i - indexDiff], w);
            int removeH = abs(oldId % tableSize);
            while (table[removeH].key != oldId) removeH = (removeH + 1) % tableSize;
            table[removeH].occupied = false;
        }
    }

    free(table);
    return false;
}
