#ifndef MALLOC_H
# define MALLOC_H
#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>
#include <stdbool.h>
#include <string.h>

# define TINY_ZONE_SIZE 4
# define SMALL_ZONE_SIZE 32
# define align4(x) (((((x)-1)>>2)<<2)+4)

enum zone_type {
    TINY,
    SMALL,
    LARGE
};
// Tiny :
// size = 4*4096 = 16384
// moins memory_zone header = 16384 -32 = 16352
// diviser en chunks : 112
// pour des chunks de 146bytes
// moins la size du header 146 - 24 = 122bytesmax par alloc. Sinon SMALL


# define SMALL_THRESHOLD (size_t)(getpagesize() / 32) // --> 128bytes
# define LARGE_THRESHOLD (size_t)getpagesize()//        --> 4096bytes

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
    size_t                  size_total; // both might be [unsigned long long], since
    size_t                  size_left; // it's bytes we can expect a large amount of it
    struct s_memory_zone    *prev;
    struct s_memory_zone    *next;
    t_chunk_header          *base_block;

}   t_memory_zone;

# define HEADER_SIZE sizeof(t_chunk_header)
# define MEMZONE_HEADER sizeof(t_memory_zone)
# define PAGE_SIZE (size_t)getpagesize()

extern t_memory_zone *base;

void    *malloc(size_t t);
void    free(void *ptr);

void    show_alloc_mem();

size_t  get_alloc_type(size_t t);

#endif