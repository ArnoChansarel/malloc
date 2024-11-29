
#include "../includes/malloc.h"
#include "libft.h"


t_memory_zone *base = NULL;
// 1/ align the malloc size (on 4)
// 2/ mmap the requested size + HEADER_SIZE and set the associated header
// 3/ 
// ?/ Use getrlimit()
// ?/ set protections


static t_memory_zone *create_zone(size_t t) {

    t_memory_zone *zone = NULL;
    size_t total_size = 0;

    if (t <= SMALL_THRESHOLD) {
        printf("Creating a tiny memzone\n");
        total_size = PAGE_SIZE * 4; // 3.12 memory page is enough for 100 allocations
    } else {
        printf("Creating a SMALL memzone\n");
        total_size = PAGE_SIZE * 32;// will see
    }

    zone = mmap(NULL, total_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (zone == MAP_FAILED) {
        printf("Malloc failed\n");
        return NULL;
    }

    zone->type = "tiny";
    zone->size_total = total_size - sizeof(t_memory_zone);
    zone->next = NULL;//          SONT MIS A NULL MAIS POUR ALLOCATION DOIT FAIRE zone + sizeof(*next);
    zone->base_block = NULL;
    printf("Access ?\n");

    return (zone);

}

// add_zone(), add a zone to the linked list
static void     add_zone(t_memory_zone *zone) {
    base = zone;
}

static t_memory_zone *get_zone(size_t t) {
    
    (void)t;
    // to implement.
    
    return NULL;
}

static t_chunk_header *init_chunk_header(size_t t) {

    t_chunk_header *chunk = NULL;

    chunk->size = t;
    chunk->is_free = false;
    chunk->next = NULL;

    return chunk;
}

static t_chunk_header *allocate_chunk(t_memory_zone *zone, size_t t) {

    printf("In allocate chunk\n");
    t_chunk_header *head = NULL;

    if (zone->base_block == NULL) {
        printf("check first condition\n");

        head = (t_chunk_header *)zone->base_block;
        head->size = t;
        head->is_free = false;
        head->next = NULL;
        // t_chunk_header *chunk;

        // chunk->size = t;
        // chunk->is_free = false;
        // chunk->next = NULL;

        // zone->base_block = init_chunk_header(t);
        // zone->base_block = chunk;
        return (zone->base_block);

    } else {
        head = zone->base_block;
        while (t > head->size && head->is_free == false) {
            
            if (head->next == NULL) {
                head->next = init_chunk_header(t);
                return (head->next);
            } else {
                head = head->next;
            }

            // implement a way to create a free block right after the selcted one
            // if possible. Otherwise it's splitting

            return(head);
        }
    }
    return (NULL);
}



EXPORT
void    *malloc(size_t t) {

    size_t len = align4(t);
    printf("len aligned is %lu\n", len);
    size_t chunk_len = HEADER_SIZE + len;
    printf("chunk Len = %lu\n", chunk_len);
    printf("HEADER_SIZE is %lu and MEMORY_SIZE_HEADER is %lu\n", HEADER_SIZE, MEMZONE_HEADER);
    t_chunk_header *chunk = NULL;
    
    if (t > LARGE_THRESHOLD) {
        // check if size + header_size <= page_size else add 1 page_size
        chunk = mmap(NULL, chunk_len, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        if (chunk == MAP_FAILED) {
            printf("Malloc failed\n");
            return NULL;
        }
            chunk->size = t;
            chunk->is_free = false;
            chunk->next = NULL;
    }
    else {
        t_memory_zone *zone = get_zone(t);
        if (zone == NULL) {
            zone = create_zone(t);
            if (zone == NULL) {
                return NULL;
            }
            add_zone(zone);
        }
        chunk = allocate_chunk(zone, t);
    }
    
    return chunk->data;
}
