#ifndef UI_INTERFACE_H
#define UI_INTERFACE_H

#include <3ds.h>
#include "UIElem.h"

class UIInterface {
    public:
        UIInterface(UIHorzList* statusBar, UITabList* navBar);
        void menuDown() const;
        void menuUp() const;
        void menuRight() const;
        void menuLeft() const;
        void draw();
    private:
        UIHorzList* statusBar;
        UIElem* mainContent;
        UITabList* navBar;
        PrintConsole statusConsole;
        PrintConsole mainConsole;
        PrintConsole navConsole;
};

#endif