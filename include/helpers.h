#ifndef _HELPERS_H
#define _HELPERS_H


//file_helpers.c
char* read_file(const char* path);
void* save_file(const char *path, const char *buffer);
bool check_if_correct_config_filename(const char* str, char **file_path);
void save_project(char *path);

//gtk_helpers.c
void gtk_text_buffer_to_file(GtkTextBuffer *gtk_buffer, const char *path);
void file_to_gtk_text_buffer(const char *path, const char *filename);

#endif //_HELPERS_H