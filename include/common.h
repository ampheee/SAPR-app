#ifndef _COMMON_HEADER_
#define _COMMON_HEADER_

#include <stdbool.h>
// #include <cyaml/cyaml.h>

#define SUCCESS true
#define FAIL false

typedef int coordinate;

typedef struct _POINT {
    coordinate x;
    coordinate y;
} point;

typedef struct _EDGE {
    point from;
    point to;
} edge;

// struct for all-configuration
typedef struct _CONSTRUCTION_CONFIGURATION {
    int countPoints;
    coordinate** points;
    int countEdges;
    edge** edges;
} construction_conf;

typedef struct _LOADS_CONFIGURATION {
} loads_conf;


#endif  //_COMMON_HEADER_