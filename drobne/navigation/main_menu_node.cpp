#include <cassert>
#include <memory>
#include <navigation/accounts_node.hpp>
#include <navigation/main_menu_node.hpp>

namespace navigation {
    void MainMenuNode::handleInput(std::vector<char>& inputQueue) {
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
                case '1':
                    navigator->push(std::make_unique<AccountsNode>(navigator));
                    break;
                default:
                    break;
            }
        }
    };
}