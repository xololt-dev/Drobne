#pragma once
#include <navigation_node.hpp>
#include <navigation_renderer.hpp>

namespace navigation {
    class AccountsNode : public navigation::INavigationNode {
    public:
        // AccountsNode() {}
        AccountsNode(navigation::Navigator* navigation) {
            this->navigator = navigation;
        }

        std::string getName() const override {
            return "Accounts";
        }
        
        void render(display::INavigationRenderer& r) const override {
            r.drawText("=== Accounts ===");
            // r.drawText("[1] Play Game");
            // r.drawText("[2] Options");
            r.drawText("[+] Add account");
            r.drawText("[0] Back");
        };

        void handleInput(std::vector<char>& inputQueue) override;
    };
}