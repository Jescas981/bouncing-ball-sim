
#include <io.h>
#include <stdio.h>
#include <stdlib.h>

char *read_plain_file(const char *filepath) {

  FILE *file = fopen(filepath, "r");
  if (file == NULL) {
    printf("Not able to open file\n");
    return NULL;
  }

  // Get the file size to allocate memory for the content
  fseek(file, 0, SEEK_END);
  long file_size = ftell(file);
  fseek(file, 0, SEEK_SET);

  // Allocate memory to store the shader content
  char *plain_text = malloc(file_size + 1);

  if (plain_text == NULL) {
    printf("Memory allocation failed\n");
    fclose(file);
    return NULL;
  }

  // Read the file content into the buffer
  fread(plain_text, 1, file_size, file);
  plain_text[file_size] = '\0'; // Null terminate the string

  // Clean up
  fclose(file);

  return plain_text;
}
