#include "../includes/malloc.h"

size_t  get_alloc_type(size_t t) {

    if (t <= SMALL_THRESHOLD)
        return (TINY);
    else if (t <= LARGE_THRESHOLD)
        return (SMALL);
    else {
        return (LARGE);
    }
}

t_memory_zone *get_zone(t_chunk_header *chunk) {
        
    t_chunk_header *head = chunk;
    while(head->prev){
        head = head->prev;
    }
    return (t_memory_zone *)((char *)head - MEMORY_HEADER_SIZE);
}

void init_chunk_header(t_memory_zone *zone, t_chunk_header *chunk, size_t t, t_chunk_header *prev, t_chunk_header *next) {

    chunk->size = t;
    chunk->is_free = false;
    chunk->prev = prev;
    chunk->next = next;

    if (zone)
        zone->size_left -= HEADER_SIZE + t;
    return;
}

t_chunk_header *reduce_chunk(t_memory_zone *zone, t_chunk_header *head, size_t t) {

    // Is a way to create a free block right after the selcted one and if there's
    // enough bytes to have 1 struct chunk_header set to free + at least 1byte of free memory. 
    // Otherwise it's splitting and we loose bytes forever

    size_t size_left_by_alloc = head->size - t;

    if (zone->type == LARGE) {

        size_t new_size = ((t + MEMORY_HEADER_SIZE + HEADER_SIZE + 4095) / 4096) * 4096;
        size_left_by_alloc = zone->size_total - HEADER_SIZE - new_size;

        if (munmap(zone + size_left_by_alloc, size_left_by_alloc)) {
            ft_printf("Free failed\n");
            return NULL;
        }
        show_alloc_mem();
        zone->size_left -= size_left_by_alloc;
        head->size -= size_left_by_alloc;
        return head;
    }

    if (size_left_by_alloc >= HEADER_SIZE + 1) {
        t_chunk_header *free_chunk = (t_chunk_header *)((char *)head + (t + HEADER_SIZE));
        size_t free_chunk_size = size_left_by_alloc - HEADER_SIZE;
        

        free_chunk->size = free_chunk_size;
        free_chunk->is_free = true;
        free_chunk->prev = head;
        free_chunk->next = head->next;
        if (head->next)
            head->next->prev = free_chunk;
        head->next = free_chunk;
    }

    init_chunk_header(zone, head, t, head->prev, head->next);
    return (head);
}

int check_memory_left(size_t new_size) {

    t_memory_zone       *head_mem = NULL;
    struct rlimit       limit;
    unsigned long long  real_alloc = 0;

    if (getrlimit(RLIMIT_NOFILE, &limit) != 0) {
        ft_printf("Error getting memory limit.\n");
        return 1;
    }

    if (base) {
        head_mem = base;
        while (head_mem) {
            real_alloc += MEMORY_HEADER_SIZE + head_mem->size_total;
            head_mem = head_mem->next;
        }
    }

    // printf("Memory used : %llu/%llu  | Trying to add a total of %lu\n", real_alloc, limit.rlim_max, new_size);

    if (real_alloc + new_size > limit.rlim_max) {
        ft_printf("Memory limit reached.\n");
        return 1;
    }
    return 0;
}
