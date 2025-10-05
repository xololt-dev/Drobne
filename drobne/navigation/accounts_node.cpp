#include <navigation/add_account_node.hpp>
#include <cassert>
#include <navigation/accounts_node.hpp>

namespace navigation {
    void AccountsNode::handleInput(std::vector<char>& inputQueue) {
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
                // case '1':
                //     navigator->push(std::make_unique<M>(navigator));
                //     break;
                case '+':
                    navigator->push(std::make_unique<AddAccountNode>(navigator));
                    break;
                default:
                    break;
            }
        }
    };
}