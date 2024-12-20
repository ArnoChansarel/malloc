
#include "../includes/malloc.h"


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

    // printf("Creating a zone of size %lu\n", total_size);
    zone = mmap(NULL, total_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (zone == MAP_FAILED) {
        ft_printf("Create Zone failed\n");
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

    if ((void*)zone > (void*)head && (void*)zone < (void*)head->next) {

        zone->next = head->next;
        zone->prev = head->prev ? head : NULL;
        head->next->prev = zone;
        head->next = zone;
        return 1;
    }
    return 0;
}

static void     add_zone(t_memory_zone *zone) {
    
    t_memory_zone *head = NULL;

    if (base == NULL) {
        base = zone;
    }   
    else {
        head = base;
        while (head->next) {
            if (zone->type == LARGE && head->next && check_large_chunk_place(zone, head)) {
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
    // printf("No zone found for type %lu\n", alloc_type);
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
                return reduce_chunk(zone, head, t);
            }
            else if (head->next == NULL) {
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

EXPORT
void    *malloc(size_t t) {

    if (t <= 0)
        return NULL;

    size_t len = align4(t);
    t_chunk_header *chunk = NULL;
    size_t alloc_type = get_alloc_type(t);

    t_memory_zone *zone = select_zone(alloc_type, len);
    if (zone == NULL || alloc_type == LARGE) {
        zone = create_zone(alloc_type, len);
        if (zone == NULL) {
            return NULL;
        }
        add_zone(zone);
    }
    chunk = allocate_chunk(zone, t);
    if (chunk == NULL) {
        ft_printf("Error: Allocation failed\n");
        return NULL;
    }

    return (void *)((char *)chunk + HEADER_SIZE);
}
