#include <common.h>
#include <stdio.h>
#include <stdlib.h>


bool check_if_correct_file(const char* str, char **file_path) {
    char* str_copy = strdup(str);
    char *ptr = (strtok((char*)str_copy, "/"));
    char *last = NULL;
    while (ptr != NULL) {
        last = ptr;
        ptr = strtok(NULL, "/");
    }
    (*file_path) = last;
    if (strcmp((const char*)(*file_path), "construction.yml") == 0 ||
        strcmp((const char*)(*file_path), "loads.yml") == 0) {
        return SUCCESS;
    }
    return FAIL;
}

char* read_file(const char* path) {
    char* buffer;
    FILE *f = fopen(path, FILE_OPEN_MODE);
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);
    buffer = (char *) malloc(fsize+1);
    fread(buffer, fsize, 1, f);
    fclose(f);
    buffer[fsize] = 0;
    return buffer;
};



