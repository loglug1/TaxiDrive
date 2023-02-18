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
        UIElem(std::string textContent = "Default Text", Color backgroundColor = black, Color color = white);
        std::string build();
    protected:
        int backgroundColor = black;
        int color = white;
        std::string textContent = "Default Text";
};

class UIHorzList : public UIElem {
    public:
        UIHorzList(std::string textContent = "Default Text", Color backgroundColor = blue, Color color = white);
};

std::ostream& operator<<(std::ostream &os, UIElem &rhs);

#endif