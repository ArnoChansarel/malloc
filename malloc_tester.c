#include <stdlib.h>
#include <stdio.h>
#include "srcs/includes/malloc.h"

// gcc -o malloc_tester malloc_tester.c -L. -lft_malloc
// gcc -o test3 test3.c -L. -lft_malloc  && /usr/bin/time -l ./test3

int main() {

// TEST SUBJECT -------------------------------------------------------------

    // char *ptr1 = (char *)malloc(42);
    // char *ptr2 = (char *)malloc(84);
 
    // char *ptr4 = (char *)malloc(48847);
    // char *ptr3 = (char *)malloc(3725);

    // show_alloc_mem();

// TEST SIMPLE -------------------------------------------------------------

    // char *ptr1 = (char *)malloc(211);
    // show_alloc_mem();

    // char *ptr2 = (char *)malloc(3048);
    // show_alloc_mem();
 
    // char *ptr3 = (char *)malloc(PAGE_SIZE * 2);
    // show_alloc_mem();


    // ft_memset(ptr1, '1', 211);
    // printf("%s\n", ptr1);
    // ft_memset(ptr2, '2', 3048);
    // printf("%s\n", ptr2);
    // ft_memset(ptr3, '3', PAGE_SIZE * 2);
    // printf("%s\n", ptr3);


    // free(ptr3);
    // show_alloc_mem();
    // free(ptr2);
    // show_alloc_mem();
    // free(ptr1);
    // show_alloc_mem();

// TEST TINY & SMALL -------------------------------------------------------------

    // char *ptr1 = (char *)malloc(128);
    // char *ptr2 = (char *)malloc(3048);
 
    // char *ptr3 = (char *)malloc(42);
    // char *ptr4 = (char *)malloc(2111);
    // show_alloc_mem();

    // free(ptr2);
    // show_alloc_mem();

    // ptr2 = malloc(1012);
    // show_alloc_mem();

    // char *ptr5 = (char *)malloc(1012);
    // show_alloc_mem();

    // free(ptr2);
    // show_alloc_mem();

    // free(ptr4);//       Here 960 + 2111 = 3103 because we add 32 of chunk_header
    // show_alloc_mem();

    // free(ptr5);
    // show_alloc_mem();

    // free(ptr1);
    // free(ptr3);
    // show_alloc_mem();


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

    // ptr1 = (char *)realloc(ptr1, 256);// bigger, must allocate a new one
    // show_alloc_mem();

    // ptr1 = (char *)realloc(ptr1, 128);// smaller, chop 256 in 128 (96 left + 32 for chunk header)
    // show_alloc_mem();

    // free(ptr1);

    // ptr2 = (char *)realloc(ptr2, PAGE_SIZE * 4 -27);//smaller but must be a PAGE_SIZE multiple, so we round number
    // show_alloc_mem();

    // ptr2 = (char *)realloc(ptr2, PAGE_SIZE * 10);// bigger, must go at end of list
    // show_alloc_mem();

// --------------------------------------------------------------------------
    return 0;
}
