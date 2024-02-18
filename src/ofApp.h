#pragma once

#include "ofMain.h"
#include "ofxTextInputField.h"
#include "ofxNodeFlowGUI.hpp"

class ofApp : public ofBaseApp{
    
public:
    void setupTxt();
    void setup() override;
    void update() override;
    void draw() override;
    void drawTxt() ;
    void exit() override;
    
    void onButtonSetParametersClicked(nfUI::UIEventArgs& eventArgs);
    
    void keyPressed(int key) override;
    void keyReleased(int key) override;
    void mouseMoved(int x, int y ) override;
    void mouseDragged(int x, int y, int button) override;
    void mousePressed(int x, int y, int button) override;
    void mouseReleased(int x, int y, int button) override;
    void mouseScrolled(int x, int y, float scrollX, float scrollY) override;
    void mouseEntered(int x, int y) override;
    void mouseExited(int x, int y) override;
    void windowResized(int w, int h) override;
    void dragEvent(ofDragInfo dragInfo) override;
    void gotMessage(ofMessage msg) override;
    
    // ofxTextInputField monoLineTextInput, multilineTextInput;
private:
    ofTrueTypeFont _font;
    ofxNodeFlowGUI _nfGUI;
    GUIParams _guiParams;
    NFNode _nfNode;
    std::vector<nfUI::ofxTextInputField> _textInputFields;
    // define a vector of UI Elements
    std::vector<nfUI::UIElement*> _uiElements;
    
};
