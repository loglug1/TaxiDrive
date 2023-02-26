#include <3ds.h>
#include <stdio.h>
#include <iostream>
#include "UIInterface.h"

int main(int argc, char **argv) {
    gfxInitDefault();
    UIListItem item;

    UIInterface mainUI = UIInterface(new UIHorzList(), new UITabList());

    bool starshine = false;

    while(aptMainLoop()) {
        gspWaitForVBlank();
        hidScanInput();

        mainUI.draw();

        if(hidKeysDown() & KEY_A) {
            if (starshine) {
                item.highlight();
                starshine = false;
            } else {
                item.dehighlight();
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
