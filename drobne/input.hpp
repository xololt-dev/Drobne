#pragma once
#include <vector>

namespace input {
    class Input {
    public:
        virtual ~Input() {};

        virtual std::vector<char> getInputQueue();
    };
}