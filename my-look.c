/* Copyright (C) 2022 Hong Xu */
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#define MAX 256

// print the help information
void print_help(char *program_name) {
    printf("\nUsage: %s [-V] [-h] [-f <filename>] <prefix>\n", program_name);
    printf("Options:\n");
    printf("    [-V]              Print information about this utility\n");
    printf("    [-h]              Print help information about this utility\n");
    printf("    [-f <filename>]   Use <filename> as the input dictionary\n");
    printf("    <prefix>          The string to search for\n\n");
}

// remove non-alphanumeric characters
void trim_line(char *trimed, char *src) {
    int length = strlen(src);
    for (int i = 0; i < length; i++) {
        char c = src[i];
        if (isalpha(c) || isdigit(c)) {
            char new_c[2];
            new_c[0] = c;
            new_c[1] = '\0';
            strncat(trimed, new_c, 1);
        }
    }
}

// compare text lines with prefix
int compare_line(char *text_line, char *prefix) {
    char trimed[MAX] = "";  // store trimed text line
    trim_line(trimed, text_line);

    int length_text = strlen(trimed);
    int length_prefix = strlen(prefix);

    if (length_prefix <= length_text) {
        if (strncasecmp(trimed, prefix, length_prefix) == 0) {
            return 0;  // matching the prefix
        }
    }

    return -1;  // not matching
}

// go through dictionary and print valid lines with matching prefix
void look_up(int is_file, char *prefix, char *file_path) {
    char buffer[MAX];

    if (is_file == 1) {
        // open file
        FILE *fp = fopen(file_path, "r");
        if (fp == NULL) {
            printf("my-look: cannot open file\n");
            exit(1);
        }

        // go through lines in the file
        while (fgets(buffer, MAX, fp) != NULL) {
            if (compare_line(buffer, prefix) == 0) {
                printf("%s", buffer);
            }
        }

        // close file
        if (fclose(fp) != 0) {
            printf("my-look: cannot close file\n");
            exit(1);
        } else {
            exit(0);
        }
    } else {  // user input
        while (fgets(buffer, MAX, stdin) != NULL) {
            if (compare_line(buffer, prefix) == 0) {
                printf("%s", buffer);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    int is_file = 0;         // indicator of input, 0 if stdin is the input,
                             // 1 if a file is the input
    char *file_path = NULL;  // path to the file
    char *prefix = NULL;

    int option = 0;
    opterr = 0;  // prevent printing any error message returned by getopt()
    while ((option = getopt(argc, argv, "Vhf:")) != -1) {
        switch (option) {
        case 'V':  // prints information about this utility, then exit with
                   // code 0
            printf("my-look from CS537 Spring 2022\n");
            exit(0);
        case 'h':  // prints help information about this utility, then exit with
                   // code 0
            print_help(argv[0]);
            exit(0);
        case 'f':  // uses <filename> as the input dictionary
            file_path = optarg;
            is_file = 1;  // set this flag to 1 if there is a file path
            break;
        case '?':  // illegal arguemnt or other errors, exit with code 1
            printf("my-look: invalid command line\n");
            exit(1);
        }
    }

    // get the prefix here
    if (optind == argc - 1) {  // first no-arguement's index equals to the last
                               // index of arguements --> correctly get the
                               // prefix string
        prefix = argv[optind];
    } else {
        printf("my-look: invalid command line\n");
        exit(1);
    }

    // look for matching lines
    look_up(is_file, prefix, file_path);

    exit(0);
}
