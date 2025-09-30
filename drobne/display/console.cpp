#include <display/console.hpp>
#include <iostream>
#include <display/menu.hpp>

namespace display {
    Console::~Console() {
    }

    void Console::render(const display::Menu state) {
        clear();

        switch (state) {
        case MAIN_MENU:
            renderMainMenu();
            break;
        default:
            std::cout << "Hello world!";
            break;
        }
    }

    void Console::renderMainMenu() {
        std::string options[3] = {"Accounts", "Investments", "Predictions"}; 
        std::cout << "\n===  MainMenu  ===" << std::endl;
        for (size_t i = 0; i < sizeof(options) / sizeof(options[0]); ++i) {
            std::cout << (i + 1) << ". " << options[i] << std::endl;
        }
        std::cout << "0. Exit" << std::endl;
        std::cout << "==================" << std::endl;
    }

    void Console::clear() {
    #if defined _WIN32
        system("cls");
        //clrscr(); // including header file : conio.h
    #elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
        system("clear");
        //std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences 
    #elif defined (__APPLE__)
        system("clear");
    #endif
    }
}