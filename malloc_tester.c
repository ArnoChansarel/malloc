#include <stdlib.h>
#include <stdio.h>
#include "srcs/includes/malloc.h"


int main() {
    // char *ptr1 = (char *)malloc(128);
    // char *ptr2 = (char *)malloc(128);
 
    // char *ptr3 = (char *)malloc(128);
    // char *ptr4 = (char *)malloc(128);
    // char *ptr5 = (char *)malloc(128);

    // show_alloc_mem();
    // free(ptr1);
    // ptr1 = malloc(64);

    // show_alloc_mem();

    // free(ptr2);

    // // show_alloc_mem();
    // free(ptr1);

    // free(ptr5);
    // // show_alloc_mem();

    // free(ptr4);
    // show_alloc_mem();
    // free(ptr3);




//  TESTS REALLOC ----------------------------------------------------------
    char *ptr1 = (char *)malloc(128);
    char *ptr2 = (char *)malloc(PAGE_SIZE * 8);
    char *ptr3 = (char *)malloc(4096);

    ptr1 = (char *)realloc(ptr1, 256);
    show_alloc_mem();

    ptr1 = (char *)realloc(ptr1, 128);
    show_alloc_mem();

    ptr2 = (char *)realloc(ptr2, PAGE_SIZE * 4 -27);
    show_alloc_mem();

    ptr2 = (char *)realloc(ptr2, PAGE_SIZE * 10);
    show_alloc_mem();

// --------------------------------------------------------------------------



    return 0;
}
