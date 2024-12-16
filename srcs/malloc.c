
#include "../includes/malloc.h"
#include "libft.h"


//
//      [chnk | data   ][chnk | data][chnk | data   ][chnk | data     ][chnk | data ][chnk | data       ][chnk | data      ]
//      |___________________________________________||______________________________||__________________||_________________|
//            zone TINY (pre allocated)                 zone SMALL (pre allocated)        zone LARGE            zone LARGE

// allocate TINY and SMALL when launching
// create a LARGE zone if needed, and add allocations in it if needed.
// defragmenting will work only in each zone.


t_memory_zone *base = NULL;

static t_memory_zone *create_zone(size_t type, size_t large_alloc) {

    t_memory_zone *zone = NULL;
    size_t total_size = 0;

    if (type == TINY) {
        total_size = PAGE_SIZE * TINY_FACTOR;
    } else if (type == SMALL) {
        total_size = PAGE_SIZE * SMALL_FACTOR;
    } else if (type == LARGE) {
        total_size = MEMORY_HEADER_SIZE + HEADER_SIZE + large_alloc;
    }

    if (check_memory_left(total_size)) {
        return NULL;
    }

    zone = mmap(NULL, total_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (zone == MAP_FAILED) {
        printf("Create Zone failed\n");
        return NULL;
    }

    zone->type = type;
    zone->size_total = total_size - MEMORY_HEADER_SIZE;
    zone-> size_left = zone->size_total;
    zone->prev = NULL;
    zone->next = NULL;
    zone->base_block = NULL;

    return (zone);
}

static int check_large_chunk_place(t_memory_zone *zone, t_memory_zone *head) {

    unsigned long long zone_addr = hex_to_decimal(zone);
    unsigned long long head_addr = hex_to_decimal(head);
    unsigned long long head_next_addr = hex_to_decimal(head->next);
    
    if (zone_addr > head_addr && zone_addr < head_next_addr) {
        // printf("Yes, address [%p] after address [%p] and before address [%p]\n", zone, head, head->next);

        zone->next = head->next;
        zone->prev = head;
        head->next->prev = zone;
        head->next = zone;

        return 1;
    }
    return 0;
}

static void     add_zone(t_memory_zone *zone) {
    
    t_memory_zone *head = NULL;
    // int i = 0;

    if (base == NULL) {
        base = zone;
    }   
    else {
        head = base;//            Here, make a pointer diff to place LARGE at right place
        while (head->next) {
            // i++;
            if (zone->type == LARGE && head->next && head->next->type == LARGE && check_large_chunk_place(zone, head)) {
                return;
            }
            if (!head->next)
                break;
            head = head->next;
        }
        head->next = zone;
        zone->prev = head;
    }
    return;
}

static t_memory_zone *select_zone(size_t alloc_type, size_t t) {

    t_memory_zone *head = base;

    if (head && alloc_type != LARGE) {
        do {
            if ((size_t)head->type == alloc_type) {
                // printf("A zone has been found, ");
                
                size_t chunk_size = HEADER_SIZE + t;
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

    // printf("No zone found\n");
    return NULL;
}

static t_chunk_header *allocate_chunk(t_memory_zone *zone, size_t t) {

    t_chunk_header *head = NULL;

    if (zone->base_block == NULL) {

        zone->base_block = (t_chunk_header *)((char *)zone + MEMORY_HEADER_SIZE);
        init_chunk_header(zone, zone->base_block, t, NULL, NULL);
        return (zone->base_block);

    } else {
        head = zone->base_block;
        while (head) {
            
            if (t <= head->size && head->is_free) {
            // implement a way to create a free block right after the selcted one and if there's
            // enough bytes to have 1 struct chunk_header set to free + 1byte of free memory. 
            // Otherwise it's splitting and we loose bytes forever
                return reduce_chunk(zone, head, t);
            }
            else if (head->next == NULL) {
                // reduce chunk will seprate chunk in 2
                // one stays the same, but size reduced
                // other is init : size is 
                size_t chunk_size = HEADER_SIZE + head->size;
                head->next = (t_chunk_header *)((char *)head + chunk_size);

                if (chunk_size <= zone->size_left)
                    init_chunk_header(zone, head->next, t, head, NULL);
                return (head->next);
            } else {
                head = head->next;
            }
        }
    }
    return (NULL);
}

static int init_memory_zone() {

    t_memory_zone *zone = NULL;

    zone = create_zone(TINY, 0);
    if (zone == NULL) {
        return (1);
    }
    add_zone(zone);
    zone = (t_memory_zone *)((char *)zone->size_total + MEMORY_HEADER_SIZE);
    zone = create_zone(SMALL, 0);
    if (zone == NULL) {
        free(base);
        return (1);
    }
    add_zone(zone);
    return (0);
}






// 1 terminer realloc                           --> good
// 2 build comparatif addresse dans add_zone    --> good
// 3 set limit with get_limit()                 --> good
// 4 check user input and protections           --> 
// 5 check les return NULL en cascade           --> 
// 6 !!!!!!!!!! COMPILER AVEC LES FLAGS !!!!!!!!!!!!


EXPORT
void    *malloc(size_t t) {

    // printf("Malloc call--------------------------------------------------------------------\n");

    if (t <= 0)
        return NULL;

    size_t len = align4(t);
    t_chunk_header *chunk = NULL;
    size_t alloc_type = get_alloc_type(t);

    if (base == NULL) {
        if (init_memory_zone()) {
            printf("Error while initializing memory zones\n");
            return NULL;
        }
    }

    t_memory_zone *zone = select_zone(alloc_type, len);
    if (zone == NULL || alloc_type == LARGE) {
        zone = create_zone(LARGE, len);
        if (zone == NULL) {
            return NULL;
        }
        add_zone(zone);
    }
    chunk = allocate_chunk(zone, t);
    if (chunk == NULL) {
        printf("Error: Allocation failed\n");
        return NULL;
    }

    return chunk->data;
}
