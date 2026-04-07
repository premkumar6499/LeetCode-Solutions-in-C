#include <stdio.h>

int countDigitOne(int n) {
    if (n <= 0) return 0;
    
    long count = 0;
    for (long i = 1; i <= n; i *= 10) {
        long prefix = n / (i * 10);
        long current = (n / i) % 10;
        long suffix = n % i;
        
        if (current == 0) {
            count += prefix * i;
        } else if (current == 1) {
            count += (prefix * i) + (suffix + 1);
        } else {
            count += (prefix + 1) * i;
        }
    }
    
    return (int)count;
}
