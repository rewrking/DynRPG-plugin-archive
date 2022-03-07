// CMS Tools: Order Switch
// by PepsiOtaku
// Version 2.0

#define AUTO_DLLMAIN
#include <DynRPG/DynRPG.h>

int OrderSwitchValue;

bool onStartup(char *pluginName) {
    // Load configuration on startup
    std::map<std::string, std::string> configuration = RPG::loadConfiguration(pluginName);
    OrderSwitchValue = atoi(configuration["OrderSwitch"].c_str()); // atoi is the easiest way here to get an integer

    // The following makes "Order" always selectable (thanks Cherry)
    *reinterpret_cast<unsigned char *>(0x4A265A) = 0xEB;
    *reinterpret_cast<unsigned char *>(0x4A0D64) = 0xEB;

    // The following turns on "OrderSwitch" when the "Order" menu option is selected
    //  (double thanks Cherry)
    static int patch2[] = {
        0x4CDC1CA1, 0xC6008B00, 0x90010C40, 0x4CDC7CA1, 0xBA008B00,
        OrderSwitchValue, // Switch ID
        0x04C701B1, 0x4A274024, 0xB33C6800, 0x90C30048
    };
    // apply the patch created above
    memcpy(reinterpret_cast<void *>(0x4A23BC), patch2, sizeof(patch2));

    return true;
}


