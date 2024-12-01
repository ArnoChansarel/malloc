
#include "../includes/malloc.h"
#include "libft.h"


t_memory_zone *base = NULL;
// 1/ align the malloc size (on 4)
// 2/ mmap the requested size + HEADER_SIZE and set the associated header
// 3/ 
// ?/ Use getrlimit()
// ?/ set protections


static t_memory_zone *create_zone(size_t type) {

    t_memory_zone *zone = NULL;
    size_t total_size = 0;

    if (type == TINY) {
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

    zone->type = type;
    zone->size_total = total_size - sizeof(t_memory_zone);
    zone->next = NULL;//          set to NULL but for allocatin must do [zone + sizeof(*next)];
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
            head = head->next;
        }
        head->next = zone;
    }
    printf("Memory zone added at linkedlist index [%d]\n", i);
    return;
}

static t_memory_zone *get_zone(size_t alloc_type, size_t t) {
    
    (void)t;// servira a check la bonne zone
    t_memory_zone *head = base;

    if (head == NULL) {
        printf("No zone found\n");
        return NULL;
    }

    do {
        if ((size_t)head->type == alloc_type) {
            printf("A zone has been found, returning.\n");//         it is not good if list has more than 1 element
            return (head);
        }
        else {
            head = head->next;
        }
    }  while (head->next);

    return NULL;
}

static void init_chunk_header(t_chunk_header *chunk, size_t t) {

    chunk->size = t;
    chunk->is_free = false;
    chunk->next = NULL;

    return;
}

static t_chunk_header *allocate_chunk(t_memory_zone *zone, size_t t) {

    printf("In allocate chunk--------------------------------------\n");
    t_chunk_header *head = NULL;

    if (zone->base_block == NULL) {
        printf("Allocating first block of %u zone\n", zone->type);

        zone->base_block = (t_chunk_header *)((char *)zone + sizeof(t_memory_zone));
        init_chunk_header(zone->base_block, t);
        printf("returning 1st chunk at address [%p]\n", zone->base_block);
        printf("Knowing that zone is at address [%p]\n", zone);
        printf("And size of memory zone is %lu\n", sizeof(t_memory_zone));
        return (zone->base_block);

    } else {
        head = zone->base_block;
        while (head) {
            
            if (t <= head->size && head->is_free) {
                printf("We return a free one !");
                return(head);
            }
            else if (head->next == NULL) {
                printf("We find the next one\n");
                head->next = (t_chunk_header *)((char *)head + sizeof(t_chunk_header) + head->size);
                init_chunk_header(head->next, t);
                printf("returning 2nd chunk at address [%p]\n", head->next);
                printf("Knowing that head is at address [%p]\n", head);
                return (head->next);
            } else {
                printf("This one not ok, let's check the next one\n");
                head = head->next;
            }

            // implement a way to create a free block right after the selcted one
            // if possible. Otherwise it's splitting


        }
    }
    printf("End of allocate chunk--------------------------------------\n");
    return (NULL);
}

size_t  get_alloc_type(size_t t) {

    if (t <= SMALL_THRESHOLD) {
        return (TINY);
    }
    // else if ()
    // return (SMALL);
    else {
        return (LARGE);
    }
}

EXPORT
void    *malloc(size_t t) {

    printf("Malloc call--------------------------------------------------------------------\n");

    size_t len = align4(t);
    printf("len aligned is %lu\n", len);
    size_t chunk_len = HEADER_SIZE + len;
    printf("chunk Len = %lu\n", chunk_len);
    printf("HEADER_SIZE is %lu and MEMORY_SIZE_HEADER is %lu\n", HEADER_SIZE, MEMZONE_HEADER);
    t_chunk_header *chunk = NULL;
    size_t alloc_type = get_alloc_type(t);

    if (alloc_type == LARGE) {
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
        t_memory_zone *zone = get_zone(alloc_type, t);
        if (zone == NULL) {
            zone = create_zone(alloc_type);
            if (zone == NULL) {
                return NULL;
            }
            add_zone(zone);
        }
        chunk = allocate_chunk(zone, t);
        if (chunk == NULL) {
            printf("Allocation of tiny failed...\n");
        }
    }
    
    return chunk->data;
}
