#pragma once

#include <iostream>
#include <string>
#include <string_view>
#include <algorithm>

std::string_view ltrim(std::string_view str)
{
    const auto pos(str.find_first_not_of(" \t\n\r\f\v\;"));
    str.remove_prefix(min(pos, str.length()));
    return str;
}

std::string_view rtrim(std::string_view str)
{
    const auto pos(str.find_last_not_of(" \t\n\r\f\v"));
    str.remove_suffix(min(str.length() - pos - 1, str.length()));
    return str;
}

std::string trim(std::string& stroc)
{
    std::string_view str{stroc};
    str = ltrim(str);
    str = rtrim(str);
    return stroc=str;
}


bool trim_sector(std::string& stroc) {
    size_t pos1 = stroc.find_first_of("[]");
    size_t pos2 = stroc.find_last_of("[]");
    if ((pos1 != std::string::npos) && (pos2 != std::string::npos)) {
        stroc = stroc.substr( pos1 + 1, pos2 - pos1 - 1 );
        return true;
    }
    else return false;
}


bool trim_key_value(std::string& stroc, std::string& name, std::string& val) {
    size_t pos = stroc.find('=');
    if (pos != std::string::npos) {
        size_t pos1 = stroc.find(';');
        if (pos1 != std::string::npos) {
            stroc.erase(pos1);
        }
        name = { stroc,0,pos };
        name = trim(name);
        val = { stroc,pos+1, size(stroc) };
        val = trim(val);
        return true;
    }
    return false;
}

bool trim_for_get(const std::string& stroc, std::string& sector, std::string& key) {
    size_t pos = stroc.find('.');
    if (pos != std::string::npos) {
        sector = { stroc,0,pos };
        sector = trim(sector);
        key = { stroc,pos + 1, size(stroc) };
        key = trim(key);
        if(!(sector.empty()&&key.empty()))
            return true;
    }
    else return false;
}