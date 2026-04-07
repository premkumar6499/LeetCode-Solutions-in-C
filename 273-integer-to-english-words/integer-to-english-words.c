#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* units[] = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", 
                 "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
char* tens[] = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
char* thousands[] = {"", "Thousand", "Million", "Billion"};

void helper(int num, char* res) {
    if (num == 0) return;
    if (num < 20) {
        sprintf(res + strlen(res), "%s ", units[num]);
    } else if (num < 100) {
        sprintf(res + strlen(res), "%s ", tens[num / 10]);
        helper(num % 10, res);
    } else {
        sprintf(res + strlen(res), "%s Hundred ", units[num / 100]);
        helper(num % 100, res);
    }
}

char* numberToWords(int num) {
    if (num == 0) return "Zero";

    char* res = (char*)calloc(1000, sizeof(char));
    int i = 0;

    // We process chunks of 1000 from largest to smallest
    int chunk_divisors[] = {1000000000, 1000000, 1000, 1};
    char* chunk_names[] = {"Billion", "Million", "Thousand", ""};

    for (int j = 0; j < 4; j++) {
        int chunk = num / chunk_divisors[j];
        if (chunk > 0) {
            helper(chunk, res);
            if (strlen(chunk_names[j]) > 0) {
                sprintf(res + strlen(res), "%s ", chunk_names[j]);
            }
        }
        num %= chunk_divisors[j];
    }

    // Trim trailing space
    int len = strlen(res);
    if (len > 0 && res[len - 1] == ' ') res[len - 1] = '\0';

    return res;
}
