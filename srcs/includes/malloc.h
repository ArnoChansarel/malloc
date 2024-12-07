#ifndef MALLOC_H
# define MALLOC_H
#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>
#include <stdbool.h>
#include <string.h>
#include "../../libft/libft.h"

# define TINY_ZONE_SIZE 4
# define SMALL_ZONE_SIZE 32
# define align4(x) (((((x)-1)>>2)<<2)+4)

enum zone_type {
    TINY,
    SMALL,
    LARGE
};

# define PAGE_SIZE (size_t)getpagesize()
# define SMALL_THRESHOLD PAGE_SIZE / 12 //    --> 308bytes
# define LARGE_THRESHOLD PAGE_SIZE - 1//        --> 4095bytes
# define TINY_FACTOR 10
# define SMALL_FACTOR 120

// --> We get 120max allocations for each zones

typedef struct s_chunk_header {

    size_t                  size;
    bool                    is_free;
    struct s_chunk_header   *prev;
    struct s_chunk_header   *next;
    char                    data[];

} t_chunk_header;

typedef struct s_memory_zone {

    enum zone_type          type;
    size_t                  size_total;
    size_t                  size_left;
    struct s_memory_zone    *prev;
    struct s_memory_zone    *next;
    t_chunk_header          *base_block;

}   t_memory_zone;

# define HEADER_SIZE sizeof(t_chunk_header)
# define MEMORY_HEADER_SIZE sizeof(t_memory_zone)
# define EXPORT __attribute__((visibility("default")))


extern t_memory_zone *base;

// FUNCTIONS
void    *malloc(size_t t);
void    free(void *ptr);
void    *realloc(void *ptr, size_t size);
void    show_alloc_mem();

// SHARED FUNCTIONS
size_t  get_alloc_type(size_t t);
t_memory_zone *get_zone(t_chunk_header *chunk);
t_chunk_header *reduce_chunk(t_memory_zone *zone, t_chunk_header *head, size_t t);
void init_chunk_header(t_memory_zone *zone, t_chunk_header *chunk, size_t t, t_chunk_header *prev, t_chunk_header *next);

#endif

