// CMS Tools: Hero Rename
// Version 1.0
// By PepsiOtaku

#include <DynRPG/DynRPG.h>
#define NOT_MAIN_MODULE
#include <sstream>

std::stringstream storedName;
int heroNameId=1;
bool changeName;

bool onComment(const char* text, const RPG::ParsedCommentData* parsedData, RPG::EventScriptLine* nextScriptLine,
		       RPG::EventScriptData* scriptData, int eventId, int pageId, int lineId, int* nextLineId)
{
    std::string cmd = parsedData->command;
    if(!cmd.compare("vars_to_name") && parsedData->parametersCount == 2) {
        storedName.str(std::string());
        heroNameId = parsedData->parameters[0].number;
        int v = parsedData->parameters[1].number;
        for (int i=0; RPG::variables[v+i]!=0; i++) {
            storedName << (char) RPG::variables[v+i];
            if (RPG::variables[v+i] == 36) // $ needs to be entered twice since it's used for symbols
                storedName << (char) RPG::variables[v+i];
        }
        changeName = true;

    }

    if(!cmd.compare("dbname_to_vars") && parsedData->parametersCount == 2) {
        char dbName[12];
        strcpy(dbName, RPG::dbActors[parsedData->parameters[0].number]->name);
        for (int i=0; dbName[i]!=0; i++) {
            if (dbName[i]) RPG::variables[parsedData->parameters[1].number+i] = dbName[i];
        }
    }
    return true;
}

bool onEventCommand(RPG::EventScriptLine* scriptLine, RPG::EventScriptData* scriptData, int eventId, int pageId,
                    int lineId, int* nextLineId)
{
    if (scriptLine->command == RPG::EVCMD_CHANGE_HERO_NAME && scriptLine->stringParameter == "@dyn") {
        if (changeName == true) {
            scriptLine->parameters[0] = heroNameId;
            scriptLine->stringParameter = storedName.str();
            changeName = false;
        } else {
            // This bit of code ensures the name does not become "@dyn" if changeName is false at the time this event command is called
            std::stringstream temp;
            temp << RPG::dbActors[scriptLine->parameters[0]]->name;
            scriptLine->stringParameter = temp.str();
        }
    }
    return true;
}
