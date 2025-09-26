#include <database/sqlite.hpp>
#include <sqlite3.h>
#include <filesystem>
#include <string>

namespace database {
    SQLite::~SQLite() {
        sqlite3_close(m_db);
    }

    void SQLite::create(const std::string name) {
        if (!std::filesystem::exists(databaseFolder) || !std::filesystem::is_directory(databaseFolder)) {
            std::filesystem::create_directory(databaseFolder);
        }

        open(databaseFolder + "/" + DEFAULT_NAME);
    }

    void SQLite::open(const std::string path) {
        int status;

        status = sqlite3_open(path.c_str(), &m_db);

        if (status != SQLITE_OK) {
            // ERROR SQLITE
        }
    }
}