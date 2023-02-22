#include <3ds.h>
#include <stdio.h>
#include <iostream>
#include "UIInterface.h"

int main(int argc, char **argv) {
    gfxInitDefault();
    UIListItem statusBar[1];
    statusBar[0] = UIListItem("StatusBarItem");
    UIListItem navBar[1];
    navBar[0] = UIListItem("NavBarItem");
    UIListItem mainList[1];
    mainList[0] = UIListItem("Main Content", blue, white);

    UIElem worldScreen("Hello World!", white, black);
    UIElem starshineScreen("Good morning starshine, the Earth says hello!", green, red);
    UIElem main = worldScreen;

    UIInterface mainUI = UIInterface(new UIHorzList(1, statusBar), &main, new UIHorzList(1, navBar));

    bool starshine = false;

    while(aptMainLoop()) {
        gspWaitForVBlank();
        hidScanInput();

        mainUI.draw();

        if(hidKeysDown() & KEY_A) {
            if (starshine) {
                main = worldScreen;
                starshine = false;
            } else {
                main = starshineScreen;
                starshine = true;
            }
        }

        if(hidKeysUp() & KEY_START)
            break;

        gfxFlushBuffers();
        gfxSwapBuffers();
    }

    gfxExit();
    return 0;
}
