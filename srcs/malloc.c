
#include "../malloc.h"

// void *mmap(void *addr, size_t len, int prot, int flags, int fd, off_t offset);
// int munmap(void *addr, size_t len);


t_chunk_header *base = NULL;



// 1/ align the malloc size (on 4)
// 2/ mmap the requested size + HEADER_SIZE and set the associated header
// 3/ 
// ?/ Use getrlimit()
// ?/ set protections


// struct t_chunk_header *allocate_chunk(size_t t) {

//     base = mmap(NULL, t + HEADER_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
//     return (base);

// }

void    *malloc(size_t t) {

    int test = 42;
    int *testptr = &test;

    size_t len = align4(t);
    size_t chunk_len = HEADER_SIZE + len;
    printf("chunk Len = %lu\n", chunk_len);

    // void *ptr1 = mmap(NULL, chunk_len, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    // void *ptr2 = mmap(NULL, chunk_len, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    // printf("address1 : %p\n", ptr1);
    // printf("address2 : %p\n", ptr2);
    // // printf("address : %p\n", (void *)testptr);
    
    // // void *ptr1 = allocate_chunk(t);


    // munmap(ptr1, t);
    // ptr1 = mmap(NULL, chunk_len, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    // printf("address1 bis : %p\n", ptr1);
    // munmap(ptr1, t);

    // munmap(ptr2, t);

    t_chunk_header *chunk = mmap(NULL, chunk_len, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (chunk == MAP_FAILED) {
        printf("Malloc failed\n");
        return NULL;
    }
    
    chunk->size = t;
    chunk->is_free = false;
    chunk->next = NULL;

    base = chunk;
    
    return chunk->data;

}

void free(void *ptr) {
    
    if (munmap(ptr, 8192) == -1) {
        printf("Free failed\n");
    }


}





int main (int argc, char **argv) {
    

    printf("page size = %d\n", TINY_THRESHOLD);
    printf("size of struct is %lu\n", HEADER_SIZE);



    // tiny malloc : 48bytes
    // char *str = "Hello World!\n";
    // void *ptr = malloc(sizeof(char) * strlen(str) + sizeof(char));


    // big malloc : 8192 bytes
    void *ptr = malloc(8192);
    free(ptr);
    
    return (0);
}