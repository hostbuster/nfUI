//
//  ofxNodeFlowGUI.hpp
//  nodeflowUI
//
//  Created by Matthias Strohmaier on 15.02.24.
//

#ifndef ofxNodeFlowGUI_hpp
#define ofxNodeFlowGUI_hpp

#include "ofMain.h"
// dependencies
#include "ofxTextInputField.h"

//--------------------------------------------------------------
class NFValue {
public:
    virtual ~NFValue() {}
};

// Example NFValues using ofParameter types
class StringNFValue : public NFValue {
public:
    ofParameter<std::string> value;
    StringNFValue(const std::string& initialValue) : value(initialValue) {}
};

class DoubleNFValue : public NFValue {
public:
    ofParameter<double> value;
    DoubleNFValue(double initialValue) : value(initialValue) {}
};

class BoolNFValue : public NFValue {
public:
    ofParameter<bool> value;
    BoolNFValue(bool initialValue) : value(initialValue) {}
};

class IntNFValue : public NFValue {
public:
    ofParameter<int> value;
    IntNFValue(int initialValue) : value(initialValue) {}
};


//--------------------------------------------------------------
// NFNode class
class NFNode {
private:
    std::vector<NFValue*> nfValues;
    std::vector<NFValue*> drawOrder; // Order of components for drawing

public:
    ~NFNode() {
        // Cleanup NFValues
        for (NFValue* nfValue : nfValues) {
            delete nfValue;
        }
    }

    
    // Add an NFValue to the node with label, value, and textInputField
    template <typename T, typename... Args>
    T* addNFValue(const std::string& label, Args&&... args, nfUI::ofxTextInputField& textInputField, uint32_t x, uint32_t y, uint32_t width, uint32_t height, ofTrueTypeFont& font) {
        T* newNFValue = new T(std::forward<Args>(args)...);
        newNFValue->value.setName(label); // Set the label for the parameter
        nfValues.push_back(newNFValue);
        drawOrder.push_back(newNFValue); // Add to draw order
        
        // Set up the textInputField
        textInputField.disable();
        textInputField.position.x = x;
        textInputField.position.y = y;
        textInputField.position.height = height;
        textInputField.position.width = width;
        
        // Convert the value to a string and assign it to textInputField.text
        // we don't use name here but I left it in for later debugging purposes
        std::string name, value;
        // get name and value as strings for display
        if (typeid(StringNFValue) == typeid(*newNFValue)) {
            StringNFValue* strNFValue = dynamic_cast<StringNFValue*>(newNFValue);
            name = strNFValue->value.getName();
            value = strNFValue->value.get();
        } else if (typeid(DoubleNFValue) == typeid(*newNFValue)) {
            DoubleNFValue* doubleNFValue = dynamic_cast<DoubleNFValue*>(newNFValue);
            name = doubleNFValue->value.getName();
            value = ofToString(doubleNFValue->value.get());
        } else if (typeid(BoolNFValue) == typeid(*newNFValue)) {
            BoolNFValue* boolNFValue = dynamic_cast<BoolNFValue*>(newNFValue);
            name = boolNFValue->value.getName();
            value = ofToString(boolNFValue->value.get());
        } else if (typeid(IntNFValue) == typeid(*newNFValue)) {
            IntNFValue* intNFValue = dynamic_cast<IntNFValue*>(newNFValue);
            name = intNFValue->value.getName();
            value = ofToString(intNFValue->value.get());
        }
        
        textInputField.text = value;
        // textInputField.setFont(font); // we just render the default bitmap font
        return newNFValue;
    }

    // Get an NFValue of a specific type
    template <typename T>
    T* getNFValue() const {
        for (NFValue* nfValue : nfValues) {
            if (typeid(T) == typeid(*nfValue)) {
                return dynamic_cast<T*>(nfValue);
            }
        }
        return nullptr;
    }

    // Get the draw order
    const std::vector<NFValue*>& getDrawOrder() const {
        return drawOrder;
    }
};
     
/*
// Add an NFValue to the node with label, value, and textInputField
template <typename T, typename TextFieldType, typename... Args>
T* addNFValue(const std::string& label, Args&&... args, TextFieldType& textInputField, uint32_t x, uint32_t y, uint32_t width, uint32_t height, ofTrueTypeFont& font) {
    T* newNFValue = new T(std::forward<Args>(args)...);
    newNFValue->value.setName(label); // Set the label for the parameter
    nfValues.push_back(newNFValue);
    drawOrder.push_back(newNFValue); // Add to draw order
    
    // Set up the textInputField
    textInputField.disable();
    textInputField.position.x = x;
    textInputField.position.y = y;
    textInputField.position.height = height;
    textInputField.position.width = width;
    
    // Convert the value to a string and assign it to textInputField.text
    std::string name, value;
    // get name and value as strings for display
    if (typeid(StringNFValue) == typeid(*newNFValue)) {
        StringNFValue* strNFValue = dynamic_cast<StringNFValue*>(newNFValue);
        name = strNFValue->value.getName();
        value = strNFValue->value.get();
    } else if (typeid(DoubleNFValue) == typeid(*newNFValue)) {
        DoubleNFValue* doubleNFValue = dynamic_cast<DoubleNFValue*>(newNFValue);
        name = doubleNFValue->value.getName();
        value = ofToString(doubleNFValue->value.get());
    } else if (typeid(BoolNFValue) == typeid(*newNFValue)) {
        BoolNFValue* boolNFValue = dynamic_cast<BoolNFValue*>(newNFValue);
        name = boolNFValue->value.getName();
        value = ofToString(boolNFValue->value.get());
    } else if (typeid(IntNFValue) == typeid(*newNFValue)) {
        IntNFValue* intNFValue = dynamic_cast<IntNFValue*>(newNFValue);
        name = intNFValue->value.getName();
        value = ofToString(intNFValue->value.get());
    }
    
    textInputField.text = value;
    // textInputField.setFont(font); // we just render the default bitmap font
    return newNFValue;
};
*/


class ofxNodeFlowGUI {
public:
    ofxNodeFlowGUI();
    virtual ~ofxNodeFlowGUI();
    
    void setup(NFNode& _nfNode, std::vector<nfUI::ofxTextInputField>& _textInputFields);
    void update(NFNode& nfNode, std::vector<nfUI::ofxTextInputField>& _textInputFields);
    void drawPanel(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
    void drawValue(NFNode& _nfNode, std::vector<nfUI::ofxTextInputField>& _textInputFields);
    void draw(NFNode& _nfNode, std::vector<nfUI::ofxTextInputField>& _textInputFields);
    nfUI::NfUIConfig _nfuiConfig;
protected:
    ofTrueTypeFont _font;
    
};

#endif /* ofxNodeFlowGUI_hpp */