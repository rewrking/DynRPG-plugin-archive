#define AUTO_DLLMAIN
#include <DynRPG/DynRPG.h>
#include <sstream> // For std::stringstream

std::map<std::string, std::string> configuration;

unsigned short int defaultSettings[4] = {0, 0, 0, 0};
unsigned short int confSys2Trigger;
unsigned short int confBattleLayout;
unsigned short int confLargeWindow;
unsigned short int confTransparency;

bool onStartup (char *pluginName) {
    // Get configuration settings for key variables
    configuration = RPG::loadConfiguration(pluginName);
    confSys2Trigger = atoi(configuration["Sys2TriggerVar"].c_str());
    confBattleLayout = atoi(configuration["BattleLayoutVar"].c_str());
    confLargeWindow = atoi(configuration["LargeWindowSwitch"].c_str());
    confTransparency = atoi(configuration["TransparencySwitch"].c_str());
    return true;
}

void onInitFinished() {
    // check defaults and store them
    if (RPG::battleSettings->layout == RPG::BL_TRADITIONAL) defaultSettings[1] = 1;
    if (RPG::battleSettings->layout == RPG::BL_ALTERNATIVE) defaultSettings[1] = 2;
    if (RPG::battleSettings->layout == RPG::BL_GAUGE) defaultSettings[1] = 3;
    if (RPG::battleSettings->largeWindows == true) defaultSettings[2] = 0; else defaultSettings[2] = 1;
    if (RPG::battleSettings->transparentWindows == true) defaultSettings[3] = 1; else defaultSettings[3] = 0;
}

void onLoadGame (int id, char* data, int length) {
    // load stored settings, or defaults
    std::stringstream strSys2Image;
    if (RPG::variables[confSys2Trigger] > 0) {
        strSys2Image << "Sys2Image" << RPG::variables[confSys2Trigger];
    }  else {strSys2Image << "Sys2Default";}
    RPG::system->systemGraphic->system2Image->loadFromFile(configuration[strSys2Image.str()], false);
    if (RPG::variables[confBattleLayout] == 0) {
        if (defaultSettings[1] == 1) RPG::battleSettings->layout = RPG::BL_TRADITIONAL;
        if (defaultSettings[1] == 2) RPG::battleSettings->layout = RPG::BL_ALTERNATIVE;
        if (defaultSettings[1] == 3) RPG::battleSettings->layout = RPG::BL_GAUGE;
    }
    if (RPG::variables[confBattleLayout] == 1) RPG::battleSettings->layout = RPG::BL_TRADITIONAL;
    if (RPG::variables[confBattleLayout] == 2) RPG::battleSettings->layout = RPG::BL_ALTERNATIVE;
    if (RPG::variables[confBattleLayout] == 3) RPG::battleSettings->layout = RPG::BL_GAUGE;

    if (RPG::switches[confLargeWindow] == true || defaultSettings[2] == 1) RPG::battleSettings->largeWindows = false; else RPG::battleSettings->largeWindows = true;
    if (RPG::switches[confTransparency] == true || defaultSettings[3] == 1) RPG::battleSettings->transparentWindows = true; else RPG::battleSettings->transparentWindows = false;
}

bool onSetVariable (int id, int value) {
    std::stringstream strSys2Image;
    if (id == confSys2Trigger){
        if (value > 0){
            strSys2Image << "Sys2Image" << value;
        } else {strSys2Image << "Sys2Default";}
        RPG::system->systemGraphic->system2Image->loadFromFile(configuration[strSys2Image.str()], false);
    }
    if (id == confBattleLayout){
        if (value == 1) RPG::battleSettings->layout = RPG::BL_TRADITIONAL;
        if (value == 2) RPG::battleSettings->layout = RPG::BL_ALTERNATIVE;
        if (value == 3) RPG::battleSettings->layout = RPG::BL_GAUGE;
    }
    return true;
}

bool onSetSwitch(int id, bool value) {
    if (id == confLargeWindow){
        if (value == true) RPG::battleSettings->largeWindows = false;
        else RPG::battleSettings->largeWindows = true;

    }
    if (id == confTransparency){
        if (value == true) RPG::battleSettings->transparentWindows = true;
        else RPG::battleSettings->transparentWindows = false;

    }
    return true;
}
