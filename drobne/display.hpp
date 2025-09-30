#pragma once
#include <display/menu.hpp>

namespace display {
    class Display {
    public:
        virtual ~Display() {};
        virtual void render(const display::Menu state) = 0;
    };
}