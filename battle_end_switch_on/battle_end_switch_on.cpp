#include <DynRPG/DynRPG.h>

int confBattleEndSwitchId;

bool onStartup (char *pluginName) {
    // DynRPG.ini
    std::map<std::string, std::string> configuration = RPG::loadConfiguration(pluginName);
    // MenuSwitch is a switch ID that will turn on when you enter the menu.
    confBattleEndSwitchId = atoi(configuration["BattleEndSwitch"].c_str());
    return true;
}


void onFrame (RPG::Scene scene) {
    if (scene == RPG::SCENE_BATTLE) {
        if (RPG::battleData->battlePhase == RPG::BPHASE_VICTORY && RPG::switches[confBattleEndSwitchId] == false) {
            RPG::switches[confBattleEndSwitchId] = true;
        }
    }
}
