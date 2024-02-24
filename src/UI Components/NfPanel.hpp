//
//  NfPanel.hpp
//  nodeflowUI
//
//  Created by Matthias Strohmaier on 23.02.24.
//

#ifndef NfPanel_hpp
#define NfPanel_hpp

#include "ofMain.h"
#include "NfBoxxer.hpp"

namespace nfUI {

class NfPanel : public NfBoxxer {
    
private:
    bool _firstRender = true; // Flag to track if draw() was called for the first time
    
public:
    // Inherit NfBoxxer constructor
    using NfBoxxer::NfBoxxer;
    
    void draw() override {
        ofPushMatrix();
        NfBoxxer::draw(); // Call base class draw for common drawing
        
        if (_firstRender) {
            std::cout << "NfPanel: " << _name << std::endl;
            _firstRender=false;
        }

        if (isFocused.get()) {
            ofSetColor(focusColor.get());
        } else {
            ofSetColor(backgroundColor.get());
        }
        
        // get Dimensions children requires
        this->getDimensions(_config.width, _config.height);
        // draw own content
        ofDrawRectangle(0, 0, _config.width, _config.height);
        
        // call drawChildren with the current paddings
        drawChildren(_config.paddingLeft, _config.paddingTop);
        
        ofPopMatrix(); // Restore the drawing context
    }
};

}


#endif /* NfPanel_hpp */
