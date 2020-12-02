#include "libmx.h"

int mx_binary_search(char **arr, int size, const char *s, int *count) {
    int left = 0;
    int right = size - 1;
    int mid;
    int arr_index;

    while (left <= right) {
        mid = (left + right) / 2;
        (*count)++;
        if (mx_strcmp(arr[mid], s) == 0) {
            arr_index = mid;
            return arr_index;
        }
        if (mx_strcmp(arr[mid], s) > 0)
            right = mid - 1;
        else
            left = mid + 1;
    }
    (*count) = 0;
    return -1;
}
