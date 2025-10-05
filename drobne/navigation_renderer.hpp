#pragma once
#include <string>

namespace display {
    class INavigationRenderer {
        public:
        virtual ~INavigationRenderer() = default;
        virtual void clearScreen() = 0;
        virtual void drawText(std::string) = 0;
        virtual void flush() {}  // optional end-frame step
    };
}