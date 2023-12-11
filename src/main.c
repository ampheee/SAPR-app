#include <common.h>
#include <stdio.h>
#include <unistd.h>

GtkBuilder *ui_builder;
GtkWindow  *window;
GtkTextBuffer *construction_buffer;
GtkTextBuffer *loads_buffer;
GtkTextBuffer *project_buffer;

// Слот выхода из программы
G_MODULE_EXPORT void onExit(GtkWindow * w __attribute__((unused))) {
    gtk_main_quit();
}

int main(int argc, char * argv[]) {
    gtk_init(&argc, &argv);
    GtkCssProvider *css_provider;
    GError * err = NULL;
    char cwd[516];
    getcwd(cwd, sizeof(cwd));
    ui_builder = gtk_builder_new();
    if(!gtk_builder_add_from_file(ui_builder, "gui/main.glade", &err)) {
        g_critical("Не вышло загрузить файл с UI : %s", err->message);
        g_error_free(err);
    }
    css_provider  = gtk_css_provider_new();
    if (!gtk_css_provider_load_from_path(css_provider, "gui/styles.css", &err)) {
        g_critical("Не вышло загрузить файл проводника стилей CSS: %s", err->message);
        g_error_free(err);
    }
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                    GTK_STYLE_PROVIDER(css_provider),
                    GTK_STYLE_PROVIDER_PRIORITY_USER);
    window = GTK_WINDOW(gtk_builder_get_object(ui_builder, "sapr_main_window"));
    construction_buffer = GTK_TEXT_BUFFER(gtk_builder_get_object(ui_builder, "construction.yml_buffer"));
    loads_buffer = GTK_TEXT_BUFFER(gtk_builder_get_object(ui_builder, "loads.yml_buffer"));
    project_buffer = GTK_TEXT_BUFFER(gtk_builder_get_object(ui_builder, "project.yml_buffer"));
    gtk_window_maximize((GtkWindow *) window);
    gtk_builder_connect_signals(ui_builder, NULL);
    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}