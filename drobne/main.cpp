#include <database/sqlite.hpp>
#include <program.hpp>
#include <display/console.hpp>

int main() {
    Program* program = new Program();

    program->start();

    return 0;
}