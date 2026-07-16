#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    while (1) {
        printf("$ ");
        char input[100] = {0};
        fgets(input, 100, stdin);
        if (strcmp(input, "exit\n") == 0) break;
        int pid = fork();
        if (pid == 0) {
            char* args[10] = {0};
            int j = 0;
            args[j] = input;
            int i;
            for (i = 0; input[i] != '\n'; i++) {
                if (input[i] == ' ') {
                    input[i] = '\0';
                    args[++j] = &input[i + 1];
                }
            }
            input[i] = '\0';
            args[++j] = NULL;
            execvp(args[0], args);
        } else {
            wait(NULL);
        }
    }
    return 0;
}
