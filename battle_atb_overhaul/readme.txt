========================================================================
ATB OVERHAUL (formerly Advanced Faster ATB 2) v1.7
For RPG Maker 2003 with DynRPG v0.20 or higher
By PepsiOtaku
========================================================================

This patch allows you to control the speed calculations of party members and monsters independently, in turn controlling the speed of ATB bar.  It uses the formula:

************************************
(ActiveSpeed or WaitSpeed) + ((AddValue * Agility) * (HeroSpeed or MonsterSpeed))
************************************

The maximum value the ATB Speed can be is 30000, which will trigger the battler's next action. The AddValue is a hard-coded number you set within the DynRPG.ini file. 300 is the recommended value, but you can decrease/increase this value to your desired result. The SpeedVar is a multiplier that you can set via variable from within RPG Maker. 

The formula gets calculated a few times a second, so if you set your AddValue to 125 & the SpeedVar to 12, while the agility is 20 (multiplying to 30000) you would get an instantaneous ATB bar (which also makes things a little easy) forcing each party member's action. The lower the AddValue, the higher your SpeedVar value needs to be. 

While you can't technically "stop" the ATB bar using that formula, you can set the SpeedVar to a negative value in RPG maker, which would make the ATB bar go backwards in game until it hits 0 and remains there until the SpeedVar is changed again.


What's NEW:

* v1.7: Fixed a bug in condition_speed_check where speed wouldn't reset when condition wore off (like a Berserk condition where speed increases)

* v1.6: More bug-fixes, StartInWaitMode, OnlyShowCommandWhenFocused, FixSelectionBarHeight, new recommended AddValue & ActiveSpeed, improved this readme hopefully

* v1.5: More tweaks and bug-fixes! 

* v1.4: More bug squashing.
	- prevented the ATB bars from moving while any selection windows are open, with the exception of command and party member selections

Installation
-------------

To install the plugin, make sure that you have patched your project with cherry's DynRPG patch which can be found here: 
http://share.cherrytree.at/showfile-24504/dynrpg_0_31_05_26_2016.rar (Link for 0.31 - latest)
http://www.rewking.com/dynrpg
http://cherrytree.at/dynrpg

1. Copy the "battle_atb_overhaul.dll" into the DynPlugins folder of your own project.

2. Add the following (between the asterisks) to your DynRPG.ini 

**********************************************

[battle_atb_overhaul]
; Starts the game (or test play) in Wait Mode instead of Active mode (Active is 2k3's default)
StartInWaitMode=false
; In Alternative mode, only show the command window (Attack/Magic/etc) when a hero has been selected
OnlyShowCommandWhenFocused=false
; FixSelectionBarHeight makes the selection bar height 16px instead of 15px in Command, Item & Skill windows.
; It might look better depending on your SystemSet or preference
FixSelectionBarHeight=false
; Switch ON = Active, Switch OFF = Wait
ATBmodeSwitch=4004
; ...(ActiveSpeed or WaitSpeed) + ((AddValue * Agility) * SpeedVar)...
; Default = 300
AddValue=300
; Set MultiplyAgility to false to change the formula to ...Base ATB Speed + (AddValue * SpeedVar)...
MultiplyAgility=true
; Master Variables. The 12 variables starting with BattlerStartVar get set to these
HeroSpeedMasterVar=4001
MonsterSpeedMasterVar=4015
; Heroes Require 4 vars: BattlerStartVar+0,+1,+2,+3
; Monsters Requires 8 vars: BattlerStartVar+4,+5,+6,+7,+8,+9,+10,+11
BattlerStartVar=4041
; Default multiplier values
DefaultHeroSpeed=3
DefaultMonsterSpeed=3
; ActiveSpeed default = 50. 100 is RM2k3's default speed, so it's recommended to set less 
; so that modifiers would be more precise. Setting to 0 would always force WAIT mode.
ActiveSpeed=50
; WaitSpeed default = 0. Set to the same value as ActiveSpeed to force ACTIVE mode.
WaitSpeed=0
; Switch that will freeze the ATB bars if turned on
FreezeSwitch=4048
; Add condition exceptions here, separated by commas (ex: CondtionException=7,8,12,13)
; This will prevent the ATB bar from moving while a condition has "No Action Allowed"
ConditionExceptions=

**********************************************

3. Set "StartInWaitMode" to true to start the game (or test play) in Wait Mode instead of Active mode (Active is 2k3's default)

4. Set "OnlyShowCommandWhenFocused" to true to only show the command window when a hero has been selected (special feature of this plugin)

5. Set "FixSelectionBarHeight" to true to make the selection bar height 16px instead of 15px in Command, Item & Skill windows. If you don't know what this means, leave it at false, but this might look better depending on your SystemSet or preference.

6. Set "ATBmodeSwitch" to the switch value of your choice to change the ATB mode by switch. Switch ON = Active, Switch OFF = Wait

7. "AddValue" is for speed calculations (See top paragraphs). This can be set to any value between 0 and 30000, but you must figure out how this would affect the ATB formula.
   
8. Set "MultiplyAgility" to false to remove Agility from the formula, making it:
	(ActiveSpeed or WaitSpeed) + (AddValue * (HeroSpeed or MonsterSpeed))

9. Change "HeroSpeedMasterVar" to the Variable ID of your choice. This variable controls the Master Speed multiplier for party members. 4001 is the default.

10. "Change MonsterSpeedMasterVar" to the Variable ID of your choice. This variable controls the Master Speed multiplier for monsters. 4015 is the default

11. Change "BattlerStartVar" to the Variable ID of your choice. 12 variables starting from here will be used for the ATB speed multipliers of individual battlers. The first 4 will be for battlers (4041-4044) while the last 8 will be used for monsters (4045-4052)
   Example naming scheme:
       4041:DynRPG-Hero1Speed
	   4042:DynRPG-Hero2Speed
	   4043:DynRPG-Hero3Speed
	   4044:DynRPG-Hero4Speed
	   4045:DynRPG-Monster1Speed
	   4046:DynRPG-Monster2Speed
	   4047:DynRPG-Monster3Speed
	   4048:DynRPG-Monster4Speed
	   4049:DynRPG-Monster5Speed
	   4050:DynRPG-Monster6Speed
	   4051:DynRPG-Monster7Speed
	   4052:DynRPG-Monster8Speed

12. Change "DefaultHeroSpeed" & "DefaultMonsterSpeed" to the default multiplier value of your choice. I use "3" but you can change this to whichever multiplier works best for you. 
   NOTE: "0" would override the whole formula, and use RM2k3's default ATB speed if you wish to do so
   EXAMPLE: Say you have a menu that has "Battle Speed" from 1-5 where 1 is slowest and 5 is fastest. Using this plugin, you can scale the battle speed to something that feels right to you for each of those settings, and use the DefaultHeroSpeed/DefaultMonsterSpeed variable in the menu itself.
   
13. Set "ActiveSpeed" to a value less than or equal to 100 (100 is rm23k's default speed). This will change the overall speed.

14. Set "WaitSpeed" to a value other than 0 if desired.

15. Set "FreezeSwitch" to a Switch ID of your choice. When turned on, this will freeze the battle until the switch has been turned off again.

16. Set "ConditionExceptions" to the condition IDs that are set to "No Action Allowed", separated by commas (example: CondtionException=7,8,12,13). When a party member becomes afflicted with one of these, their ATB bar will be reset to 0 (as it's frozen) and will not increment whatsoever.


Instructions
-------------
This plugin takes three commands:
	@init_hero_speed: 
	    Reinitializes the 4 hero variables to the value of the Master Hero Variable
		(this is done automatically at the start of battle)
	
	@init_monster_speed: 
	    Reinitializes the 8 hero variables to the value of the Master Hero Variable 
	    (regardless of how many monsters there	are, since it doesn't matter)
		(this is done automatically at the start of battle)
		
	@condition_speed_check p1, p2, p3, optionalText
		p1: Condition ID
		p2: Altered hero speed value
		p3: Altered monster speed value
		optionalText: This can be anything and has no meaning other than to tell you what condition is being checked
	    Using the technique documented below, this will check for a specific condition (p1) and if a hero/monster has that condition, their speed will be altered to hero's value (p2) & monster's value (p3) respectively. You can add text after the 3rd parameter for easy reference to the condition you're checking for. (example: @condition_speed_check 5, 10, 10, BERSERK) would set the hero's SpeedVar & monster's SpeedVar to 10 if they have condition 5 (Berserk in my case).
		
	@halt_atb:
		If in Wait mode, sets ATB to value of WaitSpeed in DynRPG.ini. If in Active mode, sets ATB to ActiveSpeed. This allows you to pause the ATB for custom skill events.
		
	@resume_atb:
		If the ATB is halted via "halt_atb," this resumes it to its default of "100."

TO ADD EASY CONDITION SPEED MANAGEMENT (recommended):
1. Create 2 additional variables (from the 14 requires by this plugin), call them something like "CondSpeed-Hero" and "CondSpeed-Monster"

2. Create a new Common Event called BATTLE-CondSpeeds (can be anything) & add the following (in this order):
   <>Comment: 
   <>Comment: ***LOWER PRIORITY CONDITIONS FIRST***
   ------ 
   <>Variable Oper: [CondSpeed-Hero] Set, Var [HeroSpeedMasterVar]'s Value
   <>Variable Oper: [CondSpeed-Hero] * #
		(This can be any operation. Multiply by a negative number to make the ATB bar go slower.)
   <>Variable Oper: [CondSpeed-Monster] Set, Var [MonsterSpeedMasterVar]'s Value
   <>Variable Oper: [CondSpeed-Monster] * #
   <>Comment: @condition_speed_check 3, V###1, V###2, CONDITION
		(Where V###1 = CondSpeed-Hero & V###2 = CondSpeed-Monster)
   -------
   Repeat the 5 lines above for each condition, with lower priorities first, and higher priorities 2nd. This technique is a tad more complex than the previous condition_speed_check example, but it basically does the same thing, only it ensures the modified condition is relative to the current SpeedVar value (again, if you have a "Battle Speed" option in a menu somewhere)
   

3. In your Monster Groups, create two new pages with the following:
   TRIGGER: Turns Elapsed [0] (first turn)
   <>Call Common Event: BATTLE-CondSpeeds
   
   TRIGGER: Turns Elapsed [1x+1] (every turn after the first one)
   <>Call Common Event: BATTLE-CondSpeeds
   
4. Copy & Paste those pages into all of your battle events. This will run that common event at the start of every turn (it's very frequent) and set speeds accordingly. If you need to make changes from there, you'll need to edit that common event or develop your own technique!
