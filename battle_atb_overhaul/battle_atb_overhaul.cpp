// ATB Overhaul
// by PepsiOtaku
// Version 1.7

#include <DynRPG/DynRPG.h>
#include <vector>

#define ATB_PARTY RPG::Actor::partyMember(i)->atbValue
#define ATB_MON RPG::monsters[i]->atbValue

std::map<std::string, std::string> configuration;

int confAddValue;
int confHeroSpeedVarM;
int confBattlerStartVar;
int confMonsterSpeedVarM;
int confDefaultHeroSpeed;
int confDefaultMonsterSpeed;
int confAtbModeSwitch;
int confActiveSpeed;
int confWaitSpeed;
bool atbWait;
bool monsterAction = false;
bool confAgilMult;
bool condCheckFail;
bool preventEarlyResume = false;
bool animPlaying = false;
bool confStartInWaitMode = false;
bool confOnlyShowCommandWhenFocused = false;
bool confFixSelectionBarHeight = false;
bool speedInitialize = false;
int confFreezeSwitch;
std::string condExceptionSet;

std::vector<int> exceptionVect;

unsigned char frameTimer = 0;

bool onStartup(char *pluginName)
{
    configuration = RPG::loadConfiguration(pluginName);
    confAtbModeSwitch = atoi(configuration["ATBmodeSwitch"].c_str());
    confAddValue = atoi(configuration["AddValue"].c_str());
    confAgilMult = configuration["MultiplyAgility"] == "true";
    confHeroSpeedVarM = atoi(configuration["HeroSpeedMasterVar"].c_str()); // Convert String to Int
    confMonsterSpeedVarM = atoi(configuration["MonsterSpeedMasterVar"].c_str());
    confBattlerStartVar = atoi(configuration["BattlerStartVar"].c_str());
    confDefaultHeroSpeed = atoi(configuration["DefaultHeroSpeed"].c_str());
    confDefaultMonsterSpeed = atoi(configuration["DefaultMonsterSpeed"].c_str());
    confActiveSpeed = atoi(configuration["ActiveSpeed"].c_str());
    confWaitSpeed = atoi(configuration["WaitSpeed"].c_str());
    confFreezeSwitch = atoi(configuration["FreezeSwitch"].c_str());
    confStartInWaitMode = configuration["StartInWaitMode"] == "true";
    confOnlyShowCommandWhenFocused = configuration["OnlyShowCommandWhenFocused"] == "true";
    confFixSelectionBarHeight = configuration["FixSelectionBarHeight"] == "true";
    // get the condition exceptions
    condExceptionSet = configuration["ConditionExceptions"];
    std::string delimiter = ",";
    size_t pos = 0;
    int token;
    while ((pos = condExceptionSet.find(delimiter)) != std::string::npos)
    {
        token = atoi(condExceptionSet.substr(0, pos).c_str());
        exceptionVect.push_back(token);
        condExceptionSet.erase(0, pos + delimiter.length());
    }
    token = atoi(condExceptionSet.c_str());
    exceptionVect.push_back(token);

    return true;
}

void initializeSpeedVars()
{
    if (RPG::variables[confHeroSpeedVarM] == 0)
        RPG::variables[confHeroSpeedVarM] = confDefaultHeroSpeed;
    if (RPG::variables[confMonsterSpeedVarM] == 0)
        RPG::variables[confMonsterSpeedVarM] = confDefaultMonsterSpeed;
}

// this will reset RPG::BattleSpeed. NOTE: RPG::battleSpeed is only set to 100 (default), 0 (for Wait Mode), or 75 (for Active Mode)
// onFrame only makes alterations to individual battler's ATB bars
void resumeAtb()
{
    if (atbWait)
    {
        if (RPG::system->atbMode == RPG::ATBM_WAIT)
            RPG::battleSpeed = 100; // wait mode should stop the atb bar when heroes are selecting actions
        else
            RPG::battleSpeed = confActiveSpeed; // active mode should still move the atb bar by the % set in confActiveSpeed (100 is the default speed)
        atbWait = false;
    }
}

void onNewGame()
{
    // initialize the master speed variables based on what's in DynRPG.ini
    initializeSpeedVars();
    if (RPG::switches[confAtbModeSwitch])
        RPG::system->atbMode = RPG::ATBM_ACTIVE;
    else
        RPG::system->atbMode = RPG::ATBM_WAIT;
}

void onLoadGame(int id, char *data, int length)
{
    // initialize the master speed variables based on what's in DynRPG.ini
    //initializeSpeedVars(); // Probably shouldn't do this onLoadGame because saves might have them set to something else
    // initialize the Active/Wait system based on what the ATB Mode Switch is in the save file
    if (RPG::switches[confAtbModeSwitch])
        RPG::system->atbMode = RPG::ATBM_ACTIVE;
    else
        RPG::system->atbMode = RPG::ATBM_WAIT;
    speedInitialize = false; // Just in case
}

bool onSetSwitch(int id, bool value)
{
    // if ATBmodeSwitch is on, set it to active, otherwise if off, set to wait
    if (id == confAtbModeSwitch)
    { // this was moved from ragnadyn since it was more appropriate here
        if (value)
            RPG::system->atbMode = RPG::ATBM_ACTIVE;
        else
            RPG::system->atbMode = RPG::ATBM_WAIT;
    }
    else if (id == confFreezeSwitch)
    {
        if (value)
        {
            // same as @halt_atb but other plugins can call it
            if (RPG::system->atbMode == RPG::ATBM_WAIT)
                RPG::battleSpeed = confWaitSpeed; // wait mode should stop the atb bar when heroes are selecting actions
            else
                RPG::battleSpeed = confActiveSpeed;
            atbWait = true;
            preventEarlyResume = true;
        }
        else
        {
            // same as @resume_atb
            preventEarlyResume = false;
            resumeAtb();
        }
    }
    return true;
}

void initHeroSpeed()
{
    // Initialize hero speed variables
    for (int i = 0; i < 4; i++)
    {
        RPG::variables[confBattlerStartVar + i] = RPG::variables[confHeroSpeedVarM];
    }
}

void initMonsterSpeed()
{
    // Initialize monster speed variables
    for (int i = 0; i < 8; i++)
    {
        RPG::variables[confBattlerStartVar + 4 + i] = RPG::variables[confMonsterSpeedVarM];
    }
}

void onDrawScreen()
{
    // This has to be onDrawScreen because F12 calls the reset game function before onFrame is called or something (fun)
    if (RPG::isBattleTest && (GetKeyState(VK_F12) & 0x8000))
    {
        speedInitialize = false;
    }
}

void onFrame(RPG::Scene scene)
{
    if (scene == RPG::SCENE_BATTLE)
    {
        // Set Active/Wait if starting up a test battle
        if (RPG::isBattleTest && (RPG::variables[confHeroSpeedVarM] != confDefaultHeroSpeed))
        {
            if (confStartInWaitMode)
            {
                RPG::system->atbMode = RPG::ATBM_WAIT; // wait mode should stop the atb bar when heroes are selecting actions
                if (confAtbModeSwitch > 0)
                    RPG::switches[confAtbModeSwitch] = false;
            }
            else
            {
                RPG::system->atbMode = RPG::ATBM_ACTIVE;
                if (confAtbModeSwitch > 0)
                    RPG::switches[confAtbModeSwitch] = true;
            }
            initializeSpeedVars();
        }
        // Speed initialization at start of battle
        if (RPG::battleData->battlePhase == RPG::BPHASE_BATTLE && !speedInitialize)
        {
            initHeroSpeed();
            initMonsterSpeed();
            speedInitialize = true;
        }
        if (!atbWait)
        { // do not do the following if the ATB bar is set to 0 or a monster is performing an action
            frameTimer++;
            if (frameTimer > 10)
            {
                frameTimer = 0;
                animPlaying = false;
                for (int i = 0; i < 8; i++)
                {
                    if (RPG::monsters[i])
                        if (RPG::monsters[i]->animData->isAnimationPlaying)
                            animPlaying = true;
                    // Heroes
                    if (i < 4 && RPG::Actor::partyMember(i))
                    {
                        if (RPG::Actor::partyMember(i)->animData->isAnimationPlaying)
                            animPlaying = true;
                        for (unsigned int j = 0; j < exceptionVect.size(); j++)
                        {
                            if (RPG::Actor::partyMember(i)->conditions[exceptionVect[j]] != 0)
                            {
                                ATB_PARTY = 0;
                                condCheckFail = true;
                                break;
                            }
                            else
                                condCheckFail = false;
                        }
                        if (!condCheckFail) // Just check this first
                        {
                            //printf("onFrame: party condition checks\n");
                            if ((RPG::Actor::partyMember(i)->conditions[1] == 0              // ... the hero is alive
                                 && RPG::Actor::partyMember(i)->actionStatus == RPG::AS_IDLE // ... the hero is idle
                                 && RPG::battleData->battlePhase == RPG::BPHASE_BATTLE)      // ... the hero has not yet won the battle
                                && !animPlaying
                                // 14 is the animation id for battle won for whatever reason-- should be 11
                                && !RPG::switches[confFreezeSwitch] // Other plugins need a means of freezing battle
                            )
                            {
                                if (ATB_PARTY < 300000)
                                {
                                    if (confAgilMult == true)
                                        ATB_PARTY = ATB_PARTY + ((confAddValue * RPG::Actor::partyMember(i)->getAgility()) * RPG::variables[confBattlerStartVar + i]);
                                    else
                                        ATB_PARTY = ATB_PARTY + (confAddValue * RPG::variables[confBattlerStartVar + i]);
                                }
                                else
                                {
                                    ATB_PARTY = 300000;
                                }
                                if (ATB_PARTY < 0)
                                    ATB_PARTY = 0;
                            }
                        }
                    }

                    // Monsters
                    if (RPG::monsters[i])
                    {
                        for (unsigned int j = 0; j < exceptionVect.size(); j++)
                        {
                            if (RPG::monsters[i]->conditions[exceptionVect[j]] != 0)
                            {
                                condCheckFail = true;
                                break;
                            }
                            else
                                condCheckFail = false;
                        }
                        if (!condCheckFail) // Just check this first
                        {
                            if ((RPG::monsters[i]->conditions[1] == 0               // the monster is alive
                                 )                                                  //&& RPG::monsters[i]->actionStatus == RPG::AS_IDLE)
                                && !animPlaying && !RPG::switches[confFreezeSwitch] // Other plugins need a means of freezing battle
                                && (!RPG::battleData->winMonTarget->choiceActive || !RPG::battleData->winPartyTarget->choiceActive || !RPG::battleData->winItem->choiceActive || !RPG::battleData->winSkill->choiceActive))
                            {
                                if (ATB_MON < 300000)
                                {
                                    if (confAgilMult == true)
                                        ATB_MON = ATB_MON + (((confAddValue * RPG::monsters[i]->getAgility()) * RPG::variables[confBattlerStartVar + 4 + i]) / 2);
                                    else
                                        ATB_MON = ATB_MON + ((confAddValue * RPG::variables[confBattlerStartVar + 4 + i]) / 2);
                                }
                                else
                                {
                                    ATB_MON = 300000;
                                }
                                if (ATB_MON < 0)
                                    ATB_MON = 0;
                            }
                        }
                    }
                }
            }
        }
        if (RPG::battleData->battlePhase != RPG::BPHASE_BATTLE)
        {
            speedInitialize = false;
        }
    }
    else if (atbWait && scene != RPG::SCENE_BATTLE)
    {
        resumeAtb();
        frameTimer = 0;
        speedInitialize = false;
    }
}

void setCursorHeight(RPG::Window *&window)
{
    if (window)
    {
        if (window->cursorHeight != 16)
        {
            window->cursorHeight = 16;
            window->updateCursor(window->currentChoice);
        }
    }
}

// anytime the battle status window refreshes
bool onBattleStatusWindowDrawn(int x, int selection, bool selActive, bool isTargetSelection, bool isVisible)
{
    if (confOnlyShowCommandWhenFocused)
    {
        if (RPG::battleData->winCommand->choiceActive)
        {
            RPG::battleData->winCommand->x = 244;
        }
        else
        {
            RPG::battleData->winCommand->x = 320;
        }
    }
    if (RPG::system->scene == RPG::SCENE_BATTLE && confFixSelectionBarHeight)
    {
        setCursorHeight(RPG::battleData->winCommand);
        setCursorHeight(RPG::battleData->winItem);
        setCursorHeight(RPG::battleData->winSkill);
    }

    if (isTargetSelection && (RPG::battleData->winMonTarget->choiceActive || RPG::battleData->winPartyTarget->choiceActive ||
                              RPG::battleData->winItem->choiceActive || RPG::battleData->winSkill->choiceActive))
    {
        atbWait = true;
        RPG::battleSpeed = 0;
    }
    else
    {
        if (atbWait && RPG::battleSpeed == 0 && RPG::system->atbMode == RPG::ATBM_ACTIVE && !preventEarlyResume)
        {
            resumeAtb();
            if (RPG::battleData->winParty->choiceActive || RPG::battleData->winCommand->choiceActive)
                atbWait = true;
        }
    }

    if ((selActive && !atbWait) || (atbWait && (RPG::battleData->winParty->choiceActive || RPG::battleData->winCommand->choiceActive)))
    {
        if (RPG::system->atbMode == RPG::ATBM_WAIT)
            RPG::battleSpeed = confWaitSpeed; // wait mode should stop the atb bar when heroes are selecting actions
        else
            RPG::battleSpeed = confActiveSpeed; // active mode should still move the atb bar by the % set in confActiveSpeed (100 is the default speed)
        atbWait = true;
    }

    // if the party member dies (or has a condition with a status restriction) while the status window was open
    if (selection >= 0 && selection < 4 && !isTargetSelection && selActive)
    {
        if (RPG::Actor::partyMember(selection))
        {
            for (unsigned int j = 0; j < exceptionVect.size(); j++)
            {
                if ((RPG::Actor::partyMember(selection)->conditions[1] != 0) ||
                    (RPG::Actor::partyMember(selection)->conditions[exceptionVect[j]] != 0))
                {
                    // Nailed it!
                    RPG::battleData->winCommand->choiceActive = false;
                    RPG::battleData->winItem->choiceActive = false;
                    RPG::battleData->winSkill->choiceActive = false;
                    RPG::battleData->winMonTarget->choiceActive = false;
                    RPG::battleData->winPartyTarget->choiceActive = false;

                    RPG::battleData->winParty->choiceActive = true;
                    if (RPG::battleData->readyPartySlot[0] != -1)
                    {
                        //RPG::battleData->winParty->choiceActive = true;
                        RPG::battleData->winParty->currentChoice = RPG::battleData->readyPartySlot[0];
                    }
                    else
                    {
                        //RPG::battleData->winParty->choiceActive = false;
                    }
                    RPG::Actor::partyMember(selection)->atbValue = 0;
                    resumeAtb(); // resume the ATB bar
                    break;
                }
            }
        }
    }
    return true;
}

bool onDoBattlerAction(RPG::Battler *battler, bool firstTry)
{
    atbWait = true;
    RPG::battleSpeed = 0;
    return true;
}
bool onBattlerActionDone(RPG::Battler *battler, bool success)
{
    if (success && RPG::system->atbMode == RPG::ATBM_WAIT)
        resumeAtb();
    return true;
}

// do not move ATB bar when event commands are running
bool onEventCommand(RPG::EventScriptLine *scriptLine, RPG::EventScriptData *scriptData,
                    int eventId, int pageId, int lineId, int *nextLineId)
{
    if (RPG::system->scene == RPG::SCENE_BATTLE && eventId == 0)
    {                                       // battle events
        if (scriptData->currentLineId == 0) // when an event page starts
            // *******************************************************
            atbWait = true;
        // *******************************************************
        else if (scriptLine->command == RPG::EVCMD_END_OF_EVENT) // when an event page ends
            resumeAtb();
    }
    return true;
}

bool onComment(const char *text,
               const RPG::ParsedCommentData *parsedData,
               RPG::EventScriptLine *nextScriptLine,
               RPG::EventScriptData *scriptData,
               int eventId,
               int pageId,
               int lineId,
               int *nextLineId)
{
    std::string cmd = parsedData->command;
    if (!cmd.compare("init_hero_speed"))
    {
        initHeroSpeed();
        return false;
    }
    if (!cmd.compare("init_monster_speed"))
    {
        initMonsterSpeed();
        return false;
    }
    if (!cmd.compare("condition_speed_check"))
    {
        // parameter 1: condition ID
        if (parsedData->parametersCount >= 3 && parsedData->parameters[0].type == RPG::PARAM_NUMBER && parsedData->parameters[1].type == RPG::PARAM_NUMBER && parsedData->parameters[2].type == RPG::PARAM_NUMBER)
        {
            for (int i = 0; i < 8; i++)
            {
                if (i < 4)
                {
                    if (RPG::Actor::partyMember(i))
                    {
                        if (RPG::Actor::partyMember(i)->conditions[parsedData->parameters[0].number] > 0)
                            RPG::variables[confBattlerStartVar + i] = parsedData->parameters[1].number;
                        else
                            RPG::variables[confBattlerStartVar + i] = RPG::variables[confHeroSpeedVarM];
                    }
                }
                if (RPG::monsters[i])
                {
                    if (RPG::monsters[i]->conditions[parsedData->parameters[0].number] != 0)
                        RPG::variables[confBattlerStartVar + 4 + i] = parsedData->parameters[2].number;
                    else
                        RPG::variables[confBattlerStartVar + 4 + i] = RPG::variables[confMonsterSpeedVarM];
                }
            }
        }
        return false;
    }
    if (!cmd.compare("halt_atb"))
    {
        if (RPG::system->atbMode == RPG::ATBM_WAIT)
            RPG::battleSpeed = confWaitSpeed; // wait mode should stop the atb bar when heroes are selecting actions
        else
            RPG::battleSpeed = confActiveSpeed;
        atbWait = true;
        preventEarlyResume = true;
        return false;
    }
    if (!cmd.compare("resume_atb"))
    {
        preventEarlyResume = false;
        resumeAtb();
        return false;
    }
    return true;
}

void onExit()
{
    exceptionVect.clear();
}
