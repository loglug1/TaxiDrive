#include "UIInterface.h"
#include <3ds.h>
#include <iostream>

UIInterface::UIInterface(UIHorzList* statusBar, UIElem* mainContent, UIHorzList* navBar) {
    consoleInit(GFX_TOP, &statusConsole);
    consoleInit(GFX_TOP, &mainConsole);
    consoleInit(GFX_TOP, &navConsole);

    consoleSetWindow(&statusConsole, 1, 1, 50, 2);
	consoleSetWindow(&mainConsole, 1, 3, 50, 26);
    consoleSetWindow(&navConsole, 1, 28, 50, 2);

    this->statusBar = statusBar;
    this->mainContent = mainContent;
    this->navBar = navBar;
}

void UIInterface::menuDown() {

}
void UIInterface::menuUp() {
    
}
void UIInterface::menuRight() {
    
}
void UIInterface::menuLeft() {
    
}
void UIInterface::draw() {
    consoleSelect(&statusConsole);
    consoleClear();
    std::cout << *statusBar;

    consoleSelect(&mainConsole);
    consoleClear();
    std::cout << *mainContent;
    

    consoleSelect(&navConsole);
    consoleClear();
    std::cout << *navBar;
}