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
        UIElem(const std::string textContent = "Default Text", const Color backgroundColor = black, const Color textColor = white);
        virtual std::string build() const;
        virtual std::string getColorCode() const;
        void setBackgroundColor(const Color backgroundColor);
        void setTextColor(const Color textColor);
        void setContent(const std::string text);
    protected:
        int backgroundColor;
        int textColor;
        std::string textContent;
};

class UIListItem : public UIElem {
    public:
        UIListItem(const std::string textContent = "Default Item", const Color backgroundColor = white, const Color textColor = black);
        void highlight();
        void dehighlight();
        void select();
        std::string build() const override;
        std::string getColorCode() const override;
        void setNext(const UIListItem* &item);
        void setPrev(const UIListItem* &item);
        UIListItem* getNext() const;
        UIListItem* getPrev() const;
        bool isHighlighted() const;
    protected:
        UIListItem* next;
        UIListItem* prev;
        bool highlighted;

};

class UITab : public UIListItem {
    public:
        UITab(const std::string textContent = "Default Item", const Color backgroundColor = white, const Color textColor = black);
        void setContent(const UIElem &elem);
        UIElem* getContent() const;
    private:
        UIElem* content;
};

class UIList : public UIElem {
    public:
        UIList(const Color backgroundColor = black, const Color textColor = white);
        ~UIList();
        UIList(const UIList &copy);
        virtual void insertItem(const UIListItem &item, const int position = -1); // copy contents of item into new dynamically allocated memory
        virtual UIListItem* getItem(const int position) const;
        virtual UIListItem* getSelected() const;
        bool isEmpty() const;
        void deleteItem(int position);
        void nextItem();
        void backItem();
        void selectItem() const;
    protected:
        UIListItem* head;
        UIListItem* selected;
        
};

class UIHorzList : public UIList {
    public:
        UIHorzList(const Color backgroundColor = black, const Color textColor = white);
        UIHorzList(const UIList &copy);
        std::string build() const override;
};

class UITabList : public UIHorzList {
    public:
        UITabList(const Color backgroundColor = black, const Color textColor = white);
        UITabList(const UIList &copy);
        void insertItem(const UITab &tab, const int position = -1);
        UITab* getItem(const int position) const override;
        UITab* getSelected() const override;
    private:
        void insertItem(const UIListItem &item, const int position = -1) override;
};

class UIVertList : public UIList {
    public:
        UIVertList(const Color backgroundColor = black, const Color textColor = white);
        UIVertList(const UIList &copy);
        std::string build() const override;
};

std::ostream& operator<<(const std::ostream &os, const UIElem &rhs);

#endif