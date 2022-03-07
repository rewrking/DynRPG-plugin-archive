// CMS Tools: Quit Switch
// by PepsiOtaku
// Version 2.0

#define AUTO_DLLMAIN
#include <DynRPG/DynRPG.h>

int quitSwitchValue;

bool onStartup(char *pluginName) {
    // Load configuration on startup
    std::map<std::string, std::string> configuration = RPG::loadConfiguration(pluginName);
    quitSwitchValue = atoi(configuration["QuitSwitch"].c_str()); // atoi is the easiest way here to get an integer
    static int patch[] = {
        0x4CDC1CA1, 0xC6008B00, 0x90010C40, 0x4CDC7CA1, 0xBA008B00,
        quitSwitchValue, // Switch ID
        0x04C701B1, 0x4A274024, 0xB33C6800, 0x90C30048
    };

    memcpy(reinterpret_cast<void *>(0x4A2328), patch, sizeof(patch));
    return true;
}

