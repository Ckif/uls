#include "libmx.h"

t_list *mx_create_node(void *data) {
    t_list *result = NULL;

    if (data) {
        result = (t_list *)malloc(sizeof(t_list));
        result->data = data;
        result->next = NULL;
    }
    return result;
}
