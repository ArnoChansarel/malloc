#include "../includes/malloc.h"
#include "libft.h"


void show_alloc_mem() {

    t_memory_zone   *head_mem = NULL;
    t_chunk_header  *head_chunk = NULL;

    if (base) {
        head_mem = base;
        while (head_mem) {
            

            head_mem = head_mem->next;
        }
    } else {
        printf("No allocations.\n");
    }

    return;
}