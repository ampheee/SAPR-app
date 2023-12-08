#include <common.h>
#include <gtk/gtk.h>
#include <unistd.h>

// Слот выхода из программы
G_MODULE_EXPORT void onExit(GtkWindow * w __attribute__((unused))) {
    gtk_main_quit();
}

// Слот нажатия на кнопку
G_MODULE_EXPORT void onBtnClicked(GtkButton * btn, gpointer data) {
    //Просто меняем надпись на кнопке
    gtk_button_set_label(GTK_BUTTON(btn), "Woof");
}

int main(int argc, char * argv[]) {
    gtk_init(&argc, &argv);
    GtkBuilder *ui_builder;
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
    GtkWidget * window = GTK_WIDGET(gtk_builder_get_object(ui_builder, "sapr_main_window"));
    gtk_window_maximize((GtkWindow *) window);
    gtk_builder_connect_signals(ui_builder, NULL);
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}