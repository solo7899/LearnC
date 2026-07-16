#include <stdio.h>

int main() {
    while (1) {
        printf("$ ");
        char* input;
        scanf("%s", input);
        printf("%s\n", input);
    }
    return 0;
}
