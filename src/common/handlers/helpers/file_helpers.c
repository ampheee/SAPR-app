#include <common.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

extern GtkTextBuffer *loads_buffer;
extern GtkTextBuffer *construction_buffer;
extern GtkTextBuffer *project_buffer;

char *read_file(const char *path) {
  char *buffer;
  FILE *f = fopen(path, "r");
  fseek(f, 0, SEEK_END);
  long fsize = ftell(f);
  fseek(f, 0, SEEK_SET);
  buffer = (char *)malloc(fsize + 1);
  fread(buffer, fsize, 1, f);
  fclose(f);
  buffer[fsize] = 0;
  return buffer;
};

void *save_file(const char *path, const char *buffer) {
  FILE *f = fopen(path, "w");
  printf("path: %s\nin buffer: %s\n", path, buffer);
  fwrite(buffer, strlen(buffer), 1, f);
  fclose(f);
}

bool check_if_correct_config_filename(const char *str, char **filename) {
  char *str_copy = strdup(str);
  char *ptr = (strtok((char *)str_copy, "/"));
  char *last = NULL;
  while (ptr != NULL) {
    last = ptr;
    ptr = strtok(NULL, "/");
  }
  (*filename) = last;
  if (strcmp((const char *)(*filename), "construction.yml") == 0 ||
      strcmp((const char *)(*filename), "loads.yml") == 0) {
    return SUCCESS;
  }
  return FAIL;
}

void save_project(char *path) {
  // save_file(strcat(path, "loads.yml"));
  // save_file(strcat(path, "constructions.yml"));
  // save_file(strcat(path, "project.yml"));
}