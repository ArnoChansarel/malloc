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

unsigned long long hex_to_decimal(const void *address) {

    char hex_str[20];
    snprintf(hex_str, sizeof(hex_str), "%p", address);

    unsigned long long result;
    sscanf(hex_str, "%llx", &result);
    
    return result;
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

    zone->size_left -= HEADER_SIZE + t;
    return;
}


t_chunk_header *reduce_chunk(t_memory_zone *zone, t_chunk_header *head, size_t t) {

    size_t size_left_by_alloc = head->size - t;

    if (zone->type == LARGE) {

        size_t new_size = ((t + MEMORY_HEADER_SIZE + HEADER_SIZE + 4095) / 4096) * 4096;
        size_left_by_alloc = zone->size_total - HEADER_SIZE - new_size;

        if (munmap(zone + size_left_by_alloc, size_left_by_alloc)) {
            printf("Free failed\n");
        }
        zone->size_total -= size_left_by_alloc;
        head->size -= size_left_by_alloc;
        show_alloc_mem();
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
