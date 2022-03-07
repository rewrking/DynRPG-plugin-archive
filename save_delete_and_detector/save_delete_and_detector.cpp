// CMS Tools: Save Detector & Delete Save function
// by PepsiOtaku
// Version 2.0

#define AUTO_DLLMAIN
#include <DynRPG/DynRPG.h>
#include <sstream> // For std::stringstream

std::map<std::string, std::string> configuration;

int confDetectSwitch;
int confCheckSwitch;
int confDeleteSaveVar;


bool onStartup(char *pluginName) {
    // Store configuration
    //std::map<std::string, std::string> configuration;
    // Load configuration on startup
    configuration = RPG::loadConfiguration(pluginName);
    confDetectSwitch = atoi(configuration["SaveDetectorSwitch"].c_str()); // atoi is the easiest way here to get an integer
    confCheckSwitch = atoi(configuration["SaveDetectorCheckSwitch"].c_str());
    confDeleteSaveVar = atoi(configuration["DeleteSaveVar"].c_str());
    return true;
}

// detect saves on startup & turn a switch on if they are detected
void onNewGame () {
    // FindFirstFile function load
    WIN32_FIND_DATA lpFindFileData;
    HANDLE hFind;
    // Find saves that begin with "save," and end with ".lsd" with any numeric value inbetween
    hFind = FindFirstFile("Save??.lsd", &lpFindFileData);
    if(hFind != INVALID_HANDLE_VALUE) {
        // default switch value = 4005
        RPG::switches[confDetectSwitch] = true;
        FindClose(hFind);
    } else {
        RPG::switches[confDetectSwitch] = false;
    }
}

// turn a switch on to check for saves at a specific time
// usage example: refresh the title screen after all saves have been deleted
bool onSetSwitch(int id, bool value){
    if (id == confCheckSwitch){ // 4009
        if (value == true){
            WIN32_FIND_DATA lpFindFileData;
            HANDLE hFind;
            // Find saves that begin with "save," and end with ".lsd" with any numeric value inbetween
            hFind = FindFirstFile("save??.lsd", &lpFindFileData);
            if(hFind != INVALID_HANDLE_VALUE) {
                // default switch value = 4005
                RPG::switches[confDetectSwitch] = true;
                FindClose(hFind);
            } else {
                RPG::switches[confDetectSwitch] = false;
            }
        }
    }
    return true;
}

// delete save file after setting a variable to the save id
bool onSetVariable (int id, int value){
    if (id == confDeleteSaveVar){ //4002
        if (value > 0) {
            // make some strings for the save id that has been set
            std::stringstream deleteFileNameLsd;
            std::stringstream deleteFileNameDyn;
            std::string deleteFileNameLsdString;
            std::string deleteFileNameDynString;
            if (value < 10) {
                deleteFileNameLsd << "Save0" << value << ".lsd";
                deleteFileNameDyn << "Save0" << value << ".dyn";
            } else {
                deleteFileNameLsd << "Save" << value << ".lsd";
                deleteFileNameDyn << "Save" << value << ".dyn";
            }
            deleteFileNameLsdString = deleteFileNameLsd.str();
            deleteFileNameDynString = deleteFileNameDyn.str();
            DeleteFile(deleteFileNameLsdString.c_str());
            DeleteFile(deleteFileNameDynString.c_str());
            // detect and delete those saves
            WIN32_FIND_DATA lpFindFileData;
            HANDLE hFind;
            // Find saves that begin with "save," and end with ".lsd" with any numeric value inbetween
            hFind = FindFirstFile("save??.lsd", &lpFindFileData);
            if(hFind != INVALID_HANDLE_VALUE) {
                // default switch value = 4005
                RPG::switches[confDetectSwitch] = true;
                FindClose(hFind);
            } else {
                RPG::switches[confDetectSwitch] = false;
            }
        }
    }
    return true;
}
