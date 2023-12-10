#include <common.h>
#include <string.h>
#include <stdio.h>
#include <helpers.h>

extern GtkWidget *window;

G_MODULE_EXPORT void file_open_handler() {
    GtkTextBuffer *gtk_buffer;
    char *file_buffer, *filename;
    GtkWidget *choose = gtk_file_chooser_dialog_new(
    "Choose a file to open",
    GTK_WINDOW(window),
    GTK_FILE_CHOOSER_ACTION_OPEN,
    "_Open", GTK_RESPONSE_OK,
    "_Cancel", GTK_RESPONSE_CANCEL,
    NULL
    );
    if (gtk_dialog_run(GTK_DIALOG(choose)) == GTK_RESPONSE_OK) {
        gchar *path = gtk_file_chooser_get_filename(
            GTK_FILE_CHOOSER(choose)
        );
        if (check_if_correct_file(path, &filename)) {
            file_buffer = read_file(path);
            gtk_buffer = GTK_TEXT_BUFFER(
                gtk_builder_get_object(ui_builder, strcat(filename, "_buffer"))
            );
            gtk_text_buffer_set_text(gtk_buffer ,(gchar*) file_buffer, -1);
            gtk_widget_grab_focus(GTK_WIDGET(
                gtk_builder_get_object(ui_builder, strcat(filename, "view"))
                )
            );
            free(file_buffer);
        } else {
            GtkWidget *dialog;
            dialog = gtk_message_dialog_new(NULL,
                                    GTK_DIALOG_MODAL,
                                    GTK_MESSAGE_ERROR,
                                    GTK_BUTTONS_OK,
                                    "Error: Incorrect file choosed\n"
                                    "Please, choose one of this files:\n"
                                    "1. constructions.yml\n"
                                    "2. loads.yml\n"
                                    "3. information.yml");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
        }
        g_free(path);
    }
    gtk_widget_destroy(choose);
}

G_MODULE_EXPORT void save_file(GtkWidget *save) {
}

G_MODULE_EXPORT void save_file_as() {

}
