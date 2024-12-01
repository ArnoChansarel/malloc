#include "../includes/malloc.h"

EXPORT
void free(void *ptr) {

    t_chunk_header *chunk = (t_chunk_header*)((char*)ptr - HEADER_SIZE);

    printf("In FREE function-------------------------------------------------------------------------\n");
    printf("size : %lu\n", chunk->size);
    printf("Data : %s\n", chunk->data);

    if (chunk->size >= PAGE_SIZE) {
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

    // Defragment the false freed memory
    // Add a checker : in memory zone, if everything is free, then free the whole memzone
}
