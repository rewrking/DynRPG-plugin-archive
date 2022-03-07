// CMS Tools: Menu Transition Tweaks
// by PepsiOtaku
// Version 2.0

#define AUTO_DLLMAIN
#include <DynRPG/DynRPG.h>

bool onStartup(char *pluginName) {
    // I don't remember what the hell this does. It's either for the menu > custom menu fade
    // or something do to with saving? Should have commented this earlier
    static unsigned char patchSave1[] = {0x50, 0x8B, 0x35, 0x1C, 0xDC, 0x4C};
    static unsigned char patchSave2[] = {0x58, 0x8B, 0x36, 0xC6, 0x46, 0x0C, 0x01};
    memcpy(reinterpret_cast<void *>(0x4A25E9), patchSave1, sizeof(patchSave1));
    memcpy(reinterpret_cast<void *>(0x4A25F7), patchSave2, sizeof(patchSave2));
    return true;

}

