#include <display/menu.hpp>
#include <display/console.hpp>
#include <input.hpp>
#include <database/sqlite.hpp>
#include <iostream>
#include <ostream>
#include <program.hpp>
#include <database.hpp>
#include <display.hpp>
#include <vector>

Program::Program() {
    this->database = new database::SQLite();
    this->display = new display::Console();

    navigationStack.push(display::Menu::MAIN_MENU);
}

Program::~Program() {
    delete database;
    delete display;
    delete input;
}

void Program::start() {
    std::cout << database->create() << std::endl;
    std::vector<char> inputQueue;

    display->render(navigationStack.top());
    while (true) {
        // std::vector<char> inputQueue = input->getInputQueue();
        int kodASCII = 0;
        while (kodASCII != 10) {
            kodASCII = getchar();
            inputQueue.emplace_back(kodASCII);
        }
        processInput(inputQueue);
        inputQueue.clear();

        if (navigationStack.empty()) {
            break;
        }

        display->render(navigationStack.top());
    }
}

void Program::processInput(std::vector<char>& inputQueue) {
    for (char& val : inputQueue) {
        switch (val) {
            // Backspace
            case 8:
                break;
            // Enter
            case 13:
                break;
            // ESC
            case 27:
                navigationStack.pop();
                break;
            // Space
            case 32:
                break;
            default:
                break;
        }
    }
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