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


# define SMALL_THRESHOLD (size_t)(getpagesize() / 12) //    --> 308bytes
# define LARGE_THRESHOLD (size_t)getpagesize() - 1//        --> 4095bytes
# define TINY_FACTOR 10
# define SMALL_FACTOR 120

// --> We get 120 allocations for each zones

#define EXPORT __attribute__((visibility("default")))

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
# define PAGE_SIZE (size_t)getpagesize()

extern t_memory_zone *base;

void    *malloc(size_t t);
void    free(void *ptr);
void    *realloc(void *ptr, size_t size);
void    show_alloc_mem();

size_t  get_alloc_type(size_t t);

#endif