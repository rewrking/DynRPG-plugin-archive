#define AUTO_DLLMAIN
#include <DynRPG/DynRPG.h>
#include <sstream> // For std::stringstream

std::map<std::string, std::string> configuration;

int g_targetHero[5][4] = {
    {0, 0, 0, 0}, // 0 - Hero MP
    {0, 0, 0, 0}, // 1 - Hero Attack
    {0, 0, 0, 0}, // 2 - Hero Defense
    {0, 0, 0, 0}, // 3 - Hero Intelligence
    {0, 0, 0, 0}  // 4 - Hero Agility
};

int g_targetMonster[5][8] = {
    {0, 0, 0, 0, 0, 0, 0, 0}, // 0 - Monster MP
    {0, 0, 0, 0, 0, 0, 0, 0}, // 1 - Monster Attack
    {0, 0, 0, 0, 0, 0, 0, 0}, // 2 - Monster Defense
    {0, 0, 0, 0, 0, 0, 0, 0}, // 3 - Monster Intelligence
    {0, 0, 0, 0, 0, 0, 0, 0}, // 4 - Monster Agility
};

bool g_isInitialized = false;
bool g_recheck = false;

unsigned char confColorMpPlus;
unsigned char confColorMpMinus;
bool confShowMpPlus;
bool confShowMpMinus;
bool confMonMpPlus;
bool confMonMpMinus;
bool confStatsPlus;
bool confStatsMinus;
std::string confAbbrAtk;
std::string confAbbrDef;
std::string confAbbrInt;
std::string confAbbrAgl;

//std::stringstream popupText;

unsigned char frameTimer = 0;

bool onStartup (char *pluginName) {
    // Get configuration settings
    configuration = RPG::loadConfiguration(pluginName);
    confColorMpPlus = atoi(configuration["ColorMpPlus"].c_str()); // Convert String to Int
    confColorMpMinus = atoi(configuration["ColorMpMinus"].c_str());
    confShowMpPlus = configuration["ShowMpPlus"] == "true";
    confShowMpMinus = configuration["ShowMpMinus"] == "true";
    confMonMpPlus = configuration["MonMpPlus"] == "true";
    confMonMpMinus = configuration["MonMpMinus"] == "true";
    confStatsPlus = configuration["StatsPlus"] == "true";
    confStatsMinus = configuration["StatsMinus"] == "true";
    confAbbrAtk = configuration["AbbrAtk"];
    confAbbrDef = configuration["AbbrDef"];
    confAbbrInt = configuration["AbbrInt"];
    confAbbrAgl = configuration["AbbrAgl"];
    return true;
}

bool __cdecl onDoBattlerAction (RPG::Battler *battler){
    if (g_isInitialized ==  false) {
        int i;
        for (i=0; i<8; i++){
            if (RPG::Actor::partyMember(i) != NULL && i<4) {
                g_targetHero[0][i] = RPG::Actor::partyMember(i)->mp;
                g_targetHero[1][i] = RPG::Actor::partyMember(i)->getAttack();
                g_targetHero[2][i] = RPG::Actor::partyMember(i)->getDefense();
                g_targetHero[3][i] = RPG::Actor::partyMember(i)->getIntelligence();
                g_targetHero[4][i] = RPG::Actor::partyMember(i)->getAgility();
            }
            if (RPG::monsters[i] != NULL) {
                g_targetMonster[0][i] = RPG::monsters[i]->mp;
                g_targetMonster[1][i] = RPG::monsters[i]->getAttack();
                g_targetMonster[2][i] = RPG::monsters[i]->getDefense();
                g_targetMonster[3][i] = RPG::monsters[i]->getIntelligence();
                g_targetMonster[4][i] = RPG::monsters[i]->getAgility();

            }
        }
        g_isInitialized = true;
    }
    return true;
}

void statPopup ( int stat, int popupTimer, bool isMonster, int statId, int id, int colorPlus, int colorMinus, bool settingPlus, bool settingMinus, std::string statAbbr) {
    int battlerStat = 0;
    int battlerValue;
    std::stringstream popupText;
    isMonster == true ? battlerValue = g_targetMonster[statId][id] : battlerValue = g_targetHero[statId][id];
    if (stat > battlerValue && settingPlus == true) {
        battlerStat = stat - battlerValue;
        //if (popupTimer == 0) {
            if (statId == 0) {
                isMonster == true ? RPG::monsters[id]->damagePopup(battlerStat, colorPlus)
                : RPG::Actor::partyMember(id)->damagePopup(battlerStat, colorPlus);
            } else {
                popupText << "+" << battlerStat << " " << statAbbr;
                isMonster == true ? RPG::monsters[id]->damagePopup(popupText.str())
                : RPG::Actor::partyMember(id)->damagePopup(popupText.str());
            }
        //} else g_recheck = true;
    } else if (stat < battlerValue && settingMinus == true) {
        battlerStat = battlerValue - stat;
        //if (popupTimer == 0) {
            if (statId == 0) {
                isMonster == true ? RPG::monsters[id]->damagePopup(battlerStat, colorMinus)
                : RPG::Actor::partyMember(id)->damagePopup(battlerStat, colorMinus);
            } else {
                popupText << "-" << battlerStat << " " << statAbbr;
                isMonster == true ? RPG::monsters[id]->damagePopup(popupText.str())
                : RPG::Actor::partyMember(id)->damagePopup(popupText.str());
            }
        //} else g_recheck = true;
    }
    if (g_recheck == false) isMonster == true ? g_targetMonster[statId][id] = stat : g_targetHero[statId][id] = stat;
    g_recheck = false;
}

void onFrame (RPG::Scene scene){
    if (scene == RPG::SCENE_BATTLE && g_isInitialized ==  true) {
        frameTimer++;
        if (frameTimer > 20) {
            frameTimer = 0;
            int i;
            for (i=0; i<8; i++){
                if (RPG::Actor::partyMember(i) != NULL && i<4) {
                    statPopup(RPG::Actor::partyMember(i)->mp, RPG::Actor::partyMember(i)->damagePopupTimer, false, 0, i, confColorMpPlus, confColorMpMinus, confShowMpPlus, confShowMpMinus, "");
                    statPopup(RPG::Actor::partyMember(i)->getAttack(), RPG::Actor::partyMember(i)->damagePopupTimer, false, 1, i, 0, 0, confStatsPlus, confStatsMinus, confAbbrAtk);
                    statPopup(RPG::Actor::partyMember(i)->getDefense(), RPG::Actor::partyMember(i)->damagePopupTimer, false, 2,  i, 0, 0, confStatsPlus, confStatsMinus, confAbbrDef);
                    statPopup(RPG::Actor::partyMember(i)->getIntelligence(), RPG::Actor::partyMember(i)->damagePopupTimer, false, 3,  i, 0, 0, confStatsPlus, confStatsMinus, confAbbrInt);
                    statPopup(RPG::Actor::partyMember(i)->getAgility(), RPG::Actor::partyMember(i)->damagePopupTimer, false, 4,  i, 0, 0, confStatsPlus, confStatsMinus, confAbbrAgl);
                }
                if (RPG::monsters[i] != NULL) {
                    statPopup(RPG::monsters[i]->mp, RPG::monsters[i]->damagePopupTimer, true, 0, i, confColorMpPlus, confColorMpMinus, confMonMpPlus, confMonMpMinus, "");
                    statPopup(RPG::monsters[i]->getAttack(), RPG::monsters[i]->damagePopupTimer, true, 1, i, 0, 0, confStatsPlus, confStatsMinus, confAbbrAtk);
                    statPopup(RPG::monsters[i]->getDefense(), RPG::monsters[i]->damagePopupTimer, true, 2, i, 0, 0, confStatsPlus, confStatsMinus, confAbbrDef);
                    statPopup(RPG::monsters[i]->getIntelligence(), RPG::monsters[i]->damagePopupTimer, true, 3, i, 0, 0, confStatsPlus, confStatsMinus, confAbbrInt);
                    statPopup(RPG::monsters[i]->getAgility(), RPG::monsters[i]->damagePopupTimer, true, 4, i, 0, 0, confStatsPlus, confStatsMinus, confAbbrAgl);
                }
            }
        }
    } else if (g_isInitialized == true) g_isInitialized =  false;
}


