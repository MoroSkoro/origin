#pragma once

#include <iostream>
#include <windows.h>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <iterator>
#include <exception>
#include <fstream>
#include <functional>
#include <utility>
#include <string_view>
#include "Trim.h"
#include "additional_functions.h"


class ini_parser {

    std::vector<std::string> vec;
    std::string s;

    IniData data;
public:
    ini_parser(const std::string& file_name) {
        std::fstream fil;
        fil.open(file_name, std::ios::in);

        if (!fil.is_open()) {
            throw std::exception("File not opened!");
        }

        while (!fil.eof()) {
            std::getline(fil, s);
            vec.push_back(s += '\n');
        }

        fil.close();

        std::string sec_, key_, value_;
        for (auto v : vec) {
            if (v.empty()) {}
            else {
                //Если встретили '[]', то это секция
                if (trim_sector(v)) {
                    sec_ = v;
                    add_section(this->data)(v);
                }
                else {
                    std::string name;
                    std::string val;
                    if (trim_key_value(v, name, val)) {
                        add_key(this->data)(name, sec_);
                        add_value(this->data)(val, sec_, name);
                    }
                }
            }
        }

    }

    ini_parser& operator=(const ini_parser&) = delete;
    ini_parser(const ini_parser&) = delete;

    void print() {
        for (auto sec : data) {
            std::cout << sec.first << "\n";
            for (auto key : sec.second) {
                std::cout << key.first << " = ";
                std::cout << key.second << "\n";
            }
        }
    }

    template <class p>
    p get_value(const std::string& section) {
        std::string sector;
        std::string key;
        std::string value = "Bad syntax!";
        if (trim_for_get(section, sector, key)) {
            auto it = data.find(sector);
            if (it != data.end()) {
                auto it1 = it->second.find(key);
                if (it1 != it->second.end()) {
                    if (it1->second.empty()) {
                        throw std::exception("The variable is not defined");
                        //return "undefined";
                    }
                }
                else {
                    print();
                    return "No find. See the acceptable values.";
                }
                value = it1->second;
                return value;
            }
            else {
                
                print();
                return "No find. See the acceptable values.";
            }
        };

        return value;
    }
};
