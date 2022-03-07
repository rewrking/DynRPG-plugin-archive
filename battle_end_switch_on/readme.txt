========================================================================
Battle End Switch On v1.0
For RPG Maker 2003 with DynRPG v0.20 or higher
By PepsiOtaku
========================================================================

This plugin turns on a switch when the menu opens.


Installation
-------------
To install the plugin, make sure that you have patched your project with cherry's DynRPG patch which can be found here:
http://share.cherrytree.at/showfile-12494/dynrpg.rar (Link for v0.20)
http://cherrytree.at/dynrpg

1. Copy the "battle_end_switch_on.dll"into the DynPlugins folder of your own project.

2. Add the following (between the asterisks) to your DynRPG.ini:

**********************************************

[battle_end_switch_on]
BattleEndSwitch=4049

**********************************************

3. Change BattleEndSwitch to the switch ID of your choice.



Instructions
-------------
1. Create a common event (or map event) set to Auto Start or Parallel Process with the Trigger Switch
set to your BattleEndSwitch.

2. Add a "hello world" message box, or your event code.

3. Turn the switch off at the end of the event (if applicable). This can be turned off any other way
you desire too.