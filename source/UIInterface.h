#ifndef UI_INTERFACE_H
#define UI_INTERFACE_H

#include <3ds.h>
#include "UIElem.h"

class UIInterface {
    public:
        UIInterface(
            UIHorzList statusBar = UIHorzList(),
            UIElem mainContent = UIElem(),
            UIHorzList navBar = UIHorzList()
            );
        void menuDown();
        void menuUp();
        void menuRight();
        void menuLeft();
        void draw();
    private:
        UIHorzList statusBar;
        UIElem mainContent;
        UIHorzList navBar;
        PrintConsole statusConsole;
        PrintConsole mainConsole;
        PrintConsole navConsole;
};

#endif