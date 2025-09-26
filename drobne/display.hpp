#pragma once

namespace display {
    class Display {
    public:
        virtual ~Display() {};
        virtual void render() = 0;
    };
}