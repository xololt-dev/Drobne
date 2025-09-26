#pragma once
#include <display.hpp>

namespace display {
    class Console : public Display {
    public:
        Console() {};
        ~Console() override;

        void render() override;
    };
}