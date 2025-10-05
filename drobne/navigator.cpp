#include <navigator.hpp>
#include <navigation_node.hpp>
#include <cassert>

namespace navigation {
    void Navigator::push(std::unique_ptr<INavigationNode>&& node) {
        if (!nodeStack.empty()) {
            nodeStack.top()->onExit();
        }
        node->onEnter();
        nodeStack.push(std::move(node));
    }
    
    void Navigator::pop() {
        if (nodeStack.empty()) return;
        
        nodeStack.top()->onExit();
        nodeStack.pop();
        
        if (!nodeStack.empty()) {
            nodeStack.top()->onEnter();
        }
    }
    
    void Navigator::replace(std::unique_ptr<INavigationNode>&& node) {
        assert(!nodeStack.empty());
        
        nodeStack.top()->onExit();
        nodeStack.pop(); // remove old top
        
        node->onEnter();
        nodeStack.push(std::move(node));
    }
    
    INavigationNode* Navigator::getCurrentNode() {
        return nodeStack.empty() ? nullptr : nodeStack.top().get();
    }
}