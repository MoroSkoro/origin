#pragma once
#include <iostream>
#include "map"
#include "vector"
#include "chrono"
#include <string>

struct Request {
    std::string column;
    std::string tabl;
    std::string where;
    std::vector<std::string> columns;
    std::map<std::string, std::string> kv;
};


class SqlSelectQueryBuilder {
public:
    std::string rq = "SELECT ";
    explicit SqlSelectQueryBuilder() {
        request.column = "*";
        request.tabl = " FROM students";

    }

    SqlSelectQueryBuilder& AddColumn(const std::string& column) noexcept {
        if (request.column == "*") {
            request.column = column;
        }
        else request.column += ", " + column;
        return *this;
    }

    SqlSelectQueryBuilder& AddColumns_vec(const std::vector<std::string>& columns) noexcept {
        request.columns = columns;
        if (request.column == "*") {
            for (size_t i = 0; i < request.columns.size(); i++) {
                if (i == 0) {
                    request.column = request.columns[i];
                }
                else request.column +=", "+ request.columns[i];
            }
        }
        else {
            for (size_t i = 0; i < request.columns.size(); i++) {
                if (request.columns[i] == request.columns.back()) {
                    request.column += request.columns[i];
                }
                else {
                    request.column += request.columns[i] + ", ";
                }
            }
        }
        return *this;
        
        
    };

    SqlSelectQueryBuilder& AddFrom(const std::string& tabl) noexcept {
        request.tabl = " FROM " + tabl;
        return *this;
    }

    SqlSelectQueryBuilder& AddWhere(const std::string& key, const std::string& value) noexcept {
        if (request.where.empty()) {
            request.where = " WHERE " + key + "=" + value;
        }
        else request.where += " AND " + key + "=" + value;
        return *this;
    }

    SqlSelectQueryBuilder& AddWhere_map(const std::map<std::string, std::string>& kv) noexcept {
        request.kv = kv;
        size_t s = request.kv.size();
        if (request.where.empty()) request.where = " WHERE ";
        for (const auto& [key, value] : request.kv) {
            if(s==1){ request.where += key + "=" + value; }
            else request.where += key + "=" + value +" AND ";
            s--;
        }
        return *this;
    };

    void BuildQuery() {
        std::string full_rq = rq + request.column + request.tabl + request.where + ";";
        std::cout << full_rq << std::endl;
    }

private:
    Request request;
};
