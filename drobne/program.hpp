#pragma once
#include <input.hpp>
#include <display.hpp>
#include <database.hpp>

class Program {
public:
    Program();
    ~Program();
    void start();

    void setDisplay(display::Display& new_display);
    void setInput(input::Input& new_input);
    void setDatabase(database::Database& new_database);

    display::Display& getDisplay();
    input::Input& getInput();
    database::Database& getDatabase();
private:
    display::Display* display;
    input::Input* input;
    database::Database* database;
};