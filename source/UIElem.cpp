#include "UIElem.h"

#include <sstream>

UIElem::UIElem(std::string textContent, Color backgroundColor, Color color) {
    this->textContent = textContent;
    this->backgroundColor = backgroundColor + 10;
    this->color = color;
}

UIHorzList::UIHorzList(std::string textContent, Color backgroundColor, Color color) {
    this->textContent = textContent;
    this->backgroundColor = backgroundColor + 10;
    this->color = color;
}

std::string UIElem::build() {
    std::ostringstream oss;
    oss << "\x1b[" << backgroundColor << ';' << color << 'm' << textContent;
    return oss.str();
}

std::ostream& operator<<(std::ostream &os, UIElem &rhs) {
    return std::cout << rhs.build();
}