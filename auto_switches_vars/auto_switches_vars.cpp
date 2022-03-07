// Auto Switches
// by PepsiOtaku
// Version 2.0

#include <DynRPG/DynRPG.h>
//#include <sstream> // For std::stringstream
#include <vector>

std::map<std::string, std::string> configuration;

unsigned short int confMasterSwitch; // 4041

// structure to hold event heirarchy
struct aswitch {
  int mapId;    // map
  int eventId;  // event
  int pageId;   // page
};
typedef std::vector<aswitch*> aswitchList; // vector of aswitch structures
aswitchList aswitches;                     // declare it


bool onStartup (char *pluginName) {
    configuration = RPG::loadConfiguration(pluginName);
    confMasterSwitch = atoi(configuration["MasterSwitch"].c_str());
    return true;
}

bool onComment ( const char* text,
                 const RPG::ParsedCommentData* parsedData,
                 RPG::EventScriptLine* nextScriptLine,
                 RPG::EventScriptData* scriptData,
                 int eventId,
                 int pageId,
                 int lineId,
                 int* nextLineId )
{
    std::string cmd = parsedData->command;
    if(!cmd.compare("export_event_state"))
    {
        bool foundEvent = false;
        int vectId = 0;
        for (unsigned int i=0; i<aswitches.size(); i++) {   // loop through existing events in vector
            if (aswitches[i]->mapId == RPG::hero->mapId) {  // if matching map found
                if (aswitches[i]->eventId == eventId) {     // if matching event found
                    if (aswitches[i]->pageId == pageId) {   // if matching event page found...
                        foundEvent=true;                    // ding ding ding! It already exists! do nothing!
                        vectId = i;
                        break;
                    }
                }
            }
        }
        if (foundEvent == false) {
            aswitch* newSwitch = new aswitch;               // create temporary aswitch structure
            newSwitch->mapId = RPG::hero->mapId;            // add the map ID,
            newSwitch->eventId = eventId;                   // event ID,
            newSwitch->pageId = pageId;                     // and event page
            aswitches.push_back(newSwitch);                 // add it to the vector
        } else {                                            // foundEvent = true
            // if parameter 1 is set to "0" it will reset that event page.
            if (parsedData->parametersCount == 1 && parsedData->parameters[0].number == 0) {
                aswitches.erase(aswitches.begin()+vectId);
            }
        }
        return false;
    }

    if(!cmd.compare("import_event_state"))
    {
        RPG::switches[confMasterSwitch] = false;            // set the master switch to OFF
        for (unsigned int i=0; i<aswitches.size(); i++) {   // loop through existing events in vector
            if (aswitches[i]->mapId == RPG::hero->mapId) {  // if matching map found
                if (aswitches[i]->eventId == eventId) {     // if matching event found
                    if (aswitches[i]->pageId == pageId) {   // if matching event page found...
                        // set the master switch to ON since the event exists in the vector
                        RPG::switches[confMasterSwitch] = true;

                    }
                }
            }
        }
        return false;
    }

    /*if(!cmd.compare("save_var"))
    {

        return false;
    }

    if(!cmd.compare("load_var"))
    {
        return false;
    }*/
    return true;
}

void onInitTitleScreen() {
    aswitches.clear();
}

void onNewGame () {
    aswitches.clear();
}

void onSaveGame( int id, void __cdecl(*savePluginData) (char* data, int length)) {
    int dataArray[aswitches.size()*3] ;
    for (unsigned int i=0; i<aswitches.size(); i++) {
        dataArray[i*3] = aswitches[i]->mapId;
        dataArray[i*3+1] = aswitches[i]->eventId;
        dataArray[i*3+2] = aswitches[i]->pageId;
    }
    savePluginData((char *)dataArray, sizeof(dataArray));
}

void onLoadGame (int id, char* data, int length) {
    aswitches.clear();
    int *dataArray = (int *)data;
    // sick loop that gets the data back and places each one into the aswitches vector in the correct order
    for (int i=0; i<length/4; i=i+3) {
        aswitch* newSwitch = new aswitch;
        newSwitch->mapId = dataArray[i];
        newSwitch->eventId = dataArray[i+1];
        newSwitch->pageId = dataArray[i+2];
        aswitches.push_back(newSwitch);
    }
}

void onExit () {
    aswitches.clear();
}


