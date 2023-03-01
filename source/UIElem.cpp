#include "UIElem.h"

#include <sstream>
#include <iostream>

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

UIListItem::UIListItem(const std::string textContent, const Color backgroundColor, const Color textColor) : UIElem(textContent, backgroundColor, textColor) {
    next = nullptr;
    prev = nullptr;
    selected = false;
}

void UIListItem::select() {
    selected = true;
}

void UIListItem::deselect() {
    selected = false;
}

void UIListItem::doAction() const {
    action();
}

std::string UIListItem::build() const {
    std::ostringstream oss;
    oss << getColorCode() << textContent;
    return oss.str();
}

std::string UIListItem::getColorCode() const {
    std::ostringstream oss;
    if (selected) {
        oss << "\x1b[" << backgroundColor << ';' << textColor << 'm';
    }    
    return oss.str();
}

void UIListItem::setNext(UIListItem* const &item) {
    next = item;
}

void UIListItem::setPrev(UIListItem* const &item) {
    prev = item;
}

template <typename Func> void UIListItem::setAction(Func func) {
    action = func;
}

UIListItem* UIListItem::getNext() const {
    return next;
}

UIListItem* UIListItem::getPrev() const {
    return prev;
}

bool UIListItem::isSelected() const {
    return selected;
}


//==================== UITab ====================

UITab::UITab(UIElem* const elem, const std::string title, const Color backgroundColor, const Color textColor) : UIListItem(title, backgroundColor, textColor) {
    content = elem;
}

void UITab::setContent(UIElem* const elem) {
    content = elem;
}

UIElem* UITab::getContent() const {
    return content;
}

//==================== UIList ====================

UIList::UIList(const Color backgroundColor, const Color textColor) : UIElem("Default List", backgroundColor, textColor) {
    head = nullptr;
    tail = nullptr;
    selected = nullptr;
}

UIList::~UIList() {
    if (head == nullptr) {
        return;
    }

    UIListItem* curItem = head;
    UIListItem* nextItem;
    while(curItem != nullptr) {
        UIListItem* nextItem = curItem->getNext();
        delete curItem;
        curItem = nextItem;
    }
}

UIList::UIList(const UIList &copy) {
    backgroundColor = copy.backgroundColor;
    textColor = copy.textColor;

    if (copy.head != nullptr) {
        UIListItem* curOldItem = copy.head;
        UIListItem* curNewItem;
        UIListItem* prevNewItem = nullptr;
        while(curOldItem != nullptr) {
            curNewItem = new UIListItem(*curOldItem);
            if (prevNewItem != nullptr) {
                prevNewItem->setNext(curNewItem);
            }
            curNewItem->setPrev(prevNewItem);
            if (curOldItem == copy.head) {
                head = curNewItem;
                curNewItem->setPrev(nullptr);
            }
            if (curOldItem == copy.selected) {
                selected = curNewItem;
            }
            if (curOldItem == copy.tail) {
                tail = curNewItem;
                curNewItem->setNext(nullptr);
            }
            curOldItem = curOldItem->getNext();
        }
    }
}

UIList UIList::operator=(const UIList &copy) {
    if (this != &copy) {
        backgroundColor = copy.backgroundColor;
        textColor = copy.textColor;

        if (copy.head != nullptr) {
            UIListItem* curOldItem = copy.head;
            UIListItem* curNewItem;
            UIListItem* prevNewItem = nullptr;
            while(curOldItem != nullptr) {
                curNewItem = new UIListItem(*curOldItem);
                if (prevNewItem != nullptr) {
                    prevNewItem->setNext(curNewItem);
                }
                curNewItem->setPrev(prevNewItem);
                if (curOldItem == copy.head) {
                    head = curNewItem;
                    curNewItem->setPrev(nullptr);
                }
                if (curOldItem == copy.selected) {
                    selected = curNewItem;
                }
                if (curOldItem == copy.tail) {
                    tail = curNewItem;
                    curNewItem->setNext(nullptr);
                }
                curOldItem = curOldItem->getNext();
            }
        }
    }
    return *this;
}

void UIList::prepend(const UIListItem &item) {
    UIListItem* newItem = new UIListItem(item);
    if (head == nullptr) {
        head = newItem;
        tail = newItem;
        selected = newItem;
        newItem->select();
    } else {
        newItem->setNext(head);
        newItem->setPrev(nullptr);
        head = newItem;
        newItem->getNext()->setPrev(newItem);
    }
}

void UIList::insertAt(const UIListItem &item, const int position) {
    insertAfter(item, getItem(position - 1));
}

void UIList::insertAfter(const UIListItem &item, UIListItem* const prevItem) { //TODO: add check for empty list
    UIListItem* newItem = new UIListItem(item);
    newItem->setPrev(prevItem);
    newItem->setNext(prevItem->getNext());
    prevItem->setNext(newItem);
    newItem->getNext()->setPrev(newItem);
}

void UIList::append(const UIListItem &item) {
    UIListItem* newItem = new UIListItem(item);
    if (head == nullptr) {
        head = newItem;
        tail = newItem;
        selected = newItem;
        newItem->select();
    } else {
        tail->setNext(newItem);
        newItem->setPrev(tail);
        newItem->setNext(nullptr);
        tail = newItem;
    }
}

UIListItem* UIList::getItem(const int position) const {
    UIListItem* item = head;
    for (int i = 0; i < position; i++) {
        item = item->getNext();
    }
    return item;
}

UIListItem* UIList::getSelected() const {
    return selected;
}

bool UIList::isEmpty() const {
    return head == nullptr;
}

void UIList::deleteItem(int position) {
    deleteItem(getItem(position));
}

void deleteItem(UIListItem* const item) {
    item->getPrev()->setNext(item->getNext());
    item->getNext()->setPrev(item->getPrev());
    delete item;
}

void UIList::nextItem() {
    if (selected->getNext() == nullptr) {
        return;
    }

    selected->deselect();
    selected = selected->getNext();
    selected->select();
}

void UIList::prevItem() {
    if (selected->getPrev() == nullptr) {
        return;
    }

    selected->deselect();
    selected = selected->getPrev();
    selected->select();
}

void UIList::doSelectedAction() const {
    selected->doAction();
}


//==================== UIHorzList ====================

UIHorzList::UIHorzList(const Color backgroundColor, const Color textColor) : UIList(backgroundColor, textColor) {}

UIHorzList::UIHorzList(const UIList &copy) : UIList(copy) {}

std::string UIHorzList::build() const {
    std::ostringstream oss;
    UIListItem* curItem = head;
    oss << getColorCode();
    while(curItem != nullptr) {
        oss << getColorCode() << ' '  << *curItem << getColorCode() << ' ';
        curItem = curItem->getNext();
    }
    return oss.str();
}


//==================== UITabList ====================

UITabList::UITabList(const Color backgroundColor, const Color textColor) : UIHorzList(backgroundColor, textColor) {}

UITabList::UITabList(const UIList &copy) : UIHorzList(copy) {}

void UITabList::insertAt(const UITab &tab, const int position) {
    insertAfter(tab, getItem(position - 1));
}

void UITabList::insertAfter(const UITab &tab, UITab* const prevTab) {
    UITab* newItem = new UITab(tab);
    newItem->setPrev(prevTab);
    newItem->setNext(prevTab->getNext());
    prevTab->setNext(newItem);
    newItem->getNext()->setPrev(newItem);
}

void UITabList::prepend(const UITab &tab) {
    UITab* newItem = new UITab(tab);
    if (head == nullptr) {
        head = newItem;
        tail = newItem;
        selected = newItem;
        newItem->select();
    } else {
        newItem->setNext(head);
        newItem->setPrev(nullptr);
        head = newItem;
        newItem->getNext()->setPrev(newItem);
    }
}

void UITabList::append(const UITab &tab) {
    UITab* newItem = new UITab(tab);
    if (head == nullptr) {
        head = newItem;
        tail = newItem;
        selected = newItem;
        newItem->select();
    } else {
        tail->setNext(newItem);
        newItem->setPrev(tail);
        newItem->setNext(nullptr);
        tail = newItem;
    }
}

UITab* UITabList::getItem(const int position) const {
    UITab* item = (UITab*)head;
    for (int i = 0; i < position; i++) {
        item = (UITab*)item->getNext();
    }
    return item;
}

UITab* UITabList::getSelected() const {
    return (UITab*)selected;
}

void UITabList::prepend(const UIListItem &item) {}
void UITabList::insertAt(const UIListItem &item, const int position) {}
void UITabList::insertAfter(const UIListItem &item, UIListItem* const prevItem) {}
void UITabList::append(const UIListItem &item) {}

//==================== UIVertList ====================

UIVertList::UIVertList(const Color backgroundColor, const Color textColor) : UIList(backgroundColor, textColor) {}

UIVertList::UIVertList(const UIList &copy) : UIList(copy) {}

std::string UIVertList::build() const {
    std::ostringstream oss;
    UIListItem* curItem = head;
    while(curItem != nullptr) {
        oss << getColorCode() << curItem << getColorCode() << std::endl;
        curItem = curItem->getNext();
    }
    return oss.str();
}

//==================== Other ====================

std::ostream& operator<<(const std::ostream &os, const UIElem &rhs) {
    return std::cout << rhs.build();
}