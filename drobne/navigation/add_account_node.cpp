#include <cassert>
#include <navigation/add_account_node.hpp>

namespace navigation {
    void AddAccountNode::handleInput(std::vector<char>& inputQueue) {
        assert(navigator != nullptr);

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
                case '0':
                    navigator->pop();
                    break;
                // Space
                case 32:
                    break;
                default:
                    break;
            }
        }
    };
}