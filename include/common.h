#ifndef _COMMON_HEADER_
#define _COMMON_HEADER_

#include <stdbool.h>
#include <gtk/gtk.h>

#define SUCCESS 1
#define FAIL    0
typedef uint status_t;

#define BUFFER_SIZE 2048

extern GtkBuilder *ui_builder;
extern GtkWindow  *window;
extern GtkTextBuffer *construction_buffer;
extern GtkTextBuffer *loads_buffer;
extern GtkTextBuffer *project_buffer;

typedef struct {
    int x;
    int y;
    int id;
} point_t;

typedef enum  {
    LOAD,
    NOT_LOAD,
} load_t;

typedef struct _EDGE {
    int from_point;
    int to_point;
    int id;
} edge_t;

#include <helpers.h>

#define FAIL_CUTBACK(expression, status, message, ...)    \
    do {                                                  \
        if (expression) {                                 \
            fprintf(stderr, message, ##__VA_ARGS__);      \
            status = FAIL;                                \
            show_error_popup(message, GTK_MESSAGE_ERROR,  ##__VA_ARGS__);     \
        }                                                 \
    } while (0)

// struct for all-configuration


#endif  //_COMMON_HEADER_