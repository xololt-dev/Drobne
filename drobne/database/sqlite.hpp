#pragma once
#include <database.hpp>
#include <sqlite3.h>
#include <string>

namespace database {
    class SQLite : public database::Database {
    public:
        ~SQLite() override;

        int create(const std::string name = "") override;
        int open(const std::string path);

        int prepare(const std::string statement, const unsigned int flags, sqlite3_stmt** handle);

        int bind(sqlite3_stmt* sqlite_statement, int index);
        int bind(sqlite3_stmt* sqlite_statement, int index, int value);
        int bind(sqlite3_stmt* sqlite_statement, int index, sqlite3_int64 value);
        int bind(sqlite3_stmt* sqlite_statement, int index, double value);
        int bind(sqlite3_stmt* sqlite_statement, int index, std::string value, sqlite3_destructor_type destructor);
        // BLOB & JSON
        int bind(sqlite3_stmt* sqlite_statement, int index, const void* value, int size, sqlite3_destructor_type destructor);

        int step(sqlite3_stmt* sqlite_statement);

    private:
        using sqlite3_destructor_type = void(*)(void*);
        using sqlite3_blob_type = const void*;

        sqlite3 *m_db;

        constexpr const static std::string DEFAULT_NAME {"finances.db"};
    };
}