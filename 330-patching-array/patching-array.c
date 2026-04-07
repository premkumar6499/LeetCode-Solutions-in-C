#include <stdio.h>

int minPatches(int* nums, int numsSize, int n) {
    long miss = 1;
    int patches = 0;
    int i = 0;

    while (miss <= n) {
        if (i < numsSize && nums[i] <= miss) {
            // Existing number helps extend the range
            miss += nums[i];
            i++;
        } else {
            // Must patch the number 'miss' to greedily extend the range
            miss += miss;
            patches++;
        }
    }

    return patches;
}
