#include "UIElem.h"

#include <sstream>

//==================== UIElem ====================

UIElem::UIElem(const std::string textContent, const Color backgroundColor, const Color textColor) {
    this->textContent = textContent;
    this->backgroundColor = backgroundColor + 10;
    this->textColor = textColor;
}

std::string UIElem::build() const {
    std::ostringstream oss;
    oss << getColorCode() << textContent;
    return oss.str();
}

std::string UIElem::getColorCode() const {
    std::ostringstream oss;
    oss << "\x1b[" << backgroundColor << ';' << textColor << 'm';
    return oss.str();
}

void UIElem::setBackgroundColor(const Color backgroundColor) { this->backgroundColor = backgroundColor; }
void UIElem::setTextColor(const Color textColor) { this->textColor = textColor; }
void UIElem::setContent(const std::string text) { this->textContent = text; }

//==================== UIListItem ====================


//==================== UITab ====================


//==================== UIList ====================


//==================== UIHorzList ====================


//==================== UITabList ====================


//==================== UIVertList ====================


//==================== Other ====================

std::ostream& operator<<(const std::ostream &os, const UIElem &rhs) {
    return std::cout << rhs.build();
}