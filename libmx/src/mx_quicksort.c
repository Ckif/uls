#include "libmx.h"

// ----------Another implementation, works as well-----------//
// static int partition (char **arr, int left, int right, int *count) {  
//     int i = left - 1;
//     int pivot = (right +  left) / 2;

//     mx_swap_str(&arr[right], &arr[pivot]);
//     for (int j = left; j < right; j++)
//         if (mx_strlen(arr[j]) < mx_strlen(arr[right])) {
//             i++;
//             if (i != j || j == pivot) {
//                 mx_swap_str(&arr[i], &arr[j]);
//                 (*count)++;
//             }
//         }
//     mx_swap_str(&arr[i + 1], &arr[right]);
//     return i + 1; 
// }
static int partition (char **arr, int l, int r, int *count) {  
    int p = (r + l) / 2;

    while (l < r) {
        for (;mx_strlen(arr[l]) < mx_strlen(arr[p]) && l < p; l++);
        for (;mx_strlen(arr[r]) >= mx_strlen(arr[p]) && r > p; r--);
        if (l < r && mx_strlen(arr[l]) > mx_strlen(arr[r])) {
            p = l * (p == r) + r * (p == l) + p * (p != l && p != r);
            mx_swap_str(&arr[l], &arr[r]);
            (*count)++;
        }
        l += 1 * (l != p);
        r -= 1 * (r != p);
    }
    return p;
}
int mx_quicksort(char **arr, int left, int right) {
    int p;
    int count = 0;

    if (arr == NULL)
        return -1;
    if (left < right) {
        p = partition(arr, left, right, &count);
        count += mx_quicksort(arr, left, p - 1);
        count += mx_quicksort(arr, p + 1, right);
    }
    return count;
}
