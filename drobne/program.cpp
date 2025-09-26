#include <program.hpp>
#include <database.hpp>
#include <display.hpp>

void Program::setDisplay(display::Display& new_display) {
    display = &new_display;
}

void Program::setDatabase(database::Database& new_database) {
    database = &new_database;
}