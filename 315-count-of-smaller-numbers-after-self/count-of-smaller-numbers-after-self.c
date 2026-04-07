#include <stdlib.h>

typedef struct {
    int val;
    int index;
} Element;

void merge(Element* arr, int left, int mid, int right, int* counts, Element* temp) {
    int i = left, j = mid + 1, k = left;
    int right_smaller_count = 0;

    while (i <= mid && j <= right) {
        if (arr[j].val < arr[i].val) {
            // Element from right is smaller; increment jump counter
            right_smaller_count++;
            temp[k++] = arr[j++];
        } else {
            // Element from left is placed; add current jump counter to its total
            counts[arr[i].index] += right_smaller_count;
            temp[k++] = arr[i++];
        }
    }

    // Process remaining elements
    while (i <= mid) {
        counts[arr[i].index] += right_smaller_count;
        temp[k++] = arr[i++];
    }
    while (j <= right) {
        temp[k++] = arr[j++];
    }

    for (i = left; i <= right; i++) arr[i] = temp[i];
}

void mergeSort(Element* arr, int left, int right, int* counts, Element* temp) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid, counts, temp);
    mergeSort(arr, mid + 1, right, counts, temp);
    merge(arr, left, mid, right, counts, temp);
}

int* countSmaller(int* nums, int numsSize, int* returnSize) {
    *returnSize = numsSize;
    int* counts = (int*)calloc(numsSize, sizeof(int));
    Element* arr = (Element*)malloc(numsSize * sizeof(Element));
    Element* temp = (Element*)malloc(numsSize * sizeof(Element));

    for (int i = 0; i < numsSize; i++) {
        arr[i].val = nums[i];
        arr[i].index = i;
    }

    mergeSort(arr, 0, numsSize - 1, counts, temp);

    free(arr);
    free(temp);
    return counts;
}
