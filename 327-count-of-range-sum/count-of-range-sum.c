#include <stdlib.h>

long* temp;

int mergeSort(long* sums, int start, int end, int lower, int upper) {
    if (end - start <= 1) return 0;
    
    int mid = start + (end - start) / 2;
    int count = mergeSort(sums, start, mid, lower, upper) + 
                mergeSort(sums, mid, end, lower, upper);
    
    int j = mid, k = mid, t = mid;
    for (int i = start; i < mid; i++) {
        // Find the range [j, k) in the right half that satisfies the condition
        while (j < end && sums[j] - sums[i] < lower) j++;
        while (k < end && sums[k] - sums[i] <= upper) k++;
        count += k - j;
        
        // Merge step: fill temp array
        while (t < end && sums[t] < sums[i]) temp[t - mid + i] = sums[t++]; // Adjusting logic for C merge
    }
    
    // Standard merge to keep prefix sums sorted
    int i = start, r = mid, p = start;
    while (i < mid && r < end) {
        if (sums[i] < sums[r]) temp[p++] = sums[i++];
        else temp[p++] = sums[r++];
    }
    while (i < mid) temp[p++] = sums[i++];
    while (r < end) temp[p++] = sums[r++];
    
    for (int idx = start; idx < end; idx++) sums[idx] = temp[idx];
    
    return count;
}

int countRangeSum(int* nums, int numsSize, int lower, int upper) {
    long* sums = (long*)malloc((numsSize + 1) * sizeof(long));
    temp = (long*)malloc((numsSize + 1) * sizeof(long));
    sums[0] = 0;
    for (int i = 0; i < numsSize; i++) {
        sums[i + 1] = sums[i] + nums[i];
    }
    
    int result = mergeSort(sums, 0, numsSize + 1, lower, upper);
    
    free(sums);
    free(temp);
    return result;
}
