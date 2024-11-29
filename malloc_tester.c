#include <stdlib.h>
#include <stdio.h>

int main() {
    char *ptr = (char *)malloc(64);

    if (ptr == NULL) {
        perror("malloc failed");
        return 1;
    }
    snprintf(ptr, 100, "Hello, custom malloc!");
    printf("%s\n", ptr);
    free(ptr);
    // printf("%s\n", ptr); --> segfault, as expected
    return 0;
}
