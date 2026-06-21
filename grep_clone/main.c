#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void usage(char*);
void lowercase(char*);

int main(int argc, char** argv) {
    char isCaseSensitive = 0;
    if (argc < 3) usage(argv[0]);

    int opt;

    while ((opt = getopt(argc, argv, "i")) != -1) {
        switch (opt) {
            case 'i':
                isCaseSensitive = 1;
                break;
        }
    }

    if (argc - optind - 1 < 2) usage(argv[0]);

    char* word = argv[optind++];

    char line[1024] = {0};
    char original_line[1024] = {0};
    // todo:  open file(s)
    for (; optind < argc; optind++) {
        FILE* file = fopen(argv[optind], "r");
        if (file == NULL) {
            fprintf(stderr, "Error: Cannot open file [%s]\n", argv[optind]);

            continue;
        }

        printf("\nProcessing file: %s\n", argv[optind]);

        // todo:  read files line by line
        while (fgets(line, sizeof(line), file) != NULL) {
            // if case senstive lowercase everything
            strncpy(original_line, line, sizeof(line));
            if (isCaseSensitive) {
                lowercase(word);
                lowercase(line);
            }

            // todo:  search for pattern in each line
            // todo:  if found print the line
            if (strstr(line, word)) printf("\t%s", original_line);
        }

        fclose(file);
    }
    return 0;
}

void usage(char* arg) {
    fprintf(stderr, "Usage: %s <word> <filename>\n", arg);
    exit(1);
}

void lowercase(char* s) {
    char c;
    for (int i = 0; s[i] != '\0'; i++) s[i] = tolower(s[i]);
}