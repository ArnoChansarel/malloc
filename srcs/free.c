#include "../includes/malloc.h"

// The free() function deallocates the memory allocation pointed to by ptr. If ptr is a NULL pointer, no operation is performed.

static void defragment_memory(t_chunk_header *chunk) {

    size_t new_size = 0;
    bool defragmented = false;

    if (chunk->prev && chunk->prev->is_free) {// CHECK PREV FREE CHUNK

        new_size = chunk->size + HEADER_SIZE;
        if (chunk->next) {
            chunk->prev->next = chunk->next;
            chunk->next->prev = chunk->prev;
        } else {
            chunk->prev->next = NULL;
        }
        chunk = chunk->prev;
        new_size += chunk->size;

        chunk->size = new_size;
        ft_memset(chunk + HEADER_SIZE, 0x55, new_size);
        defragmented = true;
    }

    if (chunk->next && chunk->next->is_free) {// CHECK NEXT FREE CHUNK
        size_t next_chunk_size = HEADER_SIZE + chunk->next->size;
        new_size = chunk->size + next_chunk_size;
        if (chunk->next->next) {
            chunk->next->next->prev = chunk;
            chunk->next = chunk->next->next;
        } else {
            chunk->next = NULL;
        }
        chunk->size = new_size;
        ft_memset(chunk + HEADER_SIZE, 0x55, new_size);
        defragmented = true;
    }

    if (defragmented)// recursive is for small free bloc remaining after a realloc.
        defragment_memory(chunk);
    return;
}

EXPORT
void free(void *ptr) {

    if (ptr == NULL)
        return;

    t_memory_zone *temp_zone = NULL;
    t_chunk_header *chunk = (t_chunk_header *)((char*)ptr - HEADER_SIZE);

    size_t alloc_type = get_alloc_type(chunk->size);

    if (alloc_type == LARGE) {
        temp_zone = (t_memory_zone *)((char *)chunk - MEMORY_HEADER_SIZE);
        if (temp_zone->next) {
            // put zone out of list before freeing it
            temp_zone->prev->next = temp_zone->next;
            temp_zone->next->prev = temp_zone->prev;
        } else {
            temp_zone->prev->next = NULL;
        }

        size_t size_total = chunk->size + HEADER_SIZE + MEMORY_HEADER_SIZE;
        if (munmap(temp_zone, size_total)) {
            printf("Free failed\n");
        }
    } else {
        ft_memset(chunk + HEADER_SIZE, 0x55, chunk->size);
        chunk->is_free = true;
        t_chunk_header *temp_chunk = chunk;

        temp_zone = get_zone(chunk);
        temp_zone->size_left += chunk->size + HEADER_SIZE;
        defragment_memory(temp_chunk);
    }

    // Defragment the false freed memory :
    //      - for chunks in memzone, will aggregate free ones
    //      - for memzones, will munmap. Must add checker rigth after mmap() :
    //                 in case we free and [ 4096bytes memzone ][ 4096bytes memzone ]----F--R--E--E----[ 4096bytes memzone]
    //                  -> if adresse of pointer is before another zone, mmap used the free zone.
    //                  -> so must add it in list at the right place
    // Add a checker : in memory zone, if everything is free, then free the whole memzone --> maybe not efficient in a 
    //                                                                                  excessive malloc-free use scenario
}
