========================================================================
Provoke Skill v4.1
For RPG Maker 2003 with DynRPG v0.20 or higher
By PepsiOtaku
========================================================================

This plugin adds the ability for a "Provoke" skill. What it does is tracks the hero who cast it, and tells the enemy target to attack that hero as long as the "Provoke" condition on them lasts. It also supports multiple hero/monster scenarios, so potentially, all of your party members can Provoke different enemies, and the monsters will stick to their corresponding attackers. Additionally, if 2 different heros Provoke the same monster, the monster will attack the last hero to Provoke them.

You can also force a monster to attack a hero at any time with @provoke_monster


Installation
-------------
To install the plugin, make sure that you have patched your project with cherry's DynRPG patch which
can be found here: 
http://share.cherrytree.at/showfile-12494/dynrpg.rar (Link for v0.20)
http://cherrytree.at/dynrpg

1. Copy the "battle_skill_provoke.dll" into the DynPlugins folder of your own project.

2. Add the following (between the asterisks) to your DynRPG.ini:

**********************************************

[battle_skill_provoke]
SkillId=10,1,4
ConditionId=10

**********************************************

3. Change the SkillID(s) to your Provoke Skill (100% success is recommended, but do as you wish). Multiple skills
should be separated by a comma with no spaces (example: 10,1,4).

4. Change the Condition ID to your Provoke Condition


Changelog:
v4.1: Fixed a crash when a provoked enemy tries to cast magic on itself
v4.0: Added @provoke_hero command, and bugfixes
v3.1: Added @provoke_monster command (forces provoke during execution of a battle event.
v3.0: Added the ability to use multiple skills. 
v2.0: No longer uses in-game variables! (Code no longer sucks!)



Instructions
-------------
1. Create a new condition with No Action Restriction set. Set a recovery time you think would be appropriate.

2. Next, create a skill that inflicts Provoke.

3. Set the ID's of both in your ini, and you're done!

Additionally, you can force provoke a battler to attack a target using the following comment command:

@provoke_monster
  - Parameter 1 (number): Monster ID (1-8)
  - Parameter 2 (number): Hero/Target ID (1-4)
@provoke_hero
  - Parameter 1 (number): Hero ID (1-4)
  - Parameter 2 (number): Monster/Target ID (1-8)
  
  Example: "@provoke_monster 2,3" would have the 2nd monster attack the party member in slot 3. Doing this will only affect that monster's next turn, but adding that comment to an event page with the Trigger "Turns Elapsed  [1x+1]" would target that hero every turn.

  


