========================================================================
MP/Stat Popups in Battle v5.0
For RPG Maker 2003 with DynRPG v0.13 or higher
By PepsiOtaku
========================================================================

This plugin displays MP in battle after MP has been healed or used, and also displays when stats are altered. 
It supports both heros and monsters in any number of either.

Stats display in the following format (using the default color 0):

+34 DEF
-20 AGL


Installation
-------------

To install the plugin, make sure that you have patched your project with cherry's DynRPG patch which
can be found here: http://cherrytree.at/dynrpg

1. Copy the "battle_mp_display.dll" into the DynPlugins folder of your own project.

2. Add the following (between the asterisks) to your DynRPG.ini 

**********************************************

[battle_mp_display]
ColorMpPlus=13
ColorMpMinus=11
ShowMpPlus=true
ShowMpMinus=true
MonMpPlus=true
MonMpMinus=true
StatsPlus=true
StatsMinus=true
AbbrAtk=ATK
AbbrDef=DEF
AbbrInt=INT
AbbrAgl=SPD

**********************************************

3. Set the "ColorMpPlus" value to the color of your choice, for when MP is added. This must be a value 
   between 0 and 19.

4. Set the "ColorMpMinus" value to the color of your choice, for when MP is subtracted. This must be a value 
   between 0 and 19.

5. Set the "ShowMpPlus" value to false to not show when MP is added.

6. Set the "ShowMpMinus" value to false to not show when MP is subtracted.

7. Set the "MonMpPlus" value to false to not show when monster's MP is been added.

8. Set the "MonMpMinus" value to false to not show when monster's MP is been subtracted.

9. Set the "StatsPlus" value to false to not show when stats are added to monsters/party members.

10.Set the "StatsMinus" value to false to not show when stats are subtracted to monsters/party members.

11. Set the AbbrAtk/AbbrDef/AbbrInt/AbbrAgl to the vocabulary values of your game for each of those stats.




Instructions
-------------
Use an MP healing spell/item or to see the MP popup, or use a stat altering spell to see your stat popups.

