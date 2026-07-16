#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    while (1) {
        printf("$ ");
        char* input;
        scanf("%s", input);
        if (fork() == 0) {
            execlp(input, NULL);
        } else {
            wait(NULL);
        }
    }
    return 0;
}
