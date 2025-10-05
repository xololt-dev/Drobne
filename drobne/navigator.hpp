#pragma once
#include <stack>
#include <memory>
#include <vector>

namespace navigation {
    class INavigationNode;

    class Navigator {
    private:
        std::stack<std::unique_ptr<INavigationNode>, std::vector<std::unique_ptr<INavigationNode>>> nodeStack;

    public:
        inline bool isEmpty() const { return nodeStack.empty(); }
        inline size_t size() const { return nodeStack.size(); }

        // Push new page onto the stack
        void push(std::unique_ptr<INavigationNode>&& node);

        // Replace current page with new one
        void replace(std::unique_ptr<INavigationNode>&& node);

        // Pop back to previous page
        void pop();

        // Get current visible page
        [[nodiscard]] INavigationNode* getCurrentNode();

        // Clear all pages except root (optional method)
        void resetToRoot();
    };
}