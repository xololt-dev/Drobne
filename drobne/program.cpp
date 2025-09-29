#include <display/console.hpp>
#include <input.hpp>
#include <database/sqlite.hpp>
#include <iostream>
#include <program.hpp>
#include <database.hpp>
#include <display.hpp>

Program::Program() {
    this->database = new database::SQLite();
    this->display = new display::Console();
}

Program::~Program() {
    delete database;
    delete display;
    delete input;
}

void Program::start() {
    // while (true) {
    std::cout << database->create() << std::endl;
    
    display->render();

        // get input
    // }
}

void Program::setDisplay(display::Display& new_display) {
    display = &new_display;
}

void Program::setDatabase(database::Database& new_database) {
    database = &new_database;
}

display::Display& Program::getDisplay() {
    return *display;
}

database::Database& Program::getDatabase() {
    return *database;
}

input::Input& Program::getInput() {
    return *input;
}