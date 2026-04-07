#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **sentences;
    int count;
} MemoEntry;

MemoEntry *memo;
char **words;
int wordsSize;

// Recursive function to find all word segmentations
MemoEntry solve(const char *s, int sLen) {
    if (memo[sLen].sentences != NULL) return memo[sLen];
    
    MemoEntry res = {NULL, 0};

    // Base case: empty string reached
    if (sLen == 0) {
        res.sentences = (char **)malloc(sizeof(char *));
        res.sentences[0] = strdup("");
        res.count = 1;
        return res;
    }

    for (int i = 0; i < wordsSize; i++) {
        int wLen = strlen(words[i]);
        // If current word matches the start of the string
        if (sLen >= wLen && strncmp(s, words[i], wLen) == 0) {
            MemoEntry sub = solve(s + wLen, sLen - wLen);
            if (sub.count > 0) {
                res.sentences = (char **)realloc(res.sentences, (res.count + sub.count) * sizeof(char *));
                for (int j = 0; j < sub.count; j++) {
                    // +1 for space (if not last word), +1 for null terminator
                    int newLen = wLen + strlen(sub.sentences[j]) + 2; 
                    res.sentences[res.count] = (char *)malloc(newLen);
                    
                    if (strlen(sub.sentences[j]) == 0) {
                        strcpy(res.sentences[res.count], words[i]);
                    } else {
                        sprintf(res.sentences[res.count], "%s %s", words[i], sub.sentences[j]);
                    }
                    res.count++;
                }
            }
        }
    }
    memo[sLen] = res;
    return res;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** wordBreak(char * s, char ** wordDict, int wordDictSize, int* returnSize) {
    int n = strlen(s);
    wordsSize = wordDictSize;
    words = wordDict;
    
    // Create memoization table for suffix lengths 0 to n
    memo = (MemoEntry *)calloc(n + 1, sizeof(MemoEntry));
    
    MemoEntry finalRes = solve(s, n);
    *returnSize = finalRes.count;
    
    char **result = finalRes.sentences;
    free(memo); // Only free the table, the actual strings are returned
    return result;
}
