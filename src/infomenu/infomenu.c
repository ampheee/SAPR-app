#include <common.h>
//on Open_project clicked
G_MODULE_EXPORT void open_project_directory() {
    GtkTextBuffer *gtk_buffer;
    char *file_buffer, *filename;
    GtkWidget *choose = gtk_file_chooser_dialog_new(
    "Choose a folder to open",
    GTK_WINDOW(window),
    GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER,
    "_Open", GTK_RESPONSE_OK,
    "_Cancel", GTK_RESPONSE_CANCEL,
    NULL
    );
    if (gtk_dialog_run(GTK_DIALOG(choose)) == GTK_RESPONSE_OK) {
        gchar *path = gtk_file_chooser_get_filename(
            GTK_FILE_CHOOSER(choose)
        );
        printf("folder path: %s\n", path);
        // gtk_buffer = GTK_TEXT_BUFFER(
        //     gtk_builder_get_object(ui_builder, strcat(filename, "_buffer"))
        // );
        // gtk_text_buffer_set_text(gtk_buffer ,(gchar*) file_buffer, -1);
        // } else {
        //     GtkWidget *dialog;
        //     dialog = gtk_message_dialog_new(NULL,
        //                             GTK_DIALOG_MODAL,
        //                             GTK_MESSAGE_ERROR,
        //                             GTK_BUTTONS_OK,
        //                             "Error: Incorrect file choosed\n"
        //                             "Please, choose one of this files:\n"
        //                             "1. constructions.yml\n"
        //                             "2. loads.yml\n"
        //                             "3. project.yml");
        //     gtk_dialog_run(GTK_DIALOG(dialog));
        //     gtk_widget_destroy(dialog);
        g_free(path);
    }
    gtk_widget_destroy(choose);
}

// on create_project clicked
G_MODULE_EXPORT void create_project_handler() {

}
// on save_project_clicked
G_MODULE_EXPORT void save_project_handler() {

}