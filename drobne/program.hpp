#pragma once
#include <display.hpp>
#include <database.hpp>

class Program {
public:
    void start();

    void setDisplay(display::Display display);
    void setDatabase(database::Database database);
private:
    display::Display* display;
    database::Database* database;
};