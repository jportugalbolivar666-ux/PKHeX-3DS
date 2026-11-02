#include <3ds.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    gfxInitDefault();
    consoleInit(GFX_TOP, NULL);

    printf("PKHeX Expanded - Gen 7\n");
    printf("----------------------\n\n");
    printf("Version experimental para Nintendo 3DS\n\n");
    printf("Proyecto de adaptacion para Android/Citra\n\n");
    printf("Menu principal en desarrollo...\n");

    while (aptMainLoop())
    {
        hidScanInput();

        u32 kDown = hidKeysDown();

        if (kDown & KEY_START)
            break;

        gfxFlushBuffers();
        gfxSwapBuffers();
        gspWaitForVBlank();
    }

    gfxExit();
    return 0;
}
