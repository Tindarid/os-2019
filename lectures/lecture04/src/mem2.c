#include <stdlib.h>

int main() {
    printf("Hello\n");
    const char * a = malloc(100);
    a[0] = 'X';
    free(a);
    printf("%c\n", a[0]);
}
