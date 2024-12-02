#include "../includes/malloc.h"

EXPORT

void defragment_memory(t_memory_zone *zone) {
    return;
}


void free(void *ptr) {

    t_memory_zone *temp_zone = NULL;
    t_chunk_header *chunk = (t_chunk_header*)((char*)ptr - HEADER_SIZE);

    printf("In FREE function-------------------------------------------------------------------------\n");
    printf("size : %lu\n", chunk->size);
    printf("Data : %s\n", chunk->data);
    size_t alloc_type = get_alloc_type()

    if (alloc_type == LARGE) {

        temp_zone = (temp_zone *)((char *)chunk - sizeof(MEMZONE_HEADER));
        if (temp_zone->next) {
            // put zone out of list before freeing it
        }

        if (munmap(chunk, chunk->size + HEADER_SIZE)) {
            printf("Free failed\n");
        } else {
            printf("Freed !\n");
        }
    } else {
        printf("Freeing memory allocatin :\n");
        bzero(chunk + HEADER_SIZE, chunk->size);
        chunk->is_free = true;
        printf("Chunk at address [%p] freed\n", chunk);
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
