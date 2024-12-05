#include <stdlib.h>
#include <stdio.h>
#include "srcs/includes/malloc.h"


unsigned long long hex_to_decimal(const void *address) {

    char hex_str[20];
    snprintf(hex_str, sizeof(hex_str), "%p", address);

    unsigned long long result;
    sscanf(hex_str, "%llx", &result);
    
    return result;
}

int main() {
    char *ptr1 = (char *)malloc(128);

    char *ptr2 = (char *)malloc(128);
    
    char *ptr3 = (char *)malloc(128);
    // char *ptr4 = (char *)malloc(128);
    // char *ptr5 = (char *)malloc(128);

    free(ptr1);
    ptr1 = malloc(64);
    show_alloc_mem();

    free(ptr1);
    free(ptr2);

    ptr1 = malloc(128);

    show_alloc_mem();


    free(ptr3);
    show_alloc_mem();

    free(ptr1);




    show_alloc_mem();
    return 0;

}