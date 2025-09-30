#pragma once
#include <input.hpp>
#include <display.hpp>
#include <display/menu.hpp>
#include <database.hpp>
#include <stack>

class Program {
public:
    Program();
    ~Program();
    void start();

    void processInput(std::vector<char>& inputQueue);

    void setDisplay(display::Display& new_display);
    void setInput(input::Input& new_input);
    void setDatabase(database::Database& new_database);

    display::Display& getDisplay();
    input::Input& getInput();
    database::Database& getDatabase();
private:
    std::stack<display::Menu, std::vector<display::Menu>> navigationStack;

    display::Display* display;
    input::Input* input;
    database::Database* database;
};