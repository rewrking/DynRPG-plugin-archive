// System/Custom Sound & Music Player
// by PepsiOtaku
// Version .0

#define AUTO_DLLMAIN
#include <DynRPG/DynRPG.h>
#include <stdio.h>
#include <fstream>
#include <string.h>

using namespace std;

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

    if(!cmd.compare("se_cursor")) {
        RPG::system->getCursorSE()->play();
    }

    if(!cmd.compare("se_decision") || !cmd.compare("se_choice")) {
        RPG::system->getDecisionSE()->play();
    }

    if(!cmd.compare("se_cancel")) {
        RPG::system->getCancelSE()->play();
    }

    if(!cmd.compare("se_buzzer")) {
        RPG::system->getBuzzerSE()->play();
    }

    if(!cmd.compare("se_battle_start")) {
        RPG::system->getBattleStartSE()->play();
    }

    if(!cmd.compare("se_flee")) {
        RPG::system->getFleeSE()->play();
    }

    if(!cmd.compare("se_enemy_attack")) {
        RPG::system->getEnemyAttackSE()->play();
    }

    if(!cmd.compare("se_enemy_damage")) {
        RPG::system->getEnemyDamageSE()->play();
    }

    if(!cmd.compare("se_hero_damage")) {
        RPG::system->getHeroDamageSE()->play();
    }

    if(!cmd.compare("se_evasion")) {
        RPG::system->getEvasionSE()->play();
    }

    if(!cmd.compare("se_enemy_death")) {
        RPG::system->getEnemyDeathSE()->play();
    }

    if(!cmd.compare("se_item_used")) {
        RPG::system->getItemSE()->play();
    }

    if(!cmd.compare("bgm_title")) {
        RPG::system->getTitleBGM()->play();
    }

    if(!cmd.compare("bgm_battle")) {
        RPG::system->getBattleBGM()->play();
    }

    if(!cmd.compare("bgm_victory")) {
        RPG::system->getVictoryBGM()->play();
    }

    if(!cmd.compare("bgm_inn")) {
        RPG::system->getInnBGM()->play();
    }

    if(!cmd.compare("bgm_skiff")) {
        RPG::system->getSkiffBGM()->play();
    }

    if(!cmd.compare("bgm_ship")) {
        RPG::system->getShipBGM()->play();
    }

    if(!cmd.compare("bgm_airship")) {
        RPG::system->getAirshipBGM()->play();
    }

    if(!cmd.compare("bgm_game_over")) {
        RPG::system->getGameOverBGM()->play();
    }

    if(!cmd.compare("se_custom")) {
        char IniValue[256];
        int volume;
        int tempo;
        int balance;
        GetPrivateProfileString("se_custom", parsedData->parameters[0].text , RPG::system->getBuzzerSE()->filename, IniValue, 256, ".\\DynRPG.ini");
        if (parsedData->parametersCount >= 2 && parsedData->parameters[1].type == RPG::PARAM_NUMBER)
            volume = parsedData->parameters[1].number;
        else volume = 100;
        if (parsedData->parametersCount >= 3 && parsedData->parameters[2].type == RPG::PARAM_NUMBER)
            tempo = parsedData->parameters[2].number;
        else tempo = 100;
        if (parsedData->parametersCount >= 4 && parsedData->parameters[3].type == RPG::PARAM_NUMBER)
            balance = parsedData->parameters[3].number;
        else balance = 50;
        RPG::Sound newSound(IniValue, volume, tempo, balance);
        newSound.play();
    }

    if(!cmd.compare("bgm_custom")) {
        char IniValue[256];
        int volume;
        int tempo;
        int balance;
        int fade;
        GetPrivateProfileString("bgm_custom", parsedData->parameters[0].text , RPG::system->getBattleBGM()->filename, IniValue, 256, ".\\DynRPG.ini");
        if (parsedData->parametersCount >= 2 && parsedData->parameters[1].type == RPG::PARAM_NUMBER) {
            if (parsedData->parameters[1].number > 10) fade = 10000;
            else fade = (parsedData->parameters[1].number)*1000;
        }
        else fade = 0;
        if (parsedData->parametersCount >= 3 && parsedData->parameters[2].type == RPG::PARAM_NUMBER)
            volume = parsedData->parameters[2].number;
        else volume = 100;
        if (parsedData->parametersCount >= 4 && parsedData->parameters[3].type == RPG::PARAM_NUMBER)
            tempo = parsedData->parameters[3].number;
        else tempo = 100;
        if (parsedData->parametersCount >= 5 && parsedData->parameters[4].type == RPG::PARAM_NUMBER)
            balance = parsedData->parameters[4].number;
        else balance = 50;
        RPG::Music newMusic(IniValue, fade, volume, tempo, balance);
        newMusic.play();
    }

    return true;
}
