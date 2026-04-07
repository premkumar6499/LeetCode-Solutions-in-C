#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **results;
int resSize;

void backtrack(char* num, int target, int index, long currentVal, long lastVal, char* expr, int exprLen) {
    if (num[index] == '\0') {
        if (currentVal == target) {
            results[resSize] = strdup(expr);
            resSize++;
        }
        return;
    }

    char part[20];
    for (int i = index; num[i] != '\0'; i++) {
        // Leading zero check: if the number starts with '0', it can only be "0"
        if (i > index && num[index] == '0') break;

        int len = i - index + 1;
        strncpy(part, num + index, len);
        part[len] = '\0';
        long val = atol(part);

        if (index == 0) {
            // First number, no operator
            backtrack(num, target, i + 1, val, val, part, len);
        } else {
            // Addition
            char nextExpr[100];
            sprintf(nextExpr, "%s+%s", expr, part);
            backtrack(num, target, i + 1, currentVal + val, val, nextExpr, strlen(nextExpr));

            // Subtraction
            sprintf(nextExpr, "%s-%s", expr, part);
            backtrack(num, target, i + 1, currentVal - val, -val, nextExpr, strlen(nextExpr));

            // Multiplication
            sprintf(nextExpr, "%s*%s", expr, part);
            // Undo lastVal and apply multiplication
            backtrack(num, target, i + 1, (currentVal - lastVal) + (lastVal * val), lastVal * val, nextExpr, strlen(nextExpr));
        }
    }
}

char ** addOperators(char * num, int target, int* returnSize) {
    results = (char**)malloc(sizeof(char*) * 10000); // Rough estimate
    resSize = 0;
    char expr[100] = "";
    
    if (strlen(num) > 0) {
        backtrack(num, target, 0, 0, 0, expr, 0);
    }
    
    *returnSize = resSize;
    return results;
}
