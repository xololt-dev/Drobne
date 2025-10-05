#pragma once
#include <navigation_renderer.hpp>
#include <navigator.hpp>
#include <input.hpp>
#include <database.hpp>

class Program {
public:
    Program();
    ~Program();
    void start();

    void processInput(std::vector<char>& inputQueue);

    void setInput(input::Input& new_input);
    void setDatabase(database::Database& new_database);

    input::Input& getInput();
    database::Database& getDatabase();
private:
    navigation::Navigator* navigation;
    display::INavigationRenderer* renderer;
    input::Input* input;
    database::Database* database;
};