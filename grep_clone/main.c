#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
    if (argc < 3) fprintf(stderr, "Usage: %s <word> <filename>\n", argv[0]);

    // todo:  open file(s)
    FILE* file = fopen(argv[2], "r");
    if (file == NULL) fprintf(stderr, "Error: Cannot open file %s\n", argv[2]);

    // todo:  read files line by line
    char line[1024] = {0};
    while (fgets(line, sizeof(line), file) != NULL) {
        // todo:  search for pattern in each line
        // todo:  if found print the line
        if (strstr(line, argv[1])) printf("%s", line);
    }
}