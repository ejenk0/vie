// main.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Structs */

struct CharVector {
    char* array;
    int capacity;
    int length;
};

/* Headers */

struct CharVector char_vector_create();
struct CharVector char_vector_append(struct CharVector, char);

struct CharVector read_file_into_char_vector(struct CharVector vec, char* filename);

void _char_vector_debug(struct CharVector);

int main(int argc, char** args) {
    struct CharVector file_vec = char_vector_create();

    if (argc > 1) {
        char* filename = args[1];
        file_vec = read_file_into_char_vector(file_vec, filename);
   }

   _char_vector_debug(file_vec); 
}

// Create a new char array with only a \0
struct CharVector char_vector_create() {
    char* arr = (char*) malloc(sizeof(char));
    arr[0] = '\0';
    struct CharVector vec = {
        arr, // array
        0,   // capacity
        0    // length
    };
    return vec;
}

struct CharVector char_vector_append(struct CharVector vec, char c) {
    if (vec.length == vec.capacity) {
        int new_capacity = (vec.capacity + 1) * 2 - 1;

        vec.array = (char*) realloc(vec.array, sizeof(char) * new_capacity + 1);
        if (vec.array == NULL) {
            fprintf(stderr, "Fatal error: unable to allocate enough memory for character vector");
            exit(EXIT_FAILURE);
        }

        vec.capacity = new_capacity;
    }

    vec.array[vec.length] = c;
    vec.length += 1;
    vec.array[vec.length] = '\0';

    return vec;
}

struct CharVector read_file_into_char_vector(struct CharVector vec, char* filename) {
    FILE* f = fopen(filename, "r");
    if (f == NULL) {
        fprintf(stderr, "Fatal error: unable to open %s", filename);
        exit(EXIT_FAILURE);
    }

    int c;
    while ((c = fgetc(f)) != EOF) {
        vec = char_vector_append(vec, (char) c);
    }

    if (ferror(f)) {
        fprintf(stderr, "Fatal error: error while reading %s", filename);
        exit(EXIT_FAILURE);
    }
    fclose(f);

    return vec;
}

void _char_vector_debug(struct CharVector vec) {
    printf("Array: \"%s\"\nCapacity: %d\nLength: %d\n", vec.array, vec.capacity, vec.length);
}
