#include "libmx.h"

int mx_insertion_sort(char **arr, int size) {
    int count = 0; 
    char *buff;

    if (!arr || size <= 0)
        return -1;
    for (int i = 1, j = 0; i < size; i++) { 
        buff = arr[i]; 
        j = i - 1; 
        while (j >= 0 && mx_strlen_safe(arr[j]) > mx_strlen_safe(buff)) { 
            arr[j + 1] = arr[j]; 
            j--; 
            count++;
        } 
        arr[j + 1] = buff; 
    } 
    return count;
}
