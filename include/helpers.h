#ifndef _HELPERS_H
#define _HELPERS_H

char* read_file(const char* path);
bool check_if_correct_config_filename(const char* str, char **file_path);


void gtk_text_buffer_to_file(GtkTextBuffer *gtk_buffer, const char *path);

#endif //_HELPERS_H