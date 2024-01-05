#ifndef _CONFIGURATION_H_
#define _CONFIGURATION_H_

#include <common.h>

typedef struct _construction_configuration {
    int countPoints;
    point_t* points;
    int countEdges;
    edge_t* edges;
} conf_construction_t;

typedef struct _loads_configuration {
    load_t type;
    int Load;
} conf_loads_t;

typedef struct _project_configuration {
    char *creation_data;
    char *project_name;
    char *project_path;
    char *construction_path;
    char *loads_path;
} conf_project_t;

int parse_construction_conf();
int parse_loads_conf();

#endif  //_CONFIGURATION_H_