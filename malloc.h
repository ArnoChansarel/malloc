#ifndef MALLOC_H
# define MALLOC_H
#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>
#include <stdbool.h>
#include <string.h>

// #ifdef __x86_64__
//     # define POINTER_SIZE 8
// #elif __i386__
//     # define POINTER_SIZE 4
// #endif

# define TINY_THRESHOLD getpagesize() / 2
# define SMALL_TRESHOLD getpagesize()
# define align4(x) (((((x)-1)>>2)<<2)+4)

typedef struct s_chunk_header {

    size_t                  size;
    void                    *chunk;
    bool                    is_free;
    struct t_chunk_header   *next;

} t_chunk_header; // MIGHT NOT USE TYPEDEF HERE


# define HEADER_SIZE sizeof(t_chunk_header) 


typedef struct s_memory_zone {

    void            *start;
    size_t          size_total;
    t_chunk_header  *base_block;

}   t_memory_zone;

void    *malloc(size_t t);
void    free(void *ptr);
struct t_chunk_header *allocate_chunk(size_t t);

#endif