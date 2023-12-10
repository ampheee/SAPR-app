#include <common.h>
#include <string.h>

extern GtkBuilder *ui_builder;
extern GtkWidget *window;
GtkTextBuffer *buffer;

G_MODULE_EXPORT void file_open(GtkWidget *load) {
    char *path;
    GtkFileChooserAction action= GTK_FILE_CHOOSER_ACTION_OPEN;
    GtkWidget *choose = gtk_file_chooser_dialog_new(
        "Choose a file to open",
        GTK_WINDOW(window),
        GTK_FILE_CHOOSER_ACTION_OPEN, GTK_STOCK_OK, GTK_RESPONSE_OK, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL
    );
    if (gtk_dialog_run(GTK_DIALOG(choose)) == GTK_RESPONSE_ACCEPT) {
        path = gtk_file_chooser_get_filename(
            GTK_FILE_CHOOSER(choose)
        );
        gtk_text_buffer_set_text(buffer, path, -1);
    }
    GtkWidget *text_widget;
    if (strcmp(path, "check")) {
        // text_widget = GTK_WIDGET(gtk_builder_get_object(ui_builder, "widget_id"));
    } else {
        text_widget = GTK_WIDGET(gtk_builder_get_object(ui_builder, "loads_text_view"));
    }
    printf("GtkTextBuffer *buffer: %s", (char *) path);
    gtk_text_view_set_buffer(GTK_TEXT_VIEW(text_widget), buffer);
    gtk_widget_destroy(choose);
}

G_MODULE_EXPORT void save_file(GtkWidget *save) {
}
