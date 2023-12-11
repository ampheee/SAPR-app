#include <common.h>
#include <string.h>
#include <stdio.h>
#include <helpers.h>


G_MODULE_EXPORT void file_open_handler() {
    GtkTextBuffer *gtk_buffer;
    char *file_buffer, *filename;
    GtkWidget *choose = gtk_file_chooser_dialog_new(
    "Choose a file to open",
    window,
    GTK_FILE_CHOOSER_ACTION_OPEN,
    "_Open", GTK_RESPONSE_OK,
    "_Cancel", GTK_RESPONSE_CANCEL,
    NULL
    );
    if (gtk_dialog_run(GTK_DIALOG(choose)) == GTK_RESPONSE_OK) {
        gchar *path = gtk_file_chooser_get_filename(
            GTK_FILE_CHOOSER(choose)
        );
        if (check_if_correct_config_filename(path, &filename)) {
            file_buffer = read_file(path);
            gtk_buffer = GTK_TEXT_BUFFER(
                gtk_builder_get_object(ui_builder, strcat(filename, "_buffer"))
            );
            gtk_text_buffer_set_text(gtk_buffer ,(gchar*) file_buffer, -1);
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
                                    "3. project.yml");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
        }
        g_free(path);
    }
    gtk_widget_destroy(choose);
}

G_MODULE_EXPORT void save_file_handler(GtkWidget *save) {
    // GtkTextBuffer *gtk_buffer;
    // get context file dir and save widget`s into it.
}

G_MODULE_EXPORT void save_file_as_handler() {
    GtkTextBuffer *gtk_buffer;
    char *filename;
    GtkWidget *choose = gtk_file_chooser_dialog_new(
    "Choose a file to save",
    window,
    GTK_FILE_CHOOSER_ACTION_SAVE,
    "_Open", GTK_RESPONSE_OK,
    "_Cancel", GTK_RESPONSE_CANCEL,
    NULL
    );
    if (gtk_dialog_run(GTK_DIALOG(choose)) == GTK_RESPONSE_OK) {
        gchar *path = gtk_file_chooser_get_filename(
            GTK_FILE_CHOOSER(choose)
        );
        if (check_if_correct_config_filename(path, &filename)) {
            if (strcmp(filename, "construction.yml") == 0) {
                gtk_text_buffer_to_file(construction_buffer, path);
            } else if (strcmp(filename, "loads.yml")) {
                gtk_text_buffer_to_file(loads_buffer, path);
            } else if (strcmp(filename, "project.yml")) {
                gtk_text_buffer_to_file(project_buffer, path);
            }
        }
        g_free(path);
    }
    gtk_widget_destroy(choose);
}
