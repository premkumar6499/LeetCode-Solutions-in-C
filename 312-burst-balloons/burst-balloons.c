#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int maxCoins(int* nums, int numsSize) {
    // 1. Create a new array with padding 1s at the boundaries
    int n = numsSize + 2;
    int* val = (int*)malloc(n * sizeof(int));
    val[0] = 1;
    val[n - 1] = 1;
    for (int i = 0; i < numsSize; i++) {
        val[i + 1] = nums[i];
    }

    // 2. DP table where dp[i][j] is the max coins in range (i, j)
    int** dp = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        dp[i] = (int*)calloc(n, sizeof(int));
    }

    // 3. Iterate through lengths of intervals
    for (int len = 2; len < n; len++) { // len is distance between i and j
        for (int i = 0; i < n - len; i++) {
            int j = i + len;
            // Iterate through every possible last balloon 'k' in the interval
            for (int k = i + 1; k < j; k++) {
                int total = val[i] * val[k] * val[j];
                total += dp[i][k] + dp[k][j];
                dp[i][j] = MAX(dp[i][j], total);
            }
        }
    }

    int result = dp[0][n - 1];

    // Clean up
    for (int i = 0; i < n; i++) free(dp[i]);
    free(dp);
    free(val);

    return result;
}
