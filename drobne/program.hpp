#pragma once
#include <display.hpp>
#include <database.hpp>

class Program {
public:
    void start();

    void setDisplay(display::Display& new_display);
    void setDatabase(database::Database& new_database);
private:
    display::Display* display;
    database::Database* database;
};