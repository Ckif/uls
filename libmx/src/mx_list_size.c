#include "libmx.h"

int mx_list_size(t_list *list) {
    t_list *temp = list;
    int size = 0;

    if (list != NULL)
        for (; temp != NULL; size++) 
            temp = temp->next;
    return size;
}  
