#include "UIInterface.h"
#include <3ds.h>
#include <iostream>

UIInterface::UIInterface(UIHorzList* statusBar, UITabList* navBar) {
    consoleInit(GFX_TOP, &statusConsole);
    consoleInit(GFX_TOP, &mainConsole);
    consoleInit(GFX_TOP, &navConsole);

    consoleSetWindow(&statusConsole, 1, 1, 50, 1);
	consoleSetWindow(&mainConsole, 1, 2, 50, 28);
    consoleSetWindow(&navConsole, 1, 29, 50, 1);

    this->statusBar = statusBar;
    this->mainContent = nullptr;
    this->navBar = navBar;
}

void UIInterface::menuDown() const {

}
void UIInterface::menuUp() const {
    
}
void UIInterface::menuRight() const {
    navBar->nextItem();
}
void UIInterface::menuLeft() const {
    navBar->prevItem();
}
void UIInterface::draw() {
    consoleSelect(&statusConsole);
    consoleClear();
    std::cout << *statusBar;


    mainContent = navBar->getSelected()->getContent();
    if (mainContent != nullptr) {
        consoleSelect(&mainConsole);
        consoleClear();
        std::cout << *mainContent;
    }

    consoleSelect(&navConsole);
    consoleClear();
    std::cout << *navBar;
}