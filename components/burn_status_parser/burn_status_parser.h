#ifndef BURN_STATUS_PARSER_H
#define BURN_STATUS_PARSER_H

#include <string>

std::string extract_json_string(const std::string& body);
bool parse_json(const std::string& json_string, int& burn_status);

#endif
