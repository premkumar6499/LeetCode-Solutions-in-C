#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct HashNode {
    char *key;
    int index;
    struct HashNode *next;
} HashNode;

bool isPalindrome(char *s, int left, int right) {
    while (left < right) {
        if (s[left++] != s[right--]) return false;
    }
    return true;
}

char* strReverse(char *s) {
    int n = strlen(s);
    char *rev = malloc(n + 1);
    for (int i = 0; i < n; i++) rev[i] = s[n - 1 - i];
    rev[n] = '\0';
    return rev;
}

// Simple hash function and table logic
unsigned int hash(char *s, int size) {
    unsigned int h = 0;
    while (*s) h = h * 31 + *s++;
    return h % size;
}

void insert(HashNode **table, int size, char *key, int index) {
    unsigned int h = hash(key, size);
    HashNode *node = malloc(sizeof(HashNode));
    node->key = key;
    node->index = index;
    node->next = table[h];
    table[h] = node;
}

int find(HashNode **table, int size, char *key) {
    unsigned int h = hash(key, size);
    HashNode *curr = table[h];
    while (curr) {
        if (strcmp(curr->key, key) == 0) return curr->index;
        curr = curr->next;
    }
    return -1;
}

int** palindromePairs(char **words, int wordsSize, int* returnSize, int** returnColumnSizes) {
    int tableSize = wordsSize * 2;
    HashNode **table = calloc(tableSize, sizeof(HashNode*));
    for (int i = 0; i < wordsSize; i++) {
        insert(table, tableSize, strReverse(words[i]), i);
    }

    int **res = malloc(wordsSize * 100 * sizeof(int*));
    *returnSize = 0;

    for (int i = 0; i < wordsSize; i++) {
        int n = strlen(words[i]);
        for (int j = 0; j <= n; j++) {
            // Case 1: Prefix is palindrome, look for reversed suffix
            if (isPalindrome(words[i], 0, j - 1)) {
                int k = find(table, tableSize, words[i] + j);
                if (k != -1 && k != i) {
                    res[*returnSize] = malloc(2 * sizeof(int));
                    res[*returnSize][0] = k;
                    res[*returnSize][1] = i;
                    (*returnSize)++;
                }
            }
            // Case 2: Suffix is palindrome, look for reversed prefix
            if (j < n && isPalindrome(words[i], j, n - 1)) {
                char temp = words[i][j];
                words[i][j] = '\0';
                int k = find(table, tableSize, words[i]);
                words[i][j] = temp;
                if (k != -1 && k != i) {
                    res[*returnSize] = malloc(2 * sizeof(int));
                    res[*returnSize][0] = i;
                    res[*returnSize][1] = k;
                    (*returnSize)++;
                }
            }
        }
    }

    *returnColumnSizes = malloc(*returnSize * sizeof(int));
    for (int i = 0; i < *returnSize; i++) (*returnColumnSizes)[i] = 2;
    return res;
}
