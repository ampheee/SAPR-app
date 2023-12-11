#include <common.h>


void gtk_text_buffer_to_file(GtkTextBuffer *gtk_buffer, const char *path) {
  GtkTextIter start, end;
  gchar *text;
  gtk_text_buffer_get_start_iter(gtk_buffer, &start);
  gtk_text_buffer_get_end_iter(gtk_buffer, &end);
  text = gtk_text_buffer_get_text(gtk_buffer, &start, &end, FALSE);
  printf("%s\n",text);
  save_file(path, (const char *) text);
  g_free(text); //you need to clean up this buffer!
}