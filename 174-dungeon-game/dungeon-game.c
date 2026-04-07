#include <stdio.h>
#include <stdlib.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int calculateMinimumHP(int** dungeon, int dungeonSize, int* dungeonColSize) {
    int m = dungeonSize;
    int n = dungeonColSize[0];
    
    // Using a 2D array for clarity, though 1D optimization is possible
    int dp[m][n];

    for (int i = m - 1; i >= 0; i--) {
        for (int j = n - 1; j >= 0; j--) {
            if (i == m - 1 && j == n - 1) {
                // Base case: Princess room
                dp[i][j] = MAX(1, 1 - dungeon[i][j]);
            } else if (i == m - 1) {
                // Bottom row: can only move right
                dp[i][j] = MAX(1, dp[i][j+1] - dungeon[i][j]);
            } else if (j == n - 1) {
                // Rightmost column: can only move down
                dp[i][j] = MAX(1, dp[i+1][j] - dungeon[i][j]);
            } else {
                // Choose the path that requires less health
                int res = MIN(dp[i+1][j], dp[i][j+1]);
                dp[i][j] = MAX(1, res - dungeon[i][j]);
            }
        }
    }

    return dp[0][0];
}
