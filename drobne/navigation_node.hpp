#pragma once
#include <navigation_renderer.hpp>
#include <navigator.hpp>
#include <string>

namespace navigation {
    class INavigationNode {
    public:
        INavigationNode() {}
        virtual ~INavigationNode() = default;

        // Optional title or identifier
        virtual std::string getName() const = 0;
        
        // Called when entering this node
        virtual void onEnter() {}

        virtual void handleInput(std::vector<char>& inputQueue) = 0;
        
        // Render using any renderer provided
        virtual void render(class display::INavigationRenderer& renderer) const = 0;
        
        // Called before exiting
        virtual void onExit() {}

        void setNavigator(Navigator& navigator) {
            this->navigator = &navigator;
        }
    protected:
        navigation::Navigator* navigator;
    };
}