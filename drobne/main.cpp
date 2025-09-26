#include <database/sqlite.hpp>
#include <iostream>
#include <program.hpp>
#include <display/console.hpp>

int main() {
    Program program;
    display::Console* cg = new display::Console();
    database::SQLite* sqlite = new database::SQLite();
    program.setDisplay(*cg);
    program.setDatabase(*sqlite);

    sqlite->open("./newDb.db");

    std::cout << "Hello world!";

    delete cg;
    delete sqlite;

    return 0;
}