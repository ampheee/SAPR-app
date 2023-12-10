#include <common.h>


G_MODULE_EXPORT void draw_button_clicked(GtkWidget *widget) {

}


G_MODULE_EXPORT gboolean draw_cb(GtkWidget *widget, cairo_t *cr, gpointer data) {
    // if (button_clicked) {
        cairo_set_source_rgb(cr, 1, 0, 0);
        cairo_move_to(cr, 0, 0);
        cairo_line_to(cr, 600, 300);
        cairo_stroke(cr);
    // }
    return FAIL;
}