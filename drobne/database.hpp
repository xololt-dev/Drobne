#pragma once
#include <string>

namespace database {
    class Database {
    public:
        virtual ~Database() {}
    protected:
        constexpr const static std::string databaseFolder {"./data"};
    };
}