#pragma once
#include <navigation_renderer.hpp>
#include <cstdlib>
#include <iostream>

namespace display {
    class ConsoleRenderer : public INavigationRenderer {
    public:
        void clearScreen() override {
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

        void drawText(std::string txt) override {
            std::cout << txt << "\n";
        }

        void flush() override {
            std::cout.flush();
        }
    };
}