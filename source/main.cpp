#include <3ds.h>
#include <stdio.h>
#include <iostream>
#include "UIInterface.h"

int main(int argc, char **argv) {
    gfxInitDefault();
    UIInterface mainUI = UIInterface(UIHorzList("Status Bar"), UIElem("Main Content", white, black), UIHorzList("Nav Bar"));

    while(aptMainLoop()) {
        gspWaitForVBlank();
        hidScanInput();

        mainUI.draw();

        if(hidKeysDown() & KEY_START)
            break;

        gfxFlushBuffers();
        gfxSwapBuffers();
    }

    gfxExit();
    return 0;
}
