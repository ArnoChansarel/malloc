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
    char *ptr = (char *)malloc(64);

    if (ptr == NULL) {
        perror("malloc failed");
        return 1;
    }

    char *ptr2 = (char *)malloc(128);

    if (ptr2 == NULL) {
        perror("malloc failed");
        return 1;
    }

    // printf("ptr1 [%p] and ptr2 [%p]\n", (void*)ptr, (void*)ptr2);

    // unsigned long long a1 = hex_to_decimal(ptr);
    // unsigned long long a2 = hex_to_decimal(ptr2);

    // printf("Valeur de ptr : 0x%llx | valeur de ptr2 : 0x%llx\n", a1, a2);
    // printf("Différence : %llu bytes\n", a2 - a1);

    snprintf(ptr, 100, "Hello, custom malloc!");
    // printf("%s\n", ptr);
    show_alloc_mem();


    snprintf(ptr2, 100, "Hello, custom malloc!");
    printf("%s\n", ptr2);



    char *ptr3 = (char *)malloc(4096 * 4);
    snprintf(ptr3, 100, "Hello, custom malloc LARGE!");
    show_alloc_mem();

    char *ptr4 = (char *)malloc(4096 * 4);
    snprintf(ptr4, 100, "Hello, custom malloc LARGE!");
    show_alloc_mem();
    
    
    char *ptr5 = malloc(310);
    show_alloc_mem();


    free(ptr);
    free(ptr2);
    free(ptr3);
    free(ptr4);
    show_alloc_mem();// --> error spotted in free when matching pointers
    free(ptr5);


    return 0;

}