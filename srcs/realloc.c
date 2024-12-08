#include "../includes/malloc.h"

// The realloc() function tries  to change the size of the allocation pointed to by ptr to size, and returns ptr.
// If there is not enough room to enlarge the memory allocation pointed to by ptr, realloc() creates a new allocation,
// copies as much of the old data pointed to by ptr as will fit to the new allocation, frees the old allocation, and 
// returns a pointer to the allocated memory. 
// If ptr is NULL, realloc() is identical to a call to malloc() for size bytes.
// If size is zero and ptr is not NULL, a new, minimum sized object is allocated and the original object is freed.
// When extending a region allocated with calloc(3), realloc(3) does not guarantee that the additional memory is
// also zero-filled.

static t_chunk_header *find_alloc(void *ptr) {

    t_memory_zone *head_zone;
    t_chunk_header *head_chunk;

    head_zone = base;
    while (head_zone) {
        
        head_chunk = head_zone->base_block;
        while (head_chunk) {
            if (ptr == head_chunk->data)
                return head_chunk;
            head_chunk = head_chunk->next;
        }
        head_zone = head_zone->next;
    }
    return NULL;
}

EXPORT
void *realloc(void *ptr, size_t size) {
    
    void *rtr;

    if (ptr == NULL) {
        return malloc(size);
    } else if (size == 0) {
        free(ptr);
        return malloc(1);
    }

    t_chunk_header *chunk = find_alloc(ptr);
    if (chunk == NULL) {
        printf("Error : Pointer hasn't been allocated by Malloc\n");
        return NULL;
    }
    
    size_t alloc_type = get_alloc_type(chunk->size);
    if ( size == chunk->size ) {
        // Same length, retruning same ptr
        return ptr;
    }
    else if ( size < chunk->size ) {
        // if keep same chunk but decreased
        t_memory_zone *zone = get_zone(chunk);
        reduce_chunk(zone, chunk, size);
        return chunk->data;
    }
    else if ( size > chunk->size) {
        // if must allocate a bigger one somewhere else
        rtr = malloc(size);
        ft_memmove(rtr, chunk->data, chunk->size);
        free(chunk->data);
        return rtr;
    } 
    return NULL;
}
