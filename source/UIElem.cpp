#include "UIElem.h"

#include <sstream>

//==================== UIElem ====================

UIElem::UIElem(std::string textContent, Color backgroundColor, Color textColor) {
    this->textContent = textContent;
    this->backgroundColor = backgroundColor + 10;
    this->textColor = textColor;
}

std::string UIElem::build() {
    std::ostringstream oss;
    oss << getColorCode() << textContent;
    return oss.str();
}

std::string UIElem::getColorCode() {
    std::ostringstream oss;
    oss << "\x1b[" << backgroundColor << ';' << textColor << 'm';
    return oss.str();
}

void UIElem::setBackgroundColor(Color backgroundColor) { this->backgroundColor = backgroundColor; }
void UIElem::setTextColor(Color textColor) { this->textColor = textColor; }
void UIElem::setContent(std::string text) { this->textContent = text; }

//==================== UIHorzList ====================

UIList::UIList(int numItems, UIListItem list[], Color backgroundColor, Color textColor) {
    if (numItems == -1) {
        this->numItems = 1;
        this->list = new UIListItem[this->numItems];
        this->list[0] = UIListItem();
    } else {
        this->numItems = numItems;
        this->list = copyArray(numItems, list, numItems);
    }
    this->backgroundColor = backgroundColor + 10;
    this->textColor = textColor;
    this->textContent = "You shouldn't see this";
}

UIList::~UIList() {
    delete [] this->list;
}

UIList::UIList(const UIList &copy) {
    this->numItems = copy.numItems;
    this->list = copyArray(copy.numItems, copy.list, copy.numItems);
    this->backgroundColor = copy.backgroundColor;
    this->textColor = copy.textColor; 
}

UIList UIList::operator=(UIList &rhs) {
    UIList obj(rhs.numItems, rhs.list, (Color)rhs.backgroundColor, (Color)rhs.textColor);
    return obj;
}

UIListItem* UIList::copyArray(int numItems, UIListItem* oldList, int newNumItems) {
    UIListItem* newList = new UIListItem[newNumItems];
    for (int i = 0; i < numItems; i++) {
        newList[i] = oldList[i];
    }
    return newList;
}

//==================== UIListItem ====================

UIListItem::UIListItem(std::string textContent, Color backgroundColor, Color textColor) : UIElem(textContent, backgroundColor, textColor) {}

std::string UIListItem::build() {
    return getColorCode() + textContent;
}

//==================== UIHorzList ====================

UIHorzList::UIHorzList(int numItems, UIListItem list[], Color backgroundColor, Color textColor) : UIList(numItems, list, backgroundColor, textColor) {}
UIHorzList::UIHorzList(const UIList &copy) : UIList(copy) {}

std::string UIHorzList::build() {
    std::ostringstream oss;
    for (int i = 0; i < numItems; i++) {
        oss << getColorCode() << ' ' << this->list[i].build() << getColorCode();
    }
    return oss.str();
}

//==================== UIVertList ====================

UIVertList::UIVertList(int numItems, UIListItem list[], Color backgroundColor, Color textColor) : UIList(numItems, list, backgroundColor, textColor) {}
UIVertList::UIVertList(const UIList &copy) : UIList(copy) {}

std::string UIVertList::build() {
    std::ostringstream oss;
    for (int i = 0; i < numItems; i++) {
        oss << getColorCode() << ' ' << this->list[i].build() << getColorCode() << std::endl;
    }
    return oss.str();
}

//==================== Other ====================

std::ostream& operator<<(std::ostream &os, UIElem &rhs) {
    return std::cout << rhs.build();
}