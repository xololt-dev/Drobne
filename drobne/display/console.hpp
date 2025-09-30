#pragma once
#include <display.hpp>
#include <display/menu.hpp>

namespace display {
    class Console : public Display {
    public:
        Console() {};
        ~Console() override;

        void render(const display::Menu state) override;
    private:
        void renderMainMenu();

        void clear();
    };
}