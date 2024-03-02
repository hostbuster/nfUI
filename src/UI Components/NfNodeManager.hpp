//
//  NfNodeManager.hpp
//  nodeflowUI
//
//  Created by Matthias Strohmaier on 26.02.24.
//

#ifndef NfNodeManager_hpp
#define NfNodeManager_hpp

#include <vector>
#include <memory>
#include "NfBoxxer.hpp"

namespace nfUI {

class NfNodeManager {
private:
    std::vector<std::shared_ptr<NfBoxxer>> nodes;

public:
    // Add a node
    void addNode(std::shared_ptr<NfBoxxer> node) {
        nodes.push_back(node);
    }

    // Draw all nodes, ensuring the focused node is drawn last
    void drawNodes() {
        // Find the focused node
        auto it = std::find_if(nodes.begin(), nodes.end(),
                               [](const std::shared_ptr<NfBoxxer>& node) { return node->nodeIsFocused; });
        
        if (it != nodes.end()) {
            // Move the focused node to the end of the vector
            std::rotate(it, it + 1, nodes.end());
        }

        // Draw the nodes, with the focused node being drawn last
        for (auto& node : nodes) {
            node->draw();
        }
    }

    // Focus a node by name
    bool focusNode(const std::string& name) {
        auto it = std::find_if(nodes.begin(), nodes.end(),
                               [&name](const std::shared_ptr<NfBoxxer>& node) { return node->_name == name; });
        if (it != nodes.end()) {
            (*it)->focus();
            return true;
        }
        return false;
    }

    // Remove a node
    bool removeNode(const std::string& name) {
        auto it = std::find_if(nodes.begin(), nodes.end(),
                               [&name](const std::shared_ptr<NfBoxxer>& node) { return node->_name == name; });
        if (it != nodes.end()) {
            nodes.erase(it);
            return true;
        }
        return false;
    }
};
} // namespace nfUI


#endif /* NfNodeManager_hpp */
