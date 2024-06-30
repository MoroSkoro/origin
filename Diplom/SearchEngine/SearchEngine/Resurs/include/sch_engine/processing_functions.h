#pragma once

#include <iostream>
#include <string>
#include <windows.h>
#include <filesystem>
#include "cpr/cpr.h"
#include "libxml/HTMLparser.h"
#include "libxml/xpath.h"
#include <sstream>

//UTF8 -> UTF16 conversion
std::wstring toUTF16(const std::string& input);

std::wstring ToLower(std::string string);

void parseHTML(const xmlXPathContextPtr& context, std::string& returnString);
std::string removeParser(std::wstring a, int& const min, int& const max);

void parseStory(xmlDocPtr doc, xmlNodePtr cur, std::string&);
std::string wordsPars(std::wstring a, int& const min, int& const max);
