#include "../includes/malloc.h"

static void print_header(t_memory_zone *head) {

    switch (head->type) {
        case TINY:
            ft_printf("TINY : %p\n", head->base_block);
            break;
        case SMALL:
            ft_printf("SMALL : %p\n", head->base_block);
            break;
        case LARGE:
            ft_printf("LARGE : %p\n", head->base_block);
            break;
        default:
            ft_printf("Unknown type found\n");
            break;
    }
}

size_t ptr_diff(void *addr1, void *addr2) {
    ptrdiff_t diff = (char*)addr1 - (char*)addr2;
    return (diff < 0) ? -diff : diff;
}

static void print_chunk_list(t_chunk_header *head, size_t *client_alloc, bool free_flag) {

    void *start = NULL;
    void *end = NULL;
    unsigned long long res = 0;

    while (head) {
            if (!head->is_free || (head->is_free && free_flag)) {
                start = (void *)((char *)head + HEADER_SIZE);
                end = (void *)((char *)head + HEADER_SIZE + head->size);
                res = ptr_diff(start, end);

                ft_printf("  %p - %p : ", start, end);
                ft_itoa_base((size_t)res, 10, 0, 0);
                ft_printf(" bytes");
                
                if (head->is_free && free_flag)
                    ft_printf(" (free)");
                else
                    *client_alloc += res;
                ft_printf("\n");
            }
        head = head->next;
    }
}

void print_main_header() {
    ft_printf("\n==== SHOW ALLOCATIONS ==========================\n");
    ft_printf("Memory Zone Size : ");
    ft_itoa_base(MEMORY_HEADER_SIZE, 10, 2, 0);
    ft_printf("   | Chunk Header Size : ");
    ft_itoa_base(HEADER_SIZE, 10, 2, 0);
    ft_printf("\nMemory Page Size : ");
    ft_itoa_base(PAGE_SIZE, 10, 2, 0);
    ft_printf("\n-\n");
}

EXPORT
void show_alloc_mem() {

    t_memory_zone   *head_mem = NULL;
    bool            is_alloc = false;
    bool            free_flag = true;// set to true to display free chunk also
    size_t          client_alloc = 0;
    size_t          real_alloc = 0;

    print_main_header();
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
        ft_printf("No allocations.\n");

    ft_printf("-\nTotal client allocation : ");
    ft_itoa_base(client_alloc, 10, 2, 0);
    ft_printf(" bytes\n");
    // printf("Total real allocation   : %lu bytes\n", real_alloc);
    ft_printf("================================================\n\n");

    return;
}