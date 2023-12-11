#include <common.h>
#include <yaml.h>

void parse_conf(const char *buffer_name, void *configuration_ptr);

project_conf parse_project_conf() {
  parse_conf("construction.yml_buffer", NULL);
}

void parse_conf(const char *buffer_name, void *configuration_ptr) {
  yaml_parser_t parser;
  yaml_parser_initialize(&parser);
  // yaml_parser_set_input_string(&parser, );
}