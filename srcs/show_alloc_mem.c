#include "../includes/malloc.h"
#include "libft.h"

static unsigned long long hex_to_decimal(const void *address) {

    char hex_str[20];
    snprintf(hex_str, sizeof(hex_str), "%p", address);

    unsigned long long result;
    sscanf(hex_str, "%llx", &result);
    
    return result;
}


static void print_header(t_memory_zone *head) {

    switch (head->type) {
        case TINY:
            printf("TINY : %p\n", head->base_block);
            break;
        case SMALL:
            printf("SMALL : %p\n", head->base_block);
            break;
        case LARGE:
            printf("LARGE : %p\n", head->base_block);
            break;
    }
}


static void print_chunk_list(t_chunk_header *head) {

    // ADD A COUNT OF CLIENT ALLOC AND REAL ALLOC

    void *start = NULL;
    void *end = NULL;
    unsigned long long r1 = 0;
    unsigned long long r2 = 0;

    while (head) {
        if (!head->is_free) {
            start = head->data;
            end = head->data + head->size;
            r1 = hex_to_decimal(start);
            r2 = hex_to_decimal(end);

            printf("  %p - %p : %llu bytes\n", start, end, r2 - r1);
        }
        head = head->next;
    }
}

EXPORT
void show_alloc_mem() {

    printf("\n====SHOW ALLOCATIONS ========================\n");
    t_memory_zone   *head_mem = NULL;
    t_chunk_header  *head_chunk = NULL;

    if (base) {
        head_mem = base;
        while (head_mem) {
            
            if (head_mem->base_block) {
                print_header(head_mem);
                print_chunk_list(head_mem->base_block);
            }
            head_mem = head_mem->next;
        }
    } else {
        printf("No allocations.\n");
    }
    printf("================================================\n\n");

    return;
}