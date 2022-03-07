// Provoke Skill
// by PepsiOtaku
// Version 4.1

#include <DynRPG/DynRPG.h>
#include <vector>

std::map<std::string, std::string> configuration;

// party[battler] = target
std::map<int,int> hero;
//int hero[4];
std::map<int,int> monster;
//int monster[8];

int m_id;
int h_id;
int confConditionId;

std::vector<int> skillVect; // stores the skill IDs that Provoke will use

#define M_CHECK_PRVK(BATTLER,ID) if (ID > -1) { \
        if (battler->conditions[confConditionId] != 0 && BATTLER) \
            battler->action->targetId = ID; \
        else if (ID != -1) { \
            ID = -1; \
        } \
    }


bool onStartup (char *pluginName) {
    // Get configuration settings for key variables
    configuration = RPG::loadConfiguration(pluginName);
    // Provoke Condition ID
    confConditionId = atoi(configuration["ConditionId"].c_str()); // Convert String to Int
    // Provoke Skill ID
	std::string confSkills;
    confSkills = configuration["SkillId"]; // Convert String to Int
    // Parses the skill ID's for Provoke
    std::string delimiter = ",";
    size_t pos = 0;
    int token;
    while ((pos = confSkills.find(delimiter)) != std::string::npos) {
        token = atoi(confSkills.substr(0, pos).c_str());
        skillVect.push_back(token);
        confSkills.erase(0, pos + delimiter.length());
    }
    token = atoi(confSkills.c_str());
    skillVect.push_back(token);

	for (int i=0; i<8; i++) {
		if (i<4) hero[i] = -1;
		monster[i] = -1;
	}
    return true;
}

bool onDoBattlerAction (RPG::Battler* battler, bool firstTry) {
	// Set Provoke
	if(battler->action->kind == RPG::AK_SKILL && firstTry) {
		for (unsigned int j=0; j<skillVect.size(); j++) {
			if (battler->action->skillId == skillVect[j]) {
				// Save the ID's for use later
				if (battler->isMonster()) {
                    m_id = battler->id-1;
                    hero[battler->action->targetId] = m_id;
				} else {
				    h_id = RPG::getPartyIndex(battler->id);
				    monster[battler->action->targetId] = h_id;
				}
			}
		}
	}

	// Hero is battler
    if (!battler->isMonster()) {
		if (battler->action->target == RPG::TARGET_MONSTER) {
            h_id = RPG::getPartyIndex(battler->id);

            M_CHECK_PRVK(RPG::monsters[hero[h_id]],hero[h_id])
		}
    }

	// Monster is battler
    else {
		if (battler->action->target == RPG::TARGET_ACTOR) {
            m_id = battler->id-1;

            M_CHECK_PRVK(RPG::Actor::partyMember(monster[m_id]),monster[m_id])
		}
	}
    return true;
}

bool onComment(const char* text, const RPG::ParsedCommentData* parsedData, RPG::EventScriptLine* nextScriptLine,
		       RPG::EventScriptData* scriptData, int eventId, int pageId, int lineId, int* nextLineId)
{
    std::string cmd = parsedData->command;

	// For provoke_monster & provoke_hero,
	// param1 = battler  (one-based)
	// param2 = targetId (one-based)

    // Forces a monster to attack the hero during the turn this is called
    if(!cmd.compare("provoke_monster")) {
        int m = parsedData->parameters[0].number-1; // monster's party ID
        int h = RPG::getPartyIndex(parsedData->parameters[1].number); // hero's party ID
		monster[m] = h;
		if (RPG::monsters[m])
			RPG::monsters[m]->conditions[confConditionId] = 1;
		return false;
    }

	// Forces a hero to attack the monster during the turn this is called
	if(!cmd.compare("provoke_hero")) {
        int h = RPG::getPartyIndex(parsedData->parameters[0].number); // hero's party ID
		int m = parsedData->parameters[1].number-1; // monster's party ID
		hero[h] = m;
		if (RPG::Actor::partyMember(m))
			RPG::Actor::partyMember(m)->conditions[confConditionId] = 1;
		return false;
    }
    return true;
}

void onExit() {
    hero.clear();
    monster.clear();
}
