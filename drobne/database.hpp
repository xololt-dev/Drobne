#pragma once
#include <string>

namespace database {
    class Database {
    public:
        virtual ~Database() {}

        virtual int create(const std::string name = "") = 0;
    protected:
        constexpr const static std::string databaseFolder {"./data"};
    };
}