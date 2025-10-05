#pragma once
#include <navigation_node.hpp>
#include <navigation_renderer.hpp>

namespace navigation {
    class AddAccountNode : public navigation::INavigationNode {
    public:
        // AccountsNode() {}
        AddAccountNode(navigation::Navigator* navigation) {
            this->navigator = navigation;
        }

        std::string getName() const override {
            return "Add Account";
        }
        
        void render(display::INavigationRenderer& r) const override {
            r.drawText("=== Add Account ===");
            r.drawText("[0] Back");
        };

        void handleInput(std::vector<char>& inputQueue) override;
    };
}