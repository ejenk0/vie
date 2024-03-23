// main.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/ioctl.h>
#include <sys/param.h>

#include <ncurses.h>

/* Structs */

struct CharVector {
  char *array;  // null ('\0') terminated string representing the current char
                // vector
  int capacity; // total number of characters the vector can hold w/o final '\0'
  int length;   // number of characters w/o final '\0'
                // array[length] == '\0' always
  int lines;    // 1 + number of '\n' characters
};

struct State {
  int cursor_row;
  int cursor_col;
  struct CharVector file_vec;
};

/* Headers */

struct CharVector char_vector_create();
struct CharVector char_vector_append(struct CharVector, char);
struct CharVector read_file_into_char_vector(struct CharVector vec,
                                             char *filename);

struct State handle_input(char c, struct State state);

struct State move_cursor_relative(struct State state, int rows, int cols);
struct State move_cursor_absolute(struct State state, int row, int col);

char *get_row(char *string, int row);
char* strtok_single(char* string, char* k);

void _char_vector_debug(struct CharVector);

int main(int argc, char **args) {
  struct CharVector file_vec = char_vector_create();

  if (argc > 1) {
    char *filename = args[1];
    file_vec = read_file_into_char_vector(file_vec, filename);
  } else {
    file_vec = char_vector_append(file_vec, '\n');
  }

  /* ncurses init */
  initscr();            // Start curses mode
  raw();                // Disable line buffering
  keypad(stdscr, TRUE); // We get function keys, arrow keys etc.
  noecho();             // Don't echo everything the user types
  cbreak();             // Line buffering disabled, pass everything to getch()

  printw(file_vec.array); // print out the entire loaded file
  move(0, 0);             // set the cursor at 0, 0

  struct State state = {0, 0, file_vec};

  /* Main loop */
  while (1) {
    refresh();
    char c = getch();
    state = handle_input(c, state);
  }
  endwin();
}

// Create a new char vector with no characters and a terminating '\0'
struct CharVector char_vector_create() {
  char *arr = (char *)malloc(sizeof(char));
  arr[0] = '\0';
  struct CharVector vec = {
      arr, // array
      0,   // capacity
      0,   // length
      0    // lines
  };
  return vec;
}

struct CharVector char_vector_append(struct CharVector vec, char c) {
  if (vec.length == vec.capacity) {
    int new_capacity = (vec.capacity + 1) * 2 - 1;

    vec.array = (char *)realloc(vec.array, sizeof(char) * new_capacity + 1);
    if (vec.array == NULL) {
      fprintf(stderr, "Fatal error: unable to allocate enough memory for "
                      "character vector\n");
      exit(EXIT_FAILURE);
    }

    vec.capacity = new_capacity;
  }
  vec.array[vec.length] = c;
  if (c == '\n')
    vec.lines += 1;
  vec.length += 1;
  vec.array[vec.length] = '\0';

  return vec;
}

struct CharVector read_file_into_char_vector(struct CharVector vec,
                                             char *filename) {
  FILE *f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "Fatal error: unable to open %s\n", filename);
    exit(EXIT_FAILURE);
  }

  int c;
  while ((c = fgetc(f)) != EOF) {
    vec = char_vector_append(vec, (char)c);
  }

  if (ferror(f)) {
    fprintf(stderr, "Fatal error: error while reading %s\n", filename);
    exit(EXIT_FAILURE);
  }
  fclose(f);

  return vec;
}

struct State handle_input(char c, struct State state) {
  switch (c) {
  case 'h':
    return move_cursor_relative(state, 0, -1);
  case 'j':
    return move_cursor_relative(state, 1, 0);
  case 'k':
    return move_cursor_relative(state, -1, 0);
  case 'l':
    return move_cursor_relative(state, 0, 1);
  }
}

struct State move_cursor_relative(struct State state, int rows, int cols) {
  int target_row = state.cursor_row + rows;
  int target_col = state.cursor_col + cols;

  struct State new_state = move_cursor_absolute(state, target_row, target_col);

  return new_state;
}

struct State move_cursor_absolute(struct State state, int row, int col) {
  int dest_row = row;
  int dest_col;

  if (row <= 0) {
    dest_row = 0;
  } else if (dest_row >= state.file_vec.lines) {
    dest_row = state.file_vec.lines - 1;
  }

  char* row_string = get_row(state.file_vec.array, dest_row);
  int row_len = strlen(row_string);
  free(row_string);
  dest_col = MIN(col, row_len);

  state.cursor_row = dest_row;
  state.cursor_col = dest_col;

  move(dest_row, dest_col);

  return state;
}

char *get_row(char *string, int row) {
  char *string_copy = (char*)malloc(sizeof(char) * (strlen(string) + 1));
  strcpy(string_copy, string);

  int i = 0;
  char *tok = strtok_single(string_copy, "\n");
  while (i < row && tok != NULL) {
    tok = strtok_single(NULL, "\n");
    i += 1;
  }
  char *row_string = (char*)malloc(sizeof(char) * (strlen(tok) + 1));
  strcpy(row_string, tok);
  free(string_copy);
  return row_string;
}

char* strtok_single(char* input, char* k) {
    static char* string;
    if (input != NULL) {
        string = input;
    }
    char *delim_ptr = strpbrk(string, k);
    if (delim_ptr == NULL) {
        return NULL;
    }
    delim_ptr[0] = '\0';
    char* ret = string;
    string = delim_ptr + 1;
    return ret;
}

void _char_vector_debug(struct CharVector vec) {
  printf("Array: \"%s\"\nCapacity: %d\nLength: %d\n", vec.array, vec.capacity,
         vec.length);
}
