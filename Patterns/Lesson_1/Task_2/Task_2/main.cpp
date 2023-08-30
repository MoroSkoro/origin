#include <iostream>
#include "map"
#include "vector"
#include "chrono"
#include "sql_query_builder.h"
#include <string>

int main() {
    std::vector<std::string> columns{{"id", "status", "curs"}};
    std::map<std::string, std::string> kv{
        {"name", "Bob"}, {"phon", "911"}
    };
    SqlSelectQueryBuilder query_builder;
    query_builder.AddColumns_vec(columns);
    query_builder.AddColumn("name").AddColumn("phone");
    query_builder.AddFrom("students");
    query_builder.AddWhere_map(kv);
    query_builder.AddWhere("id", "42").AddWhere("name", "John");

    query_builder.BuildQuery();

    //static_assert(query_builder.BuildQuery(),
                    //"SELECT name, phone FROM students WHERE id=42 AND name=John;");

    return 0;
}