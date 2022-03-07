// Epic Run Key
// by PepsiOtaku
// Version 1.0
// Based on DynRun source written by RPG Hacker:
//     http://www.multimediaxis.de/threads/134256-DynRPG-Das-RM2k3-Plugin-SDK?p=2951744&viewfull=1#post2951744

#define AUTO_DLLMAIN
#include <DynRPG/DynRPG.h>
#include <string.h>

std::map<std::string, std::string> configuration;

unsigned short int keyCode;
int runSpeed;
int walkSpeed;
int usedSwitch = -1;
int runThreshold;
bool confChangeCharset;

void changeFileName(int n, int thresh);

bool onStartup (char *pluginName) {
    configuration = RPG::loadConfiguration(pluginName);
    confChangeCharset = configuration["ChangeCharset"] == "true";
    return true;
}

// Comment callback
bool onComment(const char* text, const RPG::ParsedCommentData* parsedData, RPG::EventScriptLine* nextScriptLine,
		       RPG::EventScriptData* scriptData, int eventId, int pageId, int lineId, int* nextLineId)
{
    std::string cmd = parsedData->command;
    if(!cmd.compare("run_key")) {
        // store parameters to variables
        keyCode = parsedData->parameters[0].number;
        runSpeed = parsedData->parameters[1].number;
        walkSpeed = parsedData->parameters[2].number;
        usedSwitch = parsedData->parameters[3].number;
        runThreshold = parsedData->parameters[4].number;

        if (parsedData->parametersCount >= 5
            && parsedData->parameters[1].type == RPG::PARAM_NUMBER && runSpeed <= 6 && runSpeed >= 1
            && parsedData->parameters[2].type == RPG::PARAM_NUMBER && walkSpeed <= 6 && walkSpeed >= 1
            && parsedData->parameters[3].type == RPG::PARAM_NUMBER && usedSwitch >= 1
            && RPG::switches[usedSwitch])
        {
            if ((GetAsyncKeyState(keyCode) & 0x8000) == 0x8000) { // EJ Note: 65 = "A" Key
                RPG::hero->speed = runSpeed;
                if (confChangeCharset == true) changeFileName(runSpeed, runThreshold);
            } else {
                RPG::hero->speed = walkSpeed;
                if (confChangeCharset == true) changeFileName(walkSpeed, runThreshold);
            }
        }
    }
    if(!cmd.compare("run_key_off")) {
        walkSpeed = parsedData->parameters[0].number;
        if (parsedData->parametersCount >= 1
            && parsedData->parameters[0].type == RPG::PARAM_NUMBER && walkSpeed <= 6 && walkSpeed >= 1)
        {
            RPG::hero->speed = walkSpeed;
            if (confChangeCharset == true) changeFileName(walkSpeed, 7);
        }
    }
    return true;
}

void changeFileName(int n, int t)
{
    std::string rc;
    std::string file = RPG::hero->charsetFilename;
    rc = file.substr(file.size()-4, 4);
    if (n >= t) {
        if (rc.compare("-run") != 0) file = file.append("-run");
    } else {
        if (rc.compare("-run") == 0) file = file.substr(0,file.size()-4);
    }
    RPG::hero->charsetFilename = file;
}
