#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Helper: Custom binary search to find smallest element >= target (lower_bound)
int lower_bound(int* arr, int size, int target) {
    int left = 0, right = size;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] < target) left = mid + 1;
        else right = mid;
    }
    return left;
}

int maxSumSubmatrix(int** matrix, int matrixSize, int* matrixColSize, int k) {
    int rows = matrixSize;
    int cols = matrixColSize[0];
    int ans = INT_MIN;

    // Optimization: If rows >> cols, compress columns instead
    for (int i = 0; i < rows; i++) {
        int colSums[cols];
        for (int c = 0; c < cols; c++) colSums[c] = 0;

        for (int j = i; j < rows; j++) {
            for (int c = 0; c < cols; c++) colSums[c] += matrix[j][c];

            // 1D Problem: Max subarray sum <= k
            int sortedPrefixSums[cols + 1];
            sortedPrefixSums[0] = 0;
            int prefixSize = 1;
            int currSum = 0;

            for (int c = 0; c < cols; c++) {
                currSum += colSums[c];
                
                // Find smallest P such that P >= currSum - k
                int idx = lower_bound(sortedPrefixSums, prefixSize, currSum - k);
                if (idx < prefixSize) {
                    int rectSum = currSum - sortedPrefixSums[idx];
                    if (rectSum > ans) ans = rectSum;
                }

                // Maintain sorted order for binary search (Insertion Sort)
                int pos = lower_bound(sortedPrefixSums, prefixSize, currSum);
                for (int m = prefixSize; m > pos; m--) sortedPrefixSums[m] = sortedPrefixSums[m - 1];
                sortedPrefixSums[pos] = currSum;
                prefixSize++;
            }
        }
    }
    return ans;
}
