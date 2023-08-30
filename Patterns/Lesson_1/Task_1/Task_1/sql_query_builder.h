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
};


class SqlSelectQueryBuilder {
public:
    std::string rq = "SELECT ";
    explicit SqlSelectQueryBuilder() {
        request.column = "*";
        request.tabl = " FROM students";

    }
    
    SqlSelectQueryBuilder& AddColumn(const std::string& column) noexcept {
        if (request.column=="*") {
            request.column = column;
        }
        else request.column +=", "+ column;
        return *this;
    }

    SqlSelectQueryBuilder& AddFrom(const std::string& tabl) noexcept {
        request.tabl = " FROM "+tabl;
        return *this;
    }

    SqlSelectQueryBuilder& AddWhere(const std::string& key, const std::string& value) noexcept {
        if (request.where.empty()) {
            request.where =" WHERE "+ key + "=" + value;
        }
        else request.where +=" AND "+ key + "=" + value;
        return *this;
    }

    void BuildQuery() {
        std::string full_rq = rq + request.column + request.tabl + request.where + ";";
        std::cout << full_rq << std::endl;
    }

private:
    Request request;
};



