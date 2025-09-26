#pragma once
#include <database.hpp>
#include <sqlite3.h>
#include <string>

namespace database {
    class SQLite : public database::Database {
    public:
        ~SQLite() override;

        void create(const std::string name);
        void open(const std::string path);
    private:
        sqlite3 *m_db;

        constexpr const static std::string DEFAULT_NAME {"finances.db"};
    };
}