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

template <typename T> UIList<T>::UIList(const Color backgroundColor, const Color textColor) : UIElem("Default List", backgroundColor, textColor) {
    head = nullptr;
    tail = nullptr;
    selected = nullptr;
}

template <typename T> UIList<T>::~UIList() {
    if (head == nullptr) {
        return;
    }

    T* curItem = head;
    T* nextItem;
    while(curItem != nullptr) {
        T* nextItem = curItem->getNext();
        delete curItem;
        curItem = nextItem;
    }
}

template <typename T> UIList<T>::UIList(const UIList &copy) {
    backgroundColor = copy.backgroundColor;
    textColor = copy.textColor;

    if (copy.head != nullptr) {
        T* curOldItem = copy.head;
        T* curNewItem;
        T* prevNewItem = nullptr;
        while(curOldItem != nullptr) {
            curNewItem = new T(*curOldItem);
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

template <typename T> UIList<T> UIList<T>::operator=(const UIList<T> &copy) {
    if (this != &copy) {
        backgroundColor = copy.backgroundColor;
        textColor = copy.textColor;

        if (copy.head != nullptr) {
            T* curOldItem = copy.head;
            T* curNewItem;
            TIMESPEC_TO_TIMEVAL* prevNewItem = nullptr;
            while(curOldItem != nullptr) {
                curNewItem = new T(*curOldItem);
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

template <typename T> void UIList<T>::prepend(const T &item) {
    T* newItem = new T(item);
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

template <typename T> void UIList<T>::insertAt(const T &item, const int position) {
    insertAfter(item, getItem(position - 1));
}

template <typename T> void UIList<T>::insertAfter(const T &item, T* const prevItem) { //TODO: add check for empty list
    T* newItem = new T(item);
    newItem->setPrev(prevItem);
    newItem->setNext(prevItem->getNext());
    prevItem->setNext(newItem);
    newItem->getNext()->setPrev(newItem);
}

template <typename T> void UIList<T>::append(const T &item) {
    T* newItem = new T(item);
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

template <typename T> T* UIList<T>::getItem(const int position) const {
    T* item = head;
    for (int i = 0; i < position; i++) {
        item = item->getNext();
    }
    return item;
}

template <typename T> T* UIList<T>::getSelected() const {
    return selected;
}

template <typename T> bool UIList<T>::isEmpty() const {
    return head == nullptr;
}

template <typename T> void UIList<T>::deleteItem(int position) {
    deleteItem(getItem(position));
}

template <typename T> void deleteItem(T* const item) {
    item->getPrev()->setNext(item->getNext());
    item->getNext()->setPrev(item->getPrev());
    delete item;
}

template <typename T> void UIList<T>::nextItem() {
    if (selected->getNext() == nullptr) {
        return;
    }

    selected->deselect();
    selected = selected->getNext();
    selected->select();
}

template <typename T> void UIList<T>::prevItem() {
    if (selected->getPrev() == nullptr) {
        return;
    }

    selected->deselect();
    selected = selected->getPrev();
    selected->select();
}

template <typename T> void UIList<T>::doSelectedAction() const {
    selected->doAction();
}


//==================== UIHorzList ====================

template <typename T> UIHorzList<T>::UIHorzList(const Color backgroundColor, const Color textColor) : UIList<T>(backgroundColor, textColor) {}

template <typename T> UIHorzList<T>::UIHorzList(const UIList<T> &copy) : UIList(copy) {}

template <typename T> std::string UIHorzList<T>::build() const {
    std::ostringstream oss;
    UIListItem* curItem = head;
    oss << getColorCode();
    while(curItem != nullptr) {
        oss << getColorCode() << ' '  << *curItem << getColorCode() << ' ';
        curItem = curItem->getNext();
    }
    return oss.str();
}

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