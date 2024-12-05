
#include "../includes/malloc.h"
#include "libft.h"


//
//      [chnk | data   ][chnk | data][chnk | data   ][chnk | data     ][chnk | data ][chnk | data       ][chnk | data      ]
//      |___________________________________________||______________________________||_____________________________________|
//            zone TINY (pre allocated)                 zone SMALL (pre allocated)        zone LARGE      

// allocate TINY and SMALL when launching
// create a LARGE zone if needed, and add allocations in it if needed.
// if a new TINY or SMALL zone must be created, LARGE zone must not grow more. !! Only if last in linkedlist !!
// defragmenting will work only in each zone.


t_memory_zone *base = NULL;

unsigned long long hex_to_decimal(const void *address) {

    char hex_str[20];
    snprintf(hex_str, sizeof(hex_str), "%p", address);

    unsigned long long result;
    sscanf(hex_str, "%llx", &result);
    
    return result;
}

static t_memory_zone *create_zone(size_t type, size_t large_alloc) {

    t_memory_zone *zone = NULL;
    size_t total_size = 0;

    if (type == TINY) {
        total_size = PAGE_SIZE * TINY_FACTOR;
    } else if (type == SMALL) {
        total_size = PAGE_SIZE * SMALL_FACTOR;
    } else if (type == LARGE) {
        total_size = sizeof(t_memory_zone) + sizeof(t_chunk_header) + large_alloc;
    }

    zone = mmap(NULL, total_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (zone == MAP_FAILED) {
        printf("Create Zone failed\n");
        return NULL;
    }

    zone->type = type;
    zone->size_total = total_size - sizeof(t_memory_zone);
    zone-> size_left = zone->size_total;
    zone->prev = NULL;
    zone->next = NULL;
    zone->base_block = NULL;

    return (zone);
}

static void     add_zone(t_memory_zone *zone) {
    
    t_memory_zone *head = NULL;
    int i = 0;

    if (base == NULL) {
        base = zone;
    } 
    else {
        head = base;
        while (head->next) {
            i++;
            if (!head->next)
                break;
            head = head->next;
        }
        head->next = zone;
        zone->prev = head;
    }
    return;
}

static t_memory_zone *get_zone(size_t alloc_type, size_t t) {

    t_memory_zone *head = base;

    if (head && alloc_type != LARGE) {
        do {
            if ((size_t)head->type == alloc_type) {
                // printf("A zone has been found, ");
                
                size_t chunk_size = sizeof(t_chunk_header) + t;
                if (chunk_size > head->size_left) {
                    // printf("but no space left in memzone. Checking next one.\n");
                    head = head->next;
                } else {
                    // printf("returning.\n");
                    return (head);
                }
            }
            else {
                head = head->next;
            }
        }  while (head);
    }

    printf("No zone found\n");
    return NULL;
}

static void init_chunk_header(t_memory_zone *zone, t_chunk_header *chunk, size_t t, t_chunk_header *prev, t_chunk_header *next) {

    chunk->size = t;
    chunk->is_free = false;
    chunk->prev = prev;
    chunk->next = next;

    if (zone)
        zone->size_left -= HEADER_SIZE + t;
    return;
}

static t_chunk_header *allocate_chunk(t_memory_zone *zone, size_t t) {

    // printf("In allocate chunk--------------------------------------\n");
    t_chunk_header *head = NULL;

    if (zone->base_block == NULL) {

        zone->base_block = (t_chunk_header *)((char *)zone + sizeof(t_memory_zone));
        init_chunk_header(zone, zone->base_block, t, NULL, NULL);
        return (zone->base_block);

    } else {
        head = zone->base_block;
        while (head) {
            
            if (t <= head->size && head->is_free) {
            // implement a way to create a free block right after the selcted one and if there's
            // enough bytes to have 1 struct chunk_header set to free + 1byte of free memory. 
            // Otherwise it's splitting and we loose bytes forever
                size_t size_left_by_alloc = head->size - t;
                if (size_left_by_alloc >= HEADER_SIZE + 1) {
                    t_chunk_header *free_chunk = (t_chunk_header *)((char *)head + (t + HEADER_SIZE));
                    size_t free_chunk_size = size_left_by_alloc - HEADER_SIZE;

                    free_chunk->size = free_chunk_size;
                    free_chunk->is_free = true;
                    free_chunk->prev = head;
                    free_chunk->next = head->next;
                    head->next->prev = free_chunk;
                    head->next = free_chunk;
                }

                init_chunk_header(zone, head, t, head->prev, head->next);
                return(head);
            }
            else if (head->next == NULL) {
                size_t chunk_size = HEADER_SIZE + head->size;
                head->next = (t_chunk_header *)((char *)head + chunk_size);

                if (chunk_size <= zone->size_left)
                    init_chunk_header(zone, head->next, t, head, NULL);
                return (head->next);
            } else {
                // printf("This one not ok, let's check the next one\n");
                head = head->next;
            }

        }
    }
    // printf("End of allocate chunk--------------------------------------\n");
    return (NULL);
}

size_t  get_alloc_type(size_t t) {

    if (t <= SMALL_THRESHOLD)
        return (TINY);
    else if (t <= LARGE_THRESHOLD)
        return (SMALL);
    else {
        return (LARGE);
    }
}


static int init_memory_zone() {

    t_memory_zone *zone = NULL;

    zone = create_zone(TINY, 0);
    if (zone == NULL) {
        return (1);
    }
    // base = zone;
    add_zone(zone);
    zone = (t_memory_zone *)((char *)zone->size_total + sizeof(t_memory_zone));
    zone = create_zone(SMALL, 0);
    if (zone == NULL) {
        free(base);
        return (1);
    }
    add_zone(zone);
    return (0);
}


// struct rlimit get_limit() {
//     struct rlimit old_lim; 

//     if( getrlimit(RLIMIT_NOFILE, &old_lim) == 0) 
//         printf("Old limits -> soft limit= %llu \t"
//            " hard limit= %llu \n", old_lim.rlim_cur,  
//                                  old_lim.rlim_max); 
//     return (old_lim);
// }




//!!!!!!!!!! COMPILER AVEC LES FLAGS !!!!!!!!!!!!
EXPORT
void    *malloc(size_t t) {

    // printf("Malloc call--------------------------------------------------------------------\n");
    // get_limit();


    size_t len = align4(t);
    // printf("len aligned is %lu\n", len);
    size_t chunk_len = HEADER_SIZE + len;
    // printf("chunk Len = %lu\n", chunk_len);
    // printf("HEADER_SIZE is %lu and MEMORY_SIZE_HEADER is %lu\n", HEADER_SIZE, MEMORY_HEADER_SIZE);
    t_chunk_header *chunk = NULL;
    size_t alloc_type = get_alloc_type(t);

    if (base == NULL) {
        if (init_memory_zone()) {
            printf("Error initializing memory zones\n");
            return NULL;
        }
    }

    t_memory_zone *zone = get_zone(alloc_type, len);
    if (zone == NULL || alloc_type == LARGE) {
        zone = create_zone(LARGE, len);
        if (zone == NULL) {
            return NULL;
        }
        add_zone(zone);
    }
    chunk = allocate_chunk(zone, t);
    if (chunk == NULL) {
        printf("Allocation failed...\n");
        return NULL;
    }
    
    // printf("Returning the adress [%p]\n", chunk->data);
    return chunk->data;
}
