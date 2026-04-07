#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
    if (numsSize == 0) {
        *returnSize = 0;
        return NULL;
    }

    int* result = (int*)malloc((numsSize - k + 1) * sizeof(int));
    int* deque = (int*)malloc(numsSize * sizeof(int)); // Stores indices
    int head = 0, tail = 0;
    int resIdx = 0;

    for (int i = 0; i < numsSize; i++) {
        // 1. Remove indices of elements smaller than current (from back)
        while (tail > head && nums[deque[tail - 1]] <= nums[i]) {
            tail--;
        }
        
        // 2. Add current index
        deque[tail++] = i;

        // 3. Remove index if it's outside the window (from front)
        if (deque[head] <= i - k) {
            head++;
        }

        // 4. Start adding to result once first window is complete
        if (i >= k - 1) {
            result[resIdx++] = nums[deque[head]];
        }
    }

    *returnSize = resIdx;
    free(deque);
    return result;
}
