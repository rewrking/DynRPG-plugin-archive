#include <DynRPG/DynRPG.h>
#define NOT_MAIN_MODULE

int confMenuSwitchId;

bool onStartup (char *pluginName) {
    // DynRPG.ini
    std::map<std::string, std::string> configuration = RPG::loadConfiguration(pluginName);
    // MenuSwitch is a switch ID that will turn on when you enter the menu.
    confMenuSwitchId = atoi(configuration["MenuSwitch"].c_str());
    return true;
}


void onFrame (RPG::Scene scene) {
    if (scene == RPG::SCENE_MENU && RPG::switches[confMenuSwitchId] == false) {
        RPG::switches[confMenuSwitchId] = true;
    }

}
