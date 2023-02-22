#ifndef UI_ELEM_H
#define UI_ELEM_H

#include <iostream>
#include <string>

enum Color {
    black = 30,
    red = 31,
    green = 32,
    yellow = 33,
    blue = 34,
    magenta = 35,
    cyan = 36,
    white = 37,
};

class UIElem {
    public:
        UIElem(std::string textContent = "Default Text", Color backgroundColor = black, Color textColor = white);
        virtual std::string build();
        std::string getColorCode();
        void setBackgroundColor(Color backgroundColor);
        void setTextColor(Color textColor);
        void setContent(std::string text);
    protected:
        int backgroundColor;
        int textColor;
        std::string textContent;
};

class UIListItem : public UIElem {
    public:
        UIListItem(std::string textContent = "Default Item", Color backgroundColor = black, Color textColor = white);
        // ~UIListItem();
        // void highlight();
        // void dehighlight();
        // void select();
        std::string build() override;
    private:
        //std::string getColorCode();
};

class UIList : public UIElem {
    public:
        UIList(int numItems = -1, UIListItem list[] = nullptr, Color backgroundColor = blue, Color textColor = white);
        ~UIList();
        UIList(const UIList &copy);
        UIList operator=(UIList &rhs);
        void addListItem(UIListItem item);
        void deleteListItem(int index);
        void setList(UIListItem* newList, int newNumItems);
        void menuLeft();
        void menuRight();
        void menuSelect();
    protected:
        UIListItem* list;
        int numItems;
        UIListItem* copyArray(int numItems, UIListItem* oldList, int newNumItems);
        
};

class UIHorzList : public UIList {
    public:
        UIHorzList(int numItems = -1, UIListItem list[] = nullptr, Color backgroundColor = blue, Color textColor = white);
        UIHorzList(const UIList &copy);
        std::string build() override;
};

class UIVertList : public UIList {
    public:
        UIVertList(int numItems = -1, UIListItem list[] = nullptr, Color backgroundColor = white, Color textColor = black);
        UIVertList(const UIList &copy);
        std::string build() override;
};

std::ostream& operator<<(std::ostream &os, UIElem &rhs);

#endif