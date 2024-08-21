#pragma once

#include <iostream>
#include <string>
#include <windows.h>
#include <filesystem>
#include <sstream>

#include "cpr/cpr.h"
#include "libxml/HTMLparser.h"
#include "libxml/xpath.h"

std::wstring toUTF16(const std::string& input);

std::wstring ToLower(std::string string);

void parseHTML(const xmlXPathContextPtr& context, std::string& returnString);

std::string removeParser(std::wstring a, int& const min, int& const max);

bool func_pars(std::string& link, std::vector<std::string>& buffer_links, std::string& all_text);
