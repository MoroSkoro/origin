#pragma once

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <iterator>
#include <fstream>
#include <functional>
#include <utility>
#include <string_view>
#include "Trim.h"

typedef  std::map<std::string, std::string> Entries;
typedef  std::map<std::string, Entries> IniData;

struct add_section {
    add_section(IniData& data) : data_(data) {}
    void operator()(std::string q) const {
        data_.emplace(q, Entries());
    }

    IniData& data_;
};

struct add_key {
    add_key(IniData& data) : data_(data) {}
    void operator()(std::string q, const std::string& sec) const {
        data_[sec].emplace(q, std::string());

    }

    IniData& data_;
};

struct add_value {
    add_value(IniData& data) : data_(data) {}
    void operator()(std::string q, const std::string& sec, const std::string& key) const {
        data_[sec][key] = q;
    }

    IniData& data_;
};

