#ifndef UI_INTERFACE_H
#define UI_INTERFACE_H

#include <3ds.h>
#include "UIElem.h"

class UIInterface {
    public:
        UIInterface(UIHorzList<UIListItem>* statusBar, UIHorzList<UITab>* navBar);
        void menuDown() const;
        void menuUp() const;
        void menuRight() const;
        void menuLeft() const;
        void draw();
    private:
        UIHorzList<UIListItem>* statusBar;
        UIElem* mainContent;
        UIHorzList<UITab>* navBar;
        PrintConsole statusConsole;
        PrintConsole mainConsole;
        PrintConsole navConsole;
};

#endif