#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_WORDS 30000
#define ALPHABET_SIZE 26

typedef struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    char *word;
} TrieNode;

TrieNode* createNode() {
    TrieNode *node = (TrieNode *)calloc(1, sizeof(TrieNode));
    return node;
}

void insert(TrieNode *root, char *word) {
    TrieNode *curr = root;
    for (int i = 0; word[i]; i++) {
        int idx = word[i] - 'a';
        if (!curr->children[idx]) curr->children[idx] = createNode();
        curr = curr->children[idx];
    }
    curr->word = word;
}

void dfs(char** board, int r, int c, int rows, int cols, TrieNode *node, char **res, int *resSize) {
    char ch = board[r][c];
    if (ch == '#' || !node->children[ch - 'a']) return;

    node = node->children[ch - 'a'];
    if (node->word) {
        res[(*resSize)++] = node->word;
        node->word = NULL; // Avoid duplicate results
    }

    board[r][c] = '#'; // Mark as visited
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    for (int i = 0; i < 4; i++) {
        int nr = r + dr[i], nc = c + dc[i];
        if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
            dfs(board, nr, nc, rows, cols, node, res, resSize);
        }
    }
    board[r][c] = ch; // Backtrack
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** findWords(char** board, int boardSize, int* boardColSize, char ** words, int wordsSize, int* returnSize) {
    TrieNode *root = createNode();
    for (int i = 0; i < wordsSize; i++) insert(root, words[i]);

    char **res = (char **)malloc(MAX_WORDS * sizeof(char *));
    *returnSize = 0;

    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardColSize[i]; j++) {
            dfs(board, i, j, boardSize, boardColSize[i], root, res, returnSize);
        }
    }
    return res;
}
