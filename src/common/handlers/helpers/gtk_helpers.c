#include <common.h>
#include <helpers.h>


void gtk_text_buffer_to_file(GtkTextBuffer *gtk_buffer, const char *path) {
  GtkTextIter start, end;
  gchar *text;
  gtk_text_buffer_get_start_iter(gtk_buffer, &start);
  gtk_text_buffer_get_end_iter(gtk_buffer, &end);
  text = gtk_text_buffer_get_text(gtk_buffer, &start, &end, FALSE);
  printf("%s\n",text);
  save_file(path, (const char *) text);
  g_free(text);
}

void file_to_gtk_text_buffer(const char *path, const char *filename) { 
  GtkTextBuffer *gtk_buffer;
  char *file_buffer;
  file_buffer = read_file(path);
  gtk_buffer = GTK_TEXT_BUFFER(
    gtk_builder_get_object(ui_builder, strcat((char *)filename, "_buffer"))
  );
  gtk_text_buffer_set_text(gtk_buffer ,(gchar*) file_buffer, -1);
  free(file_buffer);
}