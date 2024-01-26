#include <common.h>
#include <helpers.h>

// g_free defer!
gchar *gtk_get_text_from_text_buffer(GtkTextBuffer *gtk_buffer) {
  GtkTextIter start, end;
  gchar *text;
  gtk_text_buffer_get_start_iter(gtk_buffer, &start);
  gtk_text_buffer_get_end_iter(gtk_buffer, &end);
  text = gtk_text_buffer_get_text(gtk_buffer, &start, &end, FALSE);
  return text;
}

void gtk_text_buffer_to_file(GtkTextBuffer *gtk_buffer, const char *path) {
  gchar *text = gtk_get_text_from_text_buffer(gtk_buffer);
  save_file(path, (const char *)text);
  g_free(text);
}

void file_to_gtk_text_buffer(const char *path, const char *filename) {
  GtkTextBuffer *gtk_buffer;
  char *file_buffer;
  file_buffer = read_file(path);
  gtk_buffer = GTK_TEXT_BUFFER(
      gtk_builder_get_object(ui_builder, strcat((char *)filename, "_buffer")));
  gtk_text_buffer_set_text(gtk_buffer, (gchar *)file_buffer, -1);
  free(file_buffer);
}

void show_error_popup(const char *message, int message_type, ...) {
  GtkWidget *dialog;
  if (message) {
    va_list args;
    va_start(args, message);
    char formatted_message[BUFFER_SIZE];
    vsnprintf(formatted_message, sizeof(formatted_message), message, args);
    va_end(args);
    dialog = gtk_message_dialog_new(NULL,
                                    GTK_DIALOG_MODAL,
                                    message_type,
                                    GTK_BUTTONS_OK,
                                    "%s",
                                    formatted_message);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
  }
}