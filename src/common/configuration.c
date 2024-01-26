#include <common.h>
#include <configuration.h>
#include <helpers.h>
#include <yaml.h>
#include <time.h>
#include <unistd.h>

static yaml_parser_t gParser = {0};
static yaml_event_t gEvent = {0};

static conf_project_t      gProject      = {0};
static conf_construction_t gConstruction = {0};
static conf_loads_t        gLoads = {0};

// char **conf_available_tokens_construction = {"CountOfPoints", "Points",
                                            //  "CountOfEdges", "Edges"};

// char **conf_available_tokens_loads = {

// };

status_t conf_validate_tokens(const char *text);

// status_t conf_create_project(char *dir_path, char *project_name, char *) {
//   status_t Status = SUCCESS;
//   time_t now = time(NULL);
//   struct tm *time = localtime(&now);
//   strftime(time, sizeof(gProject.creation_data) - 1, "%d_%m_%Y %H:%M", time);
//   sprintf(gProject.loads_path, "%s/loads.yaml", dir_path);
//   sprintf(gProject.construction_path, "%s/construction.yaml");
//   sprintf(gProject.project_name, "%s",
//   return Status;
// }

status_t parse_yaml_scalar(char *key, void *buffer, char *error_message, status_t *status) { 
  status_t compare_status = FAIL;
  if (strcmp((char *) gEvent.data.scalar.value, key) == 0) {
    compare_status = SUCCESS;
    yaml_parser_parse(&gParser, &gEvent);
    FAIL_CUTBACK(gEvent.type != YAML_SCALAR_EVENT, *status, error_message);
    if (*status == SUCCESS) {
      if (sizeof(int) == sizeof(*(int *)buffer)) {
        *(int *)buffer = atoi(gEvent.data.scalar.value);
      } else {
        *(char **)buffer = (char *) gEvent.data.scalar.value;
      }
    }
    yaml_event_delete(&gEvent);
  }
  return compare_status;
}

// conf_project_t conf_parse_project() {
//   status_t status = SUCCESS;
//   yaml_gEvent_t gEvent = {0};
//   bool parsed = false;
//   const char *text =
//       (const char *text) gtk_get_text_from_text_buffer(project_buffer);
//   FAIL_CUTBACK(!conf_validate_tokens(text), status,
//                "conf_project: token validation failed!");
//   FAIL_CUTBACK(!yaml_parser_initialize(&gParser), status,
//                "conf_project: failed to initialize parser!");
//   if (status != FAIL) {
//     yaml_parser_set_input_string(&gParser, (const unsigned char *) text,
//                             strlen(text));
//   }
//   while (yaml_parser_parse(&gParser, &gEvent) && status == SUCCESS && !parsed); {
//     switch(gEvent.type) {
//       case YAML_SCALAR_gEvent:
//         if (strcmp((char *) gEvent.data.scalar.value, "creation_date") == 0) {
//           yaml_parser_parse(&gParser, &gEvent);
//           FAIL_CUTBACK(gEvent.type != YAML_SCALAR_gEvent, status,
//                        "conf_project: failed to parse creation date: not scalar gEvent");
//         } else if (strcmp((char *) gEvent.data.scalar.value, "construction_name") == 0) {
//           yaml_parser_parse(&gParser, &gEvent);
//           FAIL_CUTBACK(gEvent.type != YAML_SCALAR_gEvent, status, "conf_project: failed to parse project name: not scalar gEvent");
//           gProject.project_name:
//         }
//     }
//   }
//   return Status;
// }

status_t conf_parse_construction() {
  bool in_points = 0, in_edges = 0;
  int i_point = 0, i_edge = 0;
  bool points_parsed = false, edges_parsed = false, parsed = false;
  status_t status = SUCCESS;
  const char *text =
      (const char *)gtk_get_text_from_text_buffer(construction_buffer);
  FAIL_CUTBACK(!conf_validate_tokens(text), status,
               "conf_construction: token validation failed!");
  FAIL_CUTBACK(!yaml_parser_initialize(&gParser), status,
               "conf_construction: failed to initialize parser!");
  if (status != FAIL) {
    yaml_parser_set_input_string(&gParser, (const unsigned char *)text,
                               strlen(text));
  }
  while (yaml_parser_parse(&gParser, &gEvent) && status == SUCCESS && !parsed) {
    switch (gEvent.type) {
      case YAML_SCALAR_EVENT:
        if (parse_yaml_scalar("countPoints", &gConstruction.countPoints, "construction: failed to parse count points.", &status)) {
          gConstruction.points =
              (point_t *)calloc(gConstruction.countPoints, sizeof(point_t));
          FAIL_CUTBACK(
              gConstruction.points == NULL, status,
              "construction: unable to allocate points array.");
        } else if (parse_yaml_scalar("countEdges", &gConstruction.countEdges, "construction: failed to parse countEdges.", &status)) {
          gConstruction.edges =
              (edge_t *)calloc(gConstruction.countEdges, sizeof(edge_t));
          FAIL_CUTBACK(
              gConstruction.points == NULL, status,
              "construction: unable to allocate edges array.");
        }
        if (in_points) {
          FAIL_CUTBACK(i_point >= gConstruction.countPoints, status,
                       "construction: some of points is out of pointCount");
          if (parse_yaml_scalar("x", &gConstruction.points[i_point].x, NULL, &status));
          else if (parse_yaml_scalar("y", &gConstruction.points[i_point].y, NULL, &status));
          else if (parse_yaml_scalar("point_id", &gConstruction.points[i_point].id, NULL, &status))
          FAIL_CUTBACK(gConstruction.points[i_point].id <= 0, status, "construction: point id must be > 0");
        } else if (in_edges) {
          FAIL_CUTBACK(i_edge >= gConstruction.countEdges, status,
                       "construction: some of edges is out of countEdges range");
          if (parse_yaml_scalar("from_point", &gConstruction.edges->from_point, NULL, &status));
          else if (parse_yaml_scalar("to_point", &gConstruction.edges->to_point, NULL, &status));
          else if (parse_yaml_scalar("edge_id", &gConstruction.edges[i_edge].id, NULL, &status));
        }
        if (status == SUCCESS && gEvent.type != YAML_NO_EVENT) {
          if (strcmp((char *) gEvent.data.scalar.value, "points") == 0 && !points_parsed) {
            in_points = 1;
          } else if (points_parsed) {
            FAIL_CUTBACK(FAIL, status, "construction: more than one points definition");
          }
          if (strcmp((char *) gEvent.data.scalar.value, "edges") == 0 && !edges_parsed) {
            in_edges = 1;
          } else if (edges_parsed) {
            FAIL_CUTBACK(FAIL, status, "construction: more than one edges definition");
          }
        }
        break;
      case YAML_MAPPING_END_EVENT:
        if (in_points) {
          i_point++;
        } else if (in_edges) {
          i_edge++;
        }
        break;
      case YAML_SEQUENCE_END_EVENT:
        if (in_edges) {
          in_edges = false;
          edges_parsed = true;
        } else if (in_points) {
          in_points = false;
          points_parsed = true;
        }
        break;
      case YAML_STREAM_END_EVENT:
        fprintf(stdout, "construction: construction.yaml parsed");
        parsed = true;
        break;
      default:
        break;
    }
    if (gEvent.type != YAML_NO_EVENT) { 
      yaml_event_delete(&gEvent);
    }
  }
  g_free((gchar *)text);
  yaml_parser_delete(&gParser);
  show_error_popup("Configuration successfully parsed!", GTK_MESSAGE_INFO);
  return SUCCESS;
}

status_t conf_parse_loads(const char *text) { 

  return SUCCESS;
}

status_t conf_validate_tokens(const char *text) {
  yaml_token_t token = {0};
  status_t status = SUCCESS;
  bool done = FAIL;
  FAIL_CUTBACK(!yaml_parser_initialize(&gParser), status,
               "Failed to initialize parser!");
  yaml_parser_set_input_string(&gParser, (const unsigned char *)text,
                               strlen((const char *)text));
  while (status == SUCCESS && done == FAIL) {
    FAIL_CUTBACK(!yaml_parser_scan(&gParser, &token), status,
                 "validation: failed to scan token in validation");
    FAIL_CUTBACK(token.type == YAML_NO_TOKEN, status,
                 "validation: no token is disallowed");
    FAIL_CUTBACK(token.type == YAML_VERSION_DIRECTIVE_TOKEN, status,
                 "validation: version directive token is disallowed");
    FAIL_CUTBACK(token.type == YAML_TAG_DIRECTIVE_TOKEN, status,
                 "validation: tag directive token is disallowed");
    FAIL_CUTBACK(token.type == YAML_DOCUMENT_START_TOKEN, status,
                 "validation: document start token is disallowed");
    FAIL_CUTBACK(token.type == YAML_DOCUMENT_END_TOKEN, status,
                 "validation: document end token is disallowed");
    FAIL_CUTBACK(token.type == YAML_FLOW_SEQUENCE_START_TOKEN, status,
                 "validation: flow sequence start token is disallowed");
    FAIL_CUTBACK(token.type == YAML_FLOW_SEQUENCE_END_TOKEN, status,
                 "validation: flow sequence end token is disallowed");
    FAIL_CUTBACK(token.type == YAML_FLOW_MAPPING_START_TOKEN, status,
                 "validation: flow mapping start token is disallowed");
    FAIL_CUTBACK(token.type == YAML_FLOW_MAPPING_END_TOKEN, status,
                 "validation: flow mapping end token is disallowed");
    FAIL_CUTBACK(token.type == YAML_FLOW_ENTRY_TOKEN, status,
                 "validation: flow entry token is disallowed");
    FAIL_CUTBACK(token.type == YAML_ALIAS_TOKEN, status,
                 "validation: alias token  is disallowed");
    FAIL_CUTBACK(token.type == YAML_ANCHOR_TOKEN, status,
                 "validation: anchor token is disallowed");
    FAIL_CUTBACK(token.type == YAML_TAG_TOKEN, status,
                 "validation: tag token is disallowed");
    if (token.type == YAML_STREAM_END_TOKEN) {
      done = SUCCESS;
    }
    // todo: check for unknown token;
    yaml_token_delete(&token);
  }
  yaml_parser_delete(&gParser);
  return status;
}

status_t conf_validate_construction();
// status_t conf_validate_loads(
// return SUCCESS;
// );