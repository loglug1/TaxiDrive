#ifndef UI_ELEM_H
#define UI_ELEM_H

#include <string>
#include <functional>

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
        void select();
        void deselect();
        void doAction() const;
        std::string build() const override;
        std::string getColorCode() const override;
        void setNext(UIListItem* const &item);
        void setPrev(UIListItem* const &item);
        template <typename Func> void setAction(Func func);
        UIListItem* getNext() const;
        UIListItem* getPrev() const;
        bool isSelected() const;
    protected:
        UIListItem* next;
        UIListItem* prev;
        std::function<void()> action;
        bool selected;

};

class UITab : public UIListItem {
    public:
        UITab(UIElem* const elem = nullptr, const std::string title = "Default Tab", const Color backgroundColor = white, const Color textColor = black);
        void setContent(UIElem* const elem);
        UIElem* getContent() const;
    private:
        UIElem* content;
};

template <typename T> class UIList : public UIElem {
    public:
        UIList(const Color backgroundColor = black, const Color textColor = white);
        ~UIList();
        UIList(const UIList &copy);
        UIList<T> operator=(const UIList<T> &copy);
        virtual void prepend(const T &item);
        virtual void insertAt(const T &item, const int position);
        virtual void insertAfter(const T &item, T* const prevItem);
        virtual void append(const T &item);
        virtual T* getItem(const int position) const;
        virtual T* getSelected() const;
        bool isEmpty() const;
        void deleteItem(int position);
        void deleteItem(T* const item);
        void nextItem();
        void prevItem();
        void doSelectedAction() const;
    protected:
        T* head;
        T* tail;
        T* selected;
        
};

template <typename T> class UIHorzList : public UIList<T> {
    public:
        UIHorzList(const Color backgroundColor = black, const Color textColor = white);
        UIHorzList(const UIList<T> &copy);
        std::string build() const override;
};

class UIVertList : public UIList<UIListItem> {
    public:
        UIVertList(const Color backgroundColor = black, const Color textColor = white);
        UIVertList(const UIList &copy);
        std::string build() const override;
};

std::ostream& operator<<(const std::ostream &os, const UIElem &rhs);

#endif