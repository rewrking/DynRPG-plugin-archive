#define _WIN32_WINNT 0x0502
#include <DynRPG/DynRPG.h>
#include <cstdio>
#include <vector>

struct hflags {
    int heroId;
    bool twoWeapons;
    bool lockEquipment;
    bool aiControl;
    bool mightyGuard;

    int condArraySize;
    int attrArraySize;
    std::map<int, RPG::DamageMultiplier_T> dbConditions;
    std::map<int, RPG::DamageMultiplier_T> conditions;
    std::map<int, RPG::DamageMultiplier_T> dbAttributes;
    std::map<int, RPG::DamageMultiplier_T> attributes;
};

typedef std::vector<hflags*> heroFlagList; // vector of aswitch structures
heroFlagList heroFlags;                     // declare it

std::map<std::string, std::string> configuration;

bool confShowDebug = false;


void changeFileName(int n, int thresh);

bool onStartup (char *pluginName) {
    configuration = RPG::loadConfiguration(pluginName);
    confShowDebug = configuration["ShowDebug"] == "true";
    //confRunSpeed = atoi(configuration["RunSpeed"].c_str());

    // --Debugging console--
    if (confShowDebug) {
        AllocConsole();
        AttachConsole(GetCurrentProcessId());
        freopen("CON", "w", stdout);
        printf("Debug: %s\n",pluginName);
    }
    return true;
}

void printHeroFlags(int hero) {
    printf("Flags for %s:\n",RPG::dbActors[hero]->name.s_str().c_str());
    printf("  Two Weapons:    %i\n",RPG::actors[hero]->twoWeapons);
    printf("  Lock Equipment: %i\n",RPG::actors[hero]->lockEquipment);
    printf("  AI Control:     %i\n",RPG::actors[hero]->aiControl);
    printf("  Mighty Guard:   %i\n",RPG::actors[hero]->mightyGuard);
}

void printHeroAttributes(int hero) {
    printf("Attribute Resists for %s:\n",RPG::dbActors[hero]->name.s_str().c_str());
    for (int i = 1; i<=RPG::attributes.count(); i++) {
        printf("  attributes[%i]: ",i);
        printf("%i\n",RPG::dbActors[hero]->attributes[i]);
    }
}

void printHeroConditions(int hero) {
    printf("Conditions Resists for %s:\n",RPG::dbActors[hero]->name.s_str().c_str());
    RPG::dbActors[hero]->conditions[1] = RPG::DMG_E;
    for (int i = 1; i<=RPG::conditions.count(); i++) {
        printf("  conditions[%i]: ",i);
        printf("%i\n",RPG::dbActors[hero]->conditions[i]);
    }
}

bool onComment(const char* text, const RPG::ParsedCommentData* parsedData, RPG::EventScriptLine* nextScriptLine,
		       RPG::EventScriptData* scriptData, int eventId, int pageId, int lineId, int* nextLineId)
{
    std::string cmd = parsedData->command;

    if(!cmd.compare("hero_options_set")) {
        int hero = parsedData->parameters[0].number;
        int vectId = 0;
        bool foundHero = false;
        if (hero > 0 && hero <= RPG::dbActors.count()) {
            for (unsigned int i=0; i<heroFlags.size(); i++) {
                if (heroFlags[i]->heroId == hero) {
                    foundHero = true;
                    vectId = i;
                    break;
                }
            }
            if (foundHero == false) {
                hflags* newFlags = new hflags;
                newFlags->heroId = hero;
                newFlags->twoWeapons = RPG::actors[hero]->twoWeapons;
                newFlags->lockEquipment = RPG::actors[hero]->lockEquipment;
                newFlags->aiControl = RPG::actors[hero]->aiControl;
                newFlags->mightyGuard = RPG::actors[hero]->mightyGuard;

                newFlags->condArraySize = RPG::conditions.count();
                newFlags->attrArraySize = RPG::attributes.count();
                for (int i=1; i<=newFlags->condArraySize; i++) {
                    newFlags->conditions[i] = newFlags->dbConditions[i] = RPG::dbActors[hero]->conditions[i];
                }
                for (int i=1; i<=newFlags->attrArraySize; i++) {
                    newFlags->attributes[i] = newFlags->dbAttributes[i] = RPG::dbActors[hero]->attributes[i];
                }
                heroFlags.push_back(newFlags);
            }
            if (parsedData->parameters[1].type == RPG::PARAM_STRING && parsedData->parameters[2].type == RPG::PARAM_NUMBER) {
                if (strcmp(parsedData->parameters[1].text,"two_weapons") == 0) {
                    if (parsedData->parameters[2].number == 1)
                        heroFlags[vectId]->twoWeapons = true;
                    else
                        heroFlags[vectId]->twoWeapons = false;
                    if (RPG::actors[hero])
                        RPG::actors[hero]->twoWeapons = heroFlags[vectId]->twoWeapons;
                    if (confShowDebug) {
                        printf("%s:   ",RPG::dbActors[hero]->name.s_str().c_str());
                        printf("Set \"Two Weapons\" to %i.\n",heroFlags[vectId]->twoWeapons);
                    }

                } else if (strcmp(parsedData->parameters[1].text,"lock_equipment") == 0) {
                    if (parsedData->parameters[2].number == 1)
                        heroFlags[vectId]->lockEquipment = true;
                    else
                        heroFlags[vectId]->lockEquipment = false;
                    if (RPG::actors[hero])
                        RPG::actors[hero]->lockEquipment = heroFlags[vectId]->lockEquipment;
                    if (confShowDebug) {
                        printf("%s:   ",RPG::dbActors[hero]->name.s_str().c_str());
                        printf("Set \"Lock Equipment\" to %i.\n",heroFlags[vectId]->lockEquipment);
                    }

                } else if (strcmp(parsedData->parameters[1].text,"ai_control") == 0) {
                    if (parsedData->parameters[2].number == 1)
                        heroFlags[vectId]->aiControl = true;
                    else
                        heroFlags[vectId]->aiControl = false;
                    if (RPG::actors[hero])
                        RPG::actors[hero]->aiControl = heroFlags[vectId]->aiControl;
                    if (confShowDebug) {
                        printf("%s:   ",RPG::dbActors[hero]->name.s_str().c_str());
                        printf("Set \"AI Control\" to %i.\n",heroFlags[vectId]->aiControl);
                    }

                } else if (strcmp(parsedData->parameters[1].text,"mighty_guard") == 0) {
                    if (parsedData->parameters[2].number == 1)
                        heroFlags[vectId]->mightyGuard = true;
                    else
                        heroFlags[vectId]->mightyGuard = false;
                    if (RPG::actors[hero])
                        RPG::actors[hero]->mightyGuard = heroFlags[vectId]->mightyGuard;
                    if (confShowDebug) {
                        printf("%s:   ",RPG::dbActors[hero]->name.s_str().c_str());
                        printf("Set \"Mighty Guard\" to %i.\n",heroFlags[vectId]->mightyGuard);
                    }

                } else {
                    int value = -1;
                    const char* multiplier = "C";
                    // Use either A,B,C,D,E or their internal numeric values for the parameter
                    if (parsedData->parameters[3].type == RPG::PARAM_STRING) {
                        multiplier = parsedData->parameters[3].text;
                        if (strcmp(multiplier,"A") == 0) value = 0;
                        else if (strcmp(multiplier,"B") == 0) value = 1;
                        else if (strcmp(multiplier,"C") == 0) value = 2;
                        else if (strcmp(multiplier,"D") == 0) value = 3;
                        else if (strcmp(multiplier,"E") == 0) value = 4;
                        else value = -1;
                    } else if (parsedData->parameters[3].type == RPG::PARAM_NUMBER) {
                        value = parsedData->parameters[3].number;
                        if (value < 0 || value > 4) value = -1;
                        switch (value) {
                            case 0: multiplier = "A"; break;
                            case 1: multiplier = "B"; break;
                            case 2: multiplier = "C"; break;
                            case 3: multiplier = "D"; break;
                            case 4: multiplier = "E"; break;
                            default: break;
                        }
                    }
                    if (strcmp(parsedData->parameters[1].text,"condition_resist") == 0) {
                        int condition = parsedData->parameters[2].number;
                        // Condition 1 is the "Death" condition and can't be changed anyway. The actual resistance is always 4 ("E") regardless of
                        //   what it's set at in the database... good ol' 2k3
                        if (condition > 1 && condition <= RPG::conditions.count() && value != -1) {
                            heroFlags[vectId]->conditions[condition] = value;
                            RPG::dbActors[hero]->conditions[condition] = value;
                            if (confShowDebug) {
                                printf("%s:   ",RPG::dbActors[hero]->name.s_str().c_str());
                                printf("Set Condition \"%s\" resistance ",RPG::conditions[condition]->name.s_str().c_str());
                                printf("to %s.\n",multiplier);
                            }
                        }
                    } else if (strcmp(parsedData->parameters[1].text,"attribute_resist") == 0) {
                        int attribute = parsedData->parameters[2].number;
                        if (attribute > 0 && attribute <= RPG::attributes.count() && value != -1) {
                            heroFlags[vectId]->attributes[attribute] = value;
                            RPG::dbActors[hero]->attributes[attribute] = value;
                            if (confShowDebug) {
                                printf("%s:   ",RPG::dbActors[hero]->name.s_str().c_str());
                                printf("Set Attribute \"%s\" resistance ",RPG::attributes[attribute]->name.s_str().c_str());
                                printf("to %s.\n",multiplier);
                            }
                        }
                    }
                }
            }
        }
        return false;
    }

    if(!cmd.compare("hero_options_print_flags")) {
        int hero = parsedData->parameters[0].number;
        if (RPG::actors[hero] && confShowDebug) printHeroFlags(hero);
        return false;
    }

    if(!cmd.compare("hero_options_print_attributes")) {
        int hero = parsedData->parameters[0].number;
        if (RPG::actors[hero] && confShowDebug) printHeroAttributes(hero);
        return false;
    }
    if(!cmd.compare("hero_options_print_conditions")) {
        int hero = parsedData->parameters[0].number;
        if (RPG::actors[hero] && confShowDebug) printHeroConditions(hero);
        return false;
    }

    if(!cmd.compare("hero_options_reset_flags")) {
        int hero = parsedData->parameters[0].number;
        RPG::actors[hero]->twoWeapons = RPG::dbActors[hero]->twoWeapons;
        RPG::actors[hero]->lockEquipment = RPG::dbActors[hero]->lockEquipment;
        RPG::actors[hero]->aiControl = RPG::dbActors[hero]->aiControl;
        RPG::actors[hero]->mightyGuard = RPG::dbActors[hero]->mightyGuard;
        return false;
    }

    if(!cmd.compare("hero_options_reset_conditions")) {
        int hero = parsedData->parameters[0].number;
        int vectId = 0;
        bool foundHero = false;
        for (unsigned int i=0; i<heroFlags.size(); i++) {
            if (heroFlags[i]->heroId == hero) {
                foundHero = true;
                vectId = i;
                break;
            }
        }
        if (RPG::actors[hero] && foundHero) {
            for (int j=1; j<=RPG::conditions.count(); j++) {
                RPG::dbActors[hero]->conditions[j] = heroFlags[vectId]->dbConditions[j];
            }
        }
        return false;
    }

    if(!cmd.compare("hero_options_reset_attributes")) {
        int hero = parsedData->parameters[0].number;
        int vectId = 0;
        bool foundHero = false;
        for (unsigned int i=0; i<heroFlags.size(); i++) {
            if (heroFlags[i]->heroId == hero) {
                foundHero = true;
                vectId = i;
                break;
            }
        }
        if (RPG::actors[hero] && foundHero) {
            for (int j=1; j<=RPG::attributes.count(); j++) {
                RPG::dbActors[hero]->attributes[j] = heroFlags[vectId]->dbAttributes[j];
            }
        }
        return false;
    }

    return true;
}

void onInitTitleScreen() {
    heroFlags.clear();
}

void onNewGame () {
    heroFlags.clear();
}

void onSaveGame( int id, void __cdecl(*savePluginData) (char* data, int length)) {
    // Save dat data
    if (heroFlags.size() > 0) {
        int condSize = heroFlags[0]->condArraySize;
        int attrSize = heroFlags[0]->attrArraySize;
        int params = 7; // number of params to save during loop (not counting conditions and attributes)
        int offset = 2; // number of params to save before loop (condSize & attrSize)
        int dataArray[heroFlags.size()*(params+(condSize*2)+(attrSize*2))+offset];
        dataArray[0] = condSize;
        dataArray[1] = attrSize;
        for (unsigned int i=0; i<heroFlags.size(); i++) {
            dataArray[offset+(i*params)] = heroFlags[i]->heroId;
            dataArray[offset+(i*params+1)] = heroFlags[i]->twoWeapons;
            dataArray[offset+(i*params+2)] = heroFlags[i]->lockEquipment;
            dataArray[offset+(i*params+3)] = heroFlags[i]->aiControl;
            dataArray[offset+(i*params+4)] = heroFlags[i]->mightyGuard;
            for (int j=1; j<=condSize; j++) {
                dataArray[offset+(i*params+4+j)] = heroFlags[i]->dbConditions[j];
                dataArray[offset+(i*params+4+condSize+j)] = heroFlags[i]->conditions[j];
            }
            for (int j=1; j<=attrSize; j++) {
                dataArray[offset+(i*params+4+(condSize*2)+j)] = heroFlags[i]->dbAttributes[j];
                dataArray[offset+(i*params+4+(condSize*2)+attrSize+j)] = heroFlags[i]->attributes[j];
            }
        }
        savePluginData((char *)dataArray, sizeof(dataArray));
    }
}

void onLoadGame (int id, char* data, int length) {
    // Reset conditions & attributes to database default, since 2k3 doesn't do this
    for (unsigned int i=0; i<heroFlags.size(); i++) {
        if (RPG::actors[heroFlags[i]->heroId]) {
            for (int j=1; j<=RPG::conditions.count(); j++) {
                RPG::dbActors[heroFlags[i]->heroId]->conditions[j] = heroFlags[i]->dbConditions[j];
            }
            for (int j=1; j<=RPG::attributes.count(); j++) {
                RPG::dbActors[heroFlags[i]->heroId]->attributes[j] = heroFlags[i]->dbAttributes[j];
            }
        }
    }
    // We're done with the existing heroFlags, so it can be cleared at this point
    heroFlags.clear();
    // Check for existing data
    if (length > 0) {
        int *dataArray = (int *)data;
        int condSize = dataArray[0];
        int attrSize = dataArray[1];
        int params = 7;
        int offset = 2;
        // sick loop that gets the data back and places each one into the heroFlags vector in the correct order
        for (int i=2; i<(length-offset)/(params+(condSize*2)+(attrSize*2)); i=i+3) {
            hflags* newFlags = new hflags;
            newFlags->condArraySize = condSize;
            newFlags->attrArraySize = attrSize;
            newFlags->heroId = dataArray[i];
            newFlags->twoWeapons = dataArray[i+1];
            newFlags->lockEquipment = dataArray[i+2];
            newFlags->aiControl = dataArray[i+3];
            newFlags->mightyGuard = dataArray[i+4];
            for (int j=1; j<=condSize; j++) {
                newFlags->dbConditions[j] = dataArray[i+4+j];
                newFlags->conditions[j] = dataArray[i+4+condSize+j];
            }
            for (int j=1; j<=attrSize; j++) {
                newFlags->dbAttributes[j] = dataArray[i+4+(condSize*2)+j];
                newFlags->attributes[j] = dataArray[i+4+(condSize*2)+attrSize+j];
            }
            heroFlags.push_back(newFlags);
        }
        // Finally, go through the heroFlags data again and save it to actors
        // conditions & attributes have to be saved to dbActors
        for (unsigned int i=0; i<heroFlags.size(); i++) {
            if (RPG::actors[heroFlags[i]->heroId]) {
                RPG::actors[heroFlags[i]->heroId]->twoWeapons = heroFlags[i]->twoWeapons;
                RPG::actors[heroFlags[i]->heroId]->lockEquipment = heroFlags[i]->lockEquipment;
                RPG::actors[heroFlags[i]->heroId]->aiControl = heroFlags[i]->aiControl;
                RPG::actors[heroFlags[i]->heroId]->mightyGuard = heroFlags[i]->mightyGuard;
                // use count() this time in case the array size was changed
                for (int j=1; j<=RPG::conditions.count(); j++) {
                    RPG::dbActors[heroFlags[i]->heroId]->conditions[j] = heroFlags[i]->conditions[j];
                }
                for (int j=1; j<=RPG::attributes.count(); j++) {
                    RPG::dbActors[heroFlags[i]->heroId]->attributes[j] = heroFlags[i]->attributes[j];
                }
            }
        }
    }
}

void onExit () {
    heroFlags.clear();
}
