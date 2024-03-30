/*

Zihua Li, CruzID: zli487
Lex.c sorts the list into lex order using ADT functions declared in List.h
PA1, CSE 101 Winter 2024

*/


#define _GNU_SOURCE
#define index __no_index__  // Temporarily rename the index function from strings.h
#include <string.h>
#undef index                // Remove the temporary rename to use index
#include "List.h"
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Invalid number of arguments. Usage: %s input_file output_file\n", argv[0]);
        exit(1);
    }

    // Open the input file
    FILE *input_file = fopen(argv[1], "r");
    if (input_file == NULL) {
        fprintf(stderr, "Unable to open the input file.\n");
        exit(1);
    }

    // Open the output file
    FILE *output_file = fopen(argv[2], "w");
    if (output_file == NULL) {
        fprintf(stderr, "Unable to create or write to the output file.\n");
        fclose(input_file); // Close the input file
        exit(1);
    }

    // Read lines and store them in an array
    char **lines = NULL;
    size_t numLines = 0;
    size_t max_line_length = 0;

    char *line = NULL;
    size_t line_length = 0;
    ssize_t read;

    // Dynamically allocation memory space to 'line', adapt to current line length
    // (line_length is only for write-in but not the reference for the length of the line
    // therefore has no use.
    while ((read = getline(&line, &line_length, input_file)) != -1) {
        line[strcspn(line, "\n")] = '\0'; // Remove the newline character
        lines = (char **)realloc(lines, (numLines + 1) * sizeof(char *));
        lines[numLines] = strdup(line);
        // max_line_length is not used, it is for future backup.
        if (read > max_line_length) {
            max_line_length = read;

        }
        numLines++;
    }
    free(line);

    // Create an array of indices
    List indicesList = newList();
    append(indicesList, 0);
    moveFront(indicesList);
    for(int i = 1; i < numLines; i++) {
        moveFront(indicesList);
        while(index(indicesList) != -1 && strcmp(lines[get(indicesList)], lines[i]) <= 0) {
            moveNext(indicesList);
        }
        if(index(indicesList) == -1) {
            append(indicesList, i);
        } else insertBefore(indicesList, i);
    }

    // Write sorted lines to output file
    for (moveFront(indicesList); listIndex(indicesList) >= 0; moveNext(indicesList)) {
        fprintf(output_file, "%s\n", lines[get(indicesList)]);
    }

    // Close files and free memory
    fclose(input_file);
    fclose(output_file);
    for (size_t i = 0; i < numLines; i++) {
        free(lines[i]);
    }
    free(lines);

    // Free the List
    freeList(&indicesList);

    return 0;
}
