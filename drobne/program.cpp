#include <iostream>
#include <ostream>
#include <vector>

#include <navigator.hpp>
#include <navigation_node.hpp>
#include <navigation/main_menu_node.hpp>
#include <input.hpp>
#include <database.hpp>
#include <database/sqlite.hpp>
#include <program.hpp>
#include <display.hpp>
#include <display/console_renderer.hpp>

Program::Program() {
    this->database = new database::SQLite();
    this->renderer = new display::ConsoleRenderer();
    this->navigation = new navigation::Navigator();

    navigation->push(std::make_unique<navigation::MainMenuNode>(navigation));
}

Program::~Program() {
    delete database;
    delete renderer;
    delete input;
    delete navigation;
}

void Program::start() {
    std::cout << database->create() << std::endl;
    std::vector<char> inputQueue;

    while (!navigation->isEmpty()) {
        navigation::INavigationNode* currentNode = navigation->getCurrentNode();

        if (!currentNode) {
            break;
        }

        renderer->clearScreen();
        currentNode->render(*renderer);

        int codeASCII = 0;
        while (codeASCII != 10) {
            codeASCII = getchar();
            inputQueue.emplace_back(codeASCII);
        }
        currentNode->handleInput(inputQueue);
        inputQueue.clear();
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
                navigation->pop();
                break;
            // Space
            case 32:
                break;
            default:
                break;
        }
    }
}

void Program::setDatabase(database::Database& new_database) {
    database = &new_database;
}

database::Database& Program::getDatabase() {
    return *database;
}

input::Input& Program::getInput() {
    return *input;
}