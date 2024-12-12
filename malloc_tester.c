#include <stdlib.h>
#include <stdio.h>
#include "srcs/includes/malloc.h"


int main() {
    // char *ptr1 = (char *)malloc(128);
    // char *ptr2 = (char *)malloc(3048);
 
    // char *ptr3 = (char *)malloc(PAGE_SIZE * 2);
    // char *ptr4 = (char *)malloc(PAGE_SIZE);

    // show_alloc_mem();
    // free(ptr3);
    // ptr3 = malloc(PAGE_SIZE);

    // show_alloc_mem();
    // char *ptr5 = (char *)malloc(PAGE_SIZE);

    // // free(ptr2);

    // show_alloc_mem();
    // free(ptr1);

    // free(ptr5);
    // // show_alloc_mem();

    // free(ptr4);
    // show_alloc_mem();
    // free(ptr3);




// TEST LARGE -------------------------------------------------------------

    char *ptr1 = (char *)malloc(128);
    char *ptr2 = (char *)malloc(3048);
 
    char *ptr3 = (char *)malloc(PAGE_SIZE * 2);
    char *ptr4 = (char *)malloc(PAGE_SIZE);

    show_alloc_mem();
    free(ptr3);
    ptr3 = malloc(PAGE_SIZE);// should be before ptr4 after reallocation

    show_alloc_mem();
    char *ptr5 = (char *)malloc(PAGE_SIZE); // should be after ptr4 since there's only 
                                            // 4096bytes of diff between ptr3 and ptr4
                                            // (no rrom for headers)

    show_alloc_mem();

//  TESTS REALLOC ----------------------------------------------------------
    // char *ptr1 = (char *)malloc(128);
    // char *ptr2 = (char *)malloc(PAGE_SIZE * 8);
    // char *ptr3 = (char *)malloc(4096);

    // ptr1 = (char *)realloc(ptr1, 256);
    // show_alloc_mem();

    // ptr1 = (char *)realloc(ptr1, 128);
    // show_alloc_mem();

    // ptr2 = (char *)realloc(ptr2, PAGE_SIZE * 4 -27);
    // show_alloc_mem();

    // ptr2 = (char *)realloc(ptr2, PAGE_SIZE * 10);
    // show_alloc_mem();

// --------------------------------------------------------------------------

    return 0;
}
