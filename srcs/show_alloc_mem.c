#include "../includes/malloc.h"
#include "libft.h"

// static size_t hex_to_decimal(const void *address) {

//     char hex_str[20];
//     snprintf(hex_str, sizeof(hex_str), "%p", address);

//     size_t result;
//     sscanf(hex_str, "%llx", &result);
    
//     return result;
// }

static void print_header(t_memory_zone *head) {

    switch (head->type) {
        case TINY:
            printf("TINY : %p\n", head->base_block);
            break;
        case SMALL:
            printf("SMALL : %p\n", head->base_block);
            break;
        case LARGE:
            if (head->prev && head->prev->type != LARGE)
                printf("LARGE : %p\n", head->base_block);
            break;
    }
}

static void print_chunk_list(t_chunk_header *head, size_t *client_alloc, bool free_flag) {

    void *start = NULL;
    void *end = NULL;
    unsigned long long r1 = 0;
    unsigned long long r2 = 0;
    unsigned long long res = 0;


    while (head) {
            if (!head->is_free || (head->is_free && free_flag)) {
                start = head->data;
                end = head->data + head->size;
                r1 = hex_to_decimal(start);
                r2 = hex_to_decimal(end);

                res = r2 - r1;

                printf("  %p - %p : %llu bytes", start, end, res);
                if (head->is_free && free_flag)
                    printf(" (free)");
                else
                    *client_alloc += res;
                printf("\n");
            }
        head = head->next;
    }
}

EXPORT
void show_alloc_mem() {

    printf("\n==== SHOW ALLOCATIONS ==========================\n");
    printf("Memory Zone Size : %lu | Chunk Header Size : %lu\n-\n", MEMORY_HEADER_SIZE, HEADER_SIZE);
    t_memory_zone   *head_mem = NULL;
    t_chunk_header  *head_chunk = NULL;
    bool            is_alloc = false;
    bool            free_flag = true;// set to true to display free chunk also
    size_t          client_alloc = 0;
    size_t          real_alloc = 0;

    if (base) {
        head_mem = base;
        while (head_mem) {     
            if (head_mem && head_mem->size_left < head_mem->size_total) {

                print_header(head_mem);
                print_chunk_list(head_mem->base_block, &client_alloc, free_flag);
                is_alloc = true;
                real_alloc += MEMORY_HEADER_SIZE + head_mem->size_total;
            }
            head_mem = head_mem->next;
        }
    }
    if (is_alloc == false)
        printf("No allocations.\n");

    printf("-\nTotal client allocation : %lu bytes\n", client_alloc);
    // printf("Total real allocation   : %lu bytes\n", real_alloc);
    printf("================================================\n\n");

    return;
}