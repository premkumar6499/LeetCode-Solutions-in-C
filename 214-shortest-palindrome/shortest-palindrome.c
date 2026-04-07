#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * shortestPalindrome(char * s) {
    int n = strlen(s);
    if (n <= 1) return s;

    // Create reverse of s
    char *rev = (char *)malloc(n + 1);
    for (int i = 0; i < n; i++) rev[i] = s[n - 1 - i];
    rev[n] = '\0';

    // Combine: s + "#" + rev
    int combinedLen = 2 * n + 1;
    char *temp = (char *)malloc(combinedLen + 1);
    sprintf(temp, "%s#%s", s, rev);

    // KMP LPS (Longest Prefix Suffix) array
    int *lps = (int *)calloc(combinedLen, sizeof(int));
    for (int i = 1; i < combinedLen; i++) {
        int j = lps[i - 1];
        while (j > 0 && temp[i] != temp[j]) {
            j = lps[j - 1];
        }
        if (temp[i] == temp[j]) j++;
        lps[i] = j;
    }

    int longestPalPrefixLen = lps[combinedLen - 1];
    free(temp);
    free(lps);

    // The characters to add are the suffix of rev starting after the palindrome prefix
    int addLen = n - longestPalPrefixLen;
    char *result = (char *)malloc(addLen + n + 1);
    
    strncpy(result, rev, addLen); // Copy the needed part from reversed string
    strcpy(result + addLen, s);   // Append original string
    
    free(rev);
    return result;
}
