#include <common.h>
#include <configuration.h>
#include <helpers.h>
#include <yaml.h>

static yaml_parser_t gParser = {0};

static conf_construction_t gConstruction = {0};
static conf_loads_t gLoads = {0};

// char **conf_available_tokens_construction = {"CountOfPoints", "Points",
//                                              "CountOfEdges", "Edges"};

// char **conf_available_tokens_loads = {

// };

status_t conf_validate_tokens(const char *text);

conf_project_t conf_create_project() {}

conf_project_t conf_parse_project() {}

status_t conf_parse_construction() {
  int in_points = 0, in_edges = 0;
  int i_point = 0, i_edge = 0;
  bool points_parsed = false, edges_parsed = false, parsed = false;
  status_t status = SUCCESS;
  yaml_event_t event = {0};
  const char *text =
      (const char *)gtk_get_text_from_text_buffer(construction_buffer);
  FAIL_CUTBACK(!conf_validate_tokens(text), status,
               "conf: token validation failed!\n");
  FAIL_CUTBACK(!yaml_parser_initialize(&gParser), status,
               "conf: failed to initialize parser!\n");
  yaml_parser_set_input_string(&gParser, (const unsigned char *)text,
                               strlen((text)));
  while (yaml_parser_parse(&gParser, &event) && status == SUCCESS && !parsed) {
    switch (event.type) {
      case YAML_SCALAR_EVENT:
        if (strcmp((char *)event.data.scalar.value, "countEdges") == 0) {
          yaml_parser_parse(&gParser, &event);
          FAIL_CUTBACK(event.type != YAML_SCALAR_EVENT, status,
                       "conf: failed to parse countEdges: not scalar event");
          gConstruction.countEdges = atoi((char *)event.data.scalar.value);
          FAIL_CUTBACK(gConstruction.countEdges == 0, status,
                       "conf: wrong countEdges value from yaml file\n");
          gConstruction.edges =
              (edge_t *)calloc(gConstruction.countEdges, sizeof(edge_t));
          FAIL_CUTBACK(
              gConstruction.points == NULL, status,
              "conf: unable to allocate points array: out_of_resource\n");
        } else if (strcmp((char *)event.data.scalar.value, "countPoints") ==
                   0) {
          yaml_parser_parse(&gParser, &event);
          FAIL_CUTBACK(event.type != YAML_SCALAR_EVENT, status,
                       "conf: failed to parse countPoints: not scalar event");
          gConstruction.countPoints = atoi((char *)event.data.scalar.value);
          FAIL_CUTBACK(gConstruction.countPoints == 0, status,
                       "conf: wrong countPoints value from yaml file\n");
          gConstruction.points =
              (point_t *)calloc(gConstruction.countPoints, sizeof(point_t));
          FAIL_CUTBACK(
              gConstruction.points == NULL, status,
              "conf: unable to allocate points array: out_of_resource\n");
        }
        if (in_points) {
          FAIL_CUTBACK(i_point >= gConstruction.countPoints, status,
                       "i_point out of pointCount\n");
          if (strcmp((char *)event.data.scalar.value, "x") == 0) {
            yaml_parser_parse(&gParser, &event);
            gConstruction.points[i_point].x =
                atoi((char *)event.data.scalar.value);
          } else if (strcmp((char *)event.data.scalar.value, "y") == 0) {
            yaml_parser_parse(&gParser, &event);
            gConstruction.points[i_point].y =
                atoi((char *)event.data.scalar.value);
          } else if (strcmp((char *)event.data.scalar.value, "id") == 0) {
            yaml_parser_parse(&gParser, &event);
            gConstruction.points[i_point].id =
                atoi((char *)event.data.scalar.value);
          }
        } else if (in_edges) {
          FAIL_CUTBACK(i_edge >= gConstruction.countEdges, status,
                       "conf: i_edge out of countEdges range\n");
          if (strcmp((char *)event.data.scalar.value, "from_point") == 0) {
            yaml_parser_parse(&gParser, &event);
            gConstruction.edges[i_edge].from_point.id =
                atoi((char *)event.data.scalar.value);
          } else if (strcmp((char *)event.data.scalar.value, "to_point") == 0) {
            yaml_parser_parse(&gParser, &event);
            gConstruction.edges[i_edge].to_point.id =
                atoi((char *)event.data.scalar.value);
          }
        }
        if (strcmp((char *)event.data.scalar.value, "points") == 0 &&
            !points_parsed) {
          in_points = 1;
        } else if (points_parsed) {
          FAIL_CUTBACK(FAIL, status, "conf: points was already parsed\n");
        }
        if (strcmp((char *)event.data.scalar.value, "edges") == 0 &&
            !edges_parsed) {
          in_edges = 1;
        } else if (edges_parsed) {
          FAIL_CUTBACK(FAIL, status, "conf: edges was already parsed\n");
        }
        break;
      case YAML_MAPPING_END_EVENT:
        if (in_edges) {
          i_edge++;
        } else if (in_points) {
          i_point++;
        }
        break;
      case YAML_SEQUENCE_END_EVENT:
        if (in_edges) {
          in_edges = 0;
        } else if (in_points) {
          in_points = 0;
        }
        break;
      case YAML_STREAM_END_EVENT:
        fprintf(stdout, "conf: construction.yaml parsed");
        parsed = true;
      default:
        break;
    }
    yaml_event_delete(&event);
  }
  g_free((gchar *)text);
  yaml_parser_delete(&gParser);
  return SUCCESS;
}

status_t conf_parse_loads() { return SUCCESS; }

status_t conf_validate_tokens(const char *text) {
  yaml_token_t token = {0};
  status_t status = SUCCESS;
  bool done = FAIL;
  FAIL_CUTBACK(!yaml_parser_initialize(&gParser), status,
               "Failed to initialize parser!\n");
  yaml_parser_set_input_string(&gParser, (const unsigned char *)text,
                               strlen((const char *)text));
  while (status == SUCCESS && done == FAIL) {
    FAIL_CUTBACK(!yaml_parser_scan(&gParser, &token), status,
                 "conf: failed to scan token in validation\n");
    FAIL_CUTBACK(token.type == YAML_NO_TOKEN, status,
                 "conf: no token is disallowed\n");
    FAIL_CUTBACK(token.type == YAML_VERSION_DIRECTIVE_TOKEN, status,
                 "conf: version directive token is disallowed\n");
    FAIL_CUTBACK(token.type == YAML_TAG_DIRECTIVE_TOKEN, status,
                 "conf: tag directive token is disallowed\n");
    FAIL_CUTBACK(token.type == YAML_DOCUMENT_START_TOKEN, status,
                 "conf: document start token is disallowed\n");
    FAIL_CUTBACK(token.type == YAML_DOCUMENT_END_TOKEN, status,
                 "conf: document end token is disallowed\n");
    FAIL_CUTBACK(token.type == YAML_FLOW_SEQUENCE_START_TOKEN, status,
                 "conf: flow sequence start token is disallowed\n");
    FAIL_CUTBACK(token.type == YAML_FLOW_SEQUENCE_END_TOKEN, status,
                 "conf: flow sequence end token is disallowed\n");
    FAIL_CUTBACK(token.type == YAML_FLOW_MAPPING_START_TOKEN, status,
                 "conf: flow mapping start token is disallowed\n");
    FAIL_CUTBACK(token.type == YAML_FLOW_MAPPING_END_TOKEN, status,
                 "conf: flow mapping end token is disallowed\n");
    FAIL_CUTBACK(token.type == YAML_FLOW_ENTRY_TOKEN, status,
                 "conf: flow entry token is disallowed\n");
    FAIL_CUTBACK(token.type == YAML_ALIAS_TOKEN, status,
                 "conf: alias token  is disallowed\n");
    FAIL_CUTBACK(token.type == YAML_ANCHOR_TOKEN, status,
                 "conf: anchor token is disallowed\n");
    FAIL_CUTBACK(token.type == YAML_TAG_TOKEN, status,
                 "conf: tag token is disallowed\n");
    if (token.type == YAML_STREAM_END_TOKEN) {
      done = SUCCESS;
    }
    // todo: check for unknown token;
    yaml_token_delete(&token);
  }
  yaml_parser_delete(&gParser);
  return status;
}

status_t conf_validate_construction(return SUCCESS;);
// status_t conf_validate_loads(
// return SUCCESS;
// );