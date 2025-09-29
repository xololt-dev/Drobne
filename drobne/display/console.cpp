#include <display/console.hpp>
#include <iostream>

namespace display {
    Console::~Console() {
    }

    void Console::render() {
        std::cout << "Hello world!";

        return;
    }
}