#include <iostream>
#include <program.hpp>
#include <display/console.hpp>

int main() {
    Program program;
    display::Console* cg = new display::Console();
    program.setDisplay(*cg);

    std::cout << "Hello world!";
    return 0;
}