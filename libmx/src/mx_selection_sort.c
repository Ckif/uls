#include "libmx.h"

int mx_selection_sort(char **arr, int size) {
    int min;
    int count = 0;
    int flag = 0;
    char *buff;

    if (!arr || size <= 0)
        return -1;
    for (int i = 0; i < size-1; i++) { 
        min = i; 
        for (int j = i+1; j < size; j++)
            if (mx_strlen_safe(arr[j]) < mx_strlen_safe(arr[min])
                || (mx_strlen_safe(arr[j]) == mx_strlen_safe(arr[min]) 
                && mx_strcmp(arr[j], arr[min]) < 0)) {
                min = j;
                flag = 1;
            }
        buff = arr[min];
        arr[min] = arr[i];
        arr[i] = buff;
        if(flag == 1)
            count++;
        flag = 0;
    }
    return count;
}
