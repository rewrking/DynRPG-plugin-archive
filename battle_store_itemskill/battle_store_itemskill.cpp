// Store Item & Skill ID in Battle
// by PepsiOtaku
// Version 1.1

#include <DynRPG/DynRPG.h>
#define NOT_MAIN_MODULE
#include <string>

std::map<std::string, std::string> configuration;

int confSkillIdSwitch;
int confSkillIdVar;
int confMonsterSkillIdSwitch;
int confMonsterSkillIdVar;

int confItemIdSwitch;
int confItemIdVar;

int confConSwitch;
int confMonConSwitch;
int confConIdStartVar;

bool onStartup (char *pluginName) {
    // Get configuration settings
    configuration = RPG::loadConfiguration(pluginName);
    // Skill ID stuff (heroes & monsters)
    confSkillIdSwitch = atoi(configuration["SkillIdSwitch"].c_str()); // Convert String to Int
    confSkillIdVar = atoi(configuration["SkillIdVar"].c_str());
    confMonsterSkillIdSwitch = atoi(configuration["MonSkillIdSwitch"].c_str()); // Convert String to Int
    confMonsterSkillIdVar = atoi(configuration["MonSkillIdVar"].c_str());
    // Item ID stuff (just heroes)
    confItemIdSwitch = atoi(configuration["ItemIdSwitch"].c_str()); // Convert String to Int
    confItemIdVar = atoi(configuration["ItemIdVar"].c_str());
    // Condition ID stuff (heroes & monsters, requires 12 switches)
    confConSwitch = atoi(configuration["ConditionSwitch"].c_str()); // Convert String to Int
    confMonConSwitch = atoi(configuration["MonConditionSwitch"].c_str()); // Convert String to Int
    confConIdStartVar = atoi(configuration["ConditionIdStartVar"].c_str()); // Convert String to Int
    //confConditionStartSwitch = atoi(configuration["ConditionStartSwitch"].c_str()); // Convert String to Int
    //confConditionPointerSwitch = atoi(configuration["ConditionPointerSwitch"].c_str()); // Convert String to Int
    return true;
}

bool onDoBattlerAction(RPG::Battler *battler, bool firstTry){
    // Skills
    if (firstTry == true) {
        if (battler->action->kind == RPG::AK_SKILL && battler->isMonster() == false) {
            RPG::variables[confSkillIdVar] = battler->action->skillId;
            RPG::switches[confSkillIdSwitch] = true;
        } else {
            //RPG::switches[confSkillIdSwitch] = false;
        }
        if (battler->action->kind == RPG::AK_SKILL && battler->isMonster() == true) {
            RPG::variables[confMonsterSkillIdVar] = battler->action->skillId;
            RPG::switches[confMonsterSkillIdSwitch] = true;
        } else {
            //RPG::switches[confMonsterSkillIdSwitch] = false;
        }
        // Items
        if (battler->action->kind == RPG::AK_ITEM) { // monsters can't use items, so the differentiation isn't needed
            RPG::variables[confItemIdVar] = battler->action->itemId;
            RPG::switches[confItemIdSwitch] = true;
        } else {
            //RPG::switches[confItemIdSwitch] = false;
        }

    }
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
    if(!cmd.compare("check_condition") && parsedData->parametersCount == 1 && parsedData->parameters[0].type == RPG::PARAM_NUMBER)
    {
        // parameter 1 = condition ID to check for
        int c; // condition id
        c = parsedData->parameters[0].number;
        for (int i=0; i<8; i++){
            if (i<4){
                if (RPG::Actor::partyMember(i) != NULL  &&  RPG::Actor::partyMember(i)->conditions[c] != 0) {
                    RPG::switches[confConSwitch] = true;
                    RPG::variables[confConIdStartVar+i] = c;
                } else RPG::variables[confConIdStartVar+i] = 0;
            }
            if (RPG::monsters[i] != NULL && RPG::monsters[i]->conditions[c] != 0) {
                RPG::switches[confMonConSwitch] = true;
                RPG::variables[confConIdStartVar+4+i] = c;
            } else RPG::variables[confConIdStartVar+4+i] = 0;
        }

    }
    return true;
}
