========================================================================
Store Item, Skill & Condition ID in Battle v1.1
For RPG Maker 2003 with DynRPG v0.20 or higher
By PepsiOtaku
========================================================================

This plugin will store the Skill or Item ID that's used during a battle's action to a variable, and turn
on a switch saying it was done. This allows for additional battle trigger conditions.

Using a comment command, it can also check all of the battlers for a specific condition. The Id will be
stored in 1 of 12 variables, depending on the battler. It also turns on one of two switches (Monster/hero) if either one of the heroes or one of the monsters has that condition.

To check for a condition every turn, use "Turns Elapsed [0]" for the first turn, "Turns Elapsed [1x+1]" for all subsequent turns, and Place a "@check_condition #" comment in either of those.

IMPORTANT: It is the maker's responsibility to turn off the switches and reset the variables after the
action has been made (or at the start of battle). I recommend adding a Trigger condition for 
Turns Elapsed [0] and calls a common event that does this.



Installation
-------------

To install the plugin, make sure that you have patched your project with cherry's DynRPG patch which
can be found here: 
http://share.cherrytree.at/showfile-12494/dynrpg.rar (Link for v0.20)
http://cherrytree.at/dynrpg

1. Copy the "battle_store_itemskill.dll" into the DynPlugins folder of your own project.

2. Add the following (between the asterisks) to your DynRPG.ini 

**********************************************

[battle_store_itemskill]
SkillIdSwitch=4037
SkillIdVar=4016
ItemIdSwitch=4038
ItemIdVar=4017
ConditionSwitch=4049
MonSkillIdSwitch=4042
MonSkillIdVar=4023
MonConditionSwitch=4050
ConditionIdStartVar=4081

**********************************************

3. Set the "SkillIdSwitch" value to the switch of your choice for when a hero uses a skill.

4. Set the "SkillIdVar" value to the variable of your choice for when a hero uses a skill.

5. Set the "ItemIdSwitch" value to the switch of your choice for when a hero uses an item.

6. Set the "ItemIdVar" value to the variable of your choice for when a hero uses an item.

7. Set the "ConditionSwitch" value to the switch of your choice for when any hero has the condition specified.

8. Set the "MonSkillIdSwitch" value to the switch of your choice for when a monster uses a skill.

9. Set the "MonSkillIdVar" value to the variable of your choice for when a monster uses a skill.

10. Set the "MonConditionSwitch" value to the switch of your choice for when any monster has the condition specified.

11. Set the "ConditionIdStartVar" to the value of the first variable in a range of 12 to identify each battler.
	When a battler has the specified condition, the variable will equal that condition ID, otherwise it will 
	automatically be set to 0.
	Only heroes and monsters that exist in the battle arena are tracked.
    Var+0 through Var+3: The 4 heroes
    Var+4 through var+11: the 8 monsters
    Example: If ConditionIdStarVar was set to 4081, Hero 3's variable would be 4083, and Monster 5's variable would
	be 4089


NOTE: Monsters can't use items, therefor, a "MonItemIdSwitch/Var" is not needed.


Instructions
-------------

In your battles, add a Trigger condition for Turns Elapsed [0] and calls a common event that turns off the three switches, and sets the 3 skill/item variables to 0. This will ensure they're initialized at the start of every battle. 
Next, follow these steps:

Step 1: Add a trigger condition for the switch of your choice
Step 2: Add a conditional check for the variable used
Step 3: Turn the switch off and reset the variable at the end of the event
Step 4: ????
Step 5: Profit!


Condtion checking is a little more involved. You must use the command "@check_condition #" to check for a specific condition, where # is the database ID of the condition to check for. As mentioned above, it will set the appropriate variable to the condition ID when the check is true. 

If one of the heroes has the condition, ConditionSwitch will be true, and if one of the monsters has the condition, MonConditionSwitch will be true. You will need to turn these off before/after use if you need to check them.