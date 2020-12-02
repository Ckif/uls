#include "libmx.h"

void mx_pop_front(t_list **head) {
    t_list *tmp = NULL;

	if (head != NULL && *head != NULL) {
		tmp = (*head)->next;
		free(*head);
		*head = tmp;
	}
}
