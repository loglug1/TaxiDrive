#include <3ds.h>
#include <stdio.h>
#include <iostream>
#include "UIInterface.h"

int main(int argc, char **argv) {
    gfxInitDefault();
    
    PrintConsole errConsole;
    consoleInit(GFX_BOTTOM, &errConsole);
    consoleSelect(&errConsole);
    std::cout << "Debug Console:" << std::endl;

    //ui setup
    UIElem page1("Page 1", white, black);
    UIElem page2("Page 2", white, black);
    UIElem page3("Page 3", white, black);

    UITab tab1(&page1, "1");
    UITab tab2(&page2, "2");
    UITab tab3(&page3, "3");

    UIHorzList<UITab> navTabs(blue);
    navTabs.append(tab1);
    navTabs.append(tab2);
    navTabs.append(tab3);

    UIListItem stat1("StatusBar", blue, white);

    UIHorzList<UIListItem> statusBar(blue, white);
    statusBar.append(stat1);

    
    //testing:
    std::cout << page1 << std::endl;
    std::cout << page2 << std::endl;
    std::cout << page3 << std::endl;
    std::cout << tab1 << std::endl;
    std::cout << tab2 << std::endl;
    std::cout << tab3 << std::endl;
    std::cout << stat1 << std::endl;

    UIInterface mainUI = UIInterface(&statusBar, &navTabs);

    while(aptMainLoop()) {
        gspWaitForVBlank();
        hidScanInput();

        mainUI.draw();

        if (hidKeysDown() & KEY_DLEFT)
            mainUI.menuLeft();
        if (hidKeysDown() & KEY_DRIGHT)
            mainUI.menuRight();
        if (hidKeysDown() & KEY_DDOWN)
            mainUI.menuDown();
        if (hidKeysDown() & KEY_DUP)
            mainUI.menuUp();
        

        if(hidKeysUp() & KEY_START)
            break;

        gfxFlushBuffers();
        gfxSwapBuffers();
    }

    gfxExit();
    return 0;
}
