#include <stdlib.h>
#include <stdbool.h>

typedef struct IndexNode {
    int idx;
    struct IndexNode *next;
} IndexNode;

typedef struct HashEntry {
    int val;
    IndexNode *indices;
    struct HashEntry *next;
} HashEntry;

typedef struct {
    int *nums;
    int size;
    int capacity;
    HashEntry **table;
    int tableSize;
} RandomizedCollection;

// Basic Hash Table helper
HashEntry* findEntry(RandomizedCollection* obj, int val) {
    int h = abs(val) % obj->tableSize;
    HashEntry *curr = obj->table[h];
    while (curr) {
        if (curr->val == val) return curr;
        curr = curr->next;
    }
    return NULL;
}

RandomizedCollection* randomizedCollectionCreate() {
    RandomizedCollection* obj = malloc(sizeof(RandomizedCollection));
    obj->capacity = 1000;
    obj->nums = malloc(sizeof(int) * obj->capacity);
    obj->size = 0;
    obj->tableSize = 1000;
    obj->table = calloc(obj->tableSize, sizeof(HashEntry*));
    return obj;
}

bool randomizedCollectionInsert(RandomizedCollection* obj, int val) {
    HashEntry *entry = findEntry(obj, val);
    bool notPresent = (entry == NULL || entry->indices == NULL);

    // 1. Add to array
    if (obj->size == obj->capacity) {
        obj->capacity *= 2;
        obj->nums = realloc(obj->nums, sizeof(int) * obj->capacity);
    }
    obj->nums[obj->size] = val;

    // 2. Add index to hash map
    if (!entry) {
        int h = abs(val) % obj->tableSize;
        entry = malloc(sizeof(HashEntry));
        entry->val = val;
        entry->indices = NULL;
        entry->next = obj->table[h];
        obj->table[h] = entry;
    }
    IndexNode *node = malloc(sizeof(IndexNode));
    node->idx = obj->size;
    node->next = entry->indices;
    entry->indices = node;

    obj->size++;
    return notPresent;
}

bool randomizedCollectionRemove(RandomizedCollection* obj, int val) {
    HashEntry *entry = findEntry(obj, val);
    if (!entry || !entry->indices) return false;

    // 1. Get an index of the value to remove
    IndexNode *toRemove = entry->indices;
    int idx = toRemove->idx;
    entry->indices = toRemove->next;
    free(toRemove);

    // 2. Swap with last element in array to maintain O(1)
    int lastVal = obj->nums[obj->size - 1];
    obj->nums[idx] = lastVal;

    if (idx < obj->size - 1) {
        // Update the index of lastVal in the hash map
        HashEntry *lastEntry = findEntry(obj, lastVal);
        IndexNode *curr = lastEntry->indices;
        while (curr) {
            if (curr->idx == obj->size - 1) {
                curr->idx = idx;
                break;
            }
            curr = curr->next;
        }
    }

    obj->size--;
    return true;
}

int randomizedCollectionGetRandom(RandomizedCollection* obj) {
    return obj->nums[rand() % obj->size];
}

void randomizedCollectionFree(RandomizedCollection* obj) {
    // Free nodes and table in real implementation...
    free(obj->nums);
    free(obj->table);
    free(obj);
}
