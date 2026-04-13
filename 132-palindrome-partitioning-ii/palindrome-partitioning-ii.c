#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

int minCut(char *s) {
    int n = strlen(s);
    if (n <= 1) return 0;

    bool isPal[n][n];
    memset(isPal, 0, sizeof(isPal));

    // Pre-calculate all palindromic substrings
    for (int i = n - 1; i >= 0; i--) {
        for (int j = i; j < n; j++) {
            if (s[i] == s[j] && (j - i <= 2 || isPal[i + 1][j - 1])) {
                isPal[i][j] = true;
            }
        }
    }

    int dp[n];
    for (int i = 0; i < n; i++) {
        if (isPal[0][i]) {
            dp[i] = 0;
        } else {
            dp[i] = i; // Max possible cuts
            for (int j = 0; j < i; j++) {
                if (isPal[j + 1][i]) {
                    dp[i] = MIN(dp[i], dp[j] + 1);
                }
            }
        }
    }
    return dp[n - 1];
}