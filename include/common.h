#ifndef _COMMON_HEADER_
#define _COMMON_HEADER_

#include <stdbool.h>
#include <gtk/gtk.h>
// #include <cyaml/cyaml.h>

#define SUCCESS true
#define FAIL false

#define BUFFER_SIZE 2048

extern GtkBuilder *ui_builder;
extern GtkWindow  *window;
extern GtkTextBuffer *construction_buffer;
extern GtkTextBuffer *loads_buffer;
extern GtkTextBuffer *project_buffer;

typedef int coordinate;


typedef enum  {
    LOAD,
    NOT_LOAD,
} load_type;

typedef struct _POINT {
    coordinate x;
    coordinate y;
} point;

typedef struct _EDGE {
    point from;
    point to;
} edge;

// struct for all-configuration
typedef struct _construction_configuration {
    int countPoints;
    coordinate** points;
    int countEdges;
    edge** edges;
} construction_conf;

typedef struct _loads_configuration {
    load_type type;
    int Load;
} loads_conf;

typedef struct _ProjectConfiguration {
    
} project_conf;


#endif  //_COMMON_HEADER_