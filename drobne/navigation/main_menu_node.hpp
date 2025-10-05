#pragma once
#include <navigation_node.hpp>
#include <navigation_renderer.hpp>

namespace navigation {
    class MainMenuNode : public navigation::INavigationNode {
    public:
        // MainMenuNode() {}
        MainMenuNode(navigation::Navigator* navigation) {
            this->navigator = navigation;
        }

        std::string getName() const override {
            return "Main Menu";
        }
        
        void render(display::INavigationRenderer& r) const override {
            r.drawText("=== Main Menu ===");
            r.drawText("[1] Accounts");
            r.drawText("[2] Investments");
            r.drawText("[3] Predictions");
            r.drawText("[0] Quit");
        };

        void handleInput(std::vector<char>& inputQueue) override;
    };
}