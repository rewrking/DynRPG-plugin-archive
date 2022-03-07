========================================================================
CMS Tools: Save Detector & Delete Save function v1.0
For RPG Maker 2003 with DynRPG v0.13 or higher
By PepsiOtaku
========================================================================

Save Detector
-------------
This plugin should be used in conjunction with BetterAEP (Auto Enter Patch) found here: 
http://cherrytree.at/cms/lang/en/download/?did=17

To install with DynRPG, place the BetterAEP RPG Maker 2003 RPG_RT.exe in your folder first, 
then run the DynRPG patcher.

This patch detects if you have any save games present in your game directory, and is specfically
used for your custom title screen. If there are saves present, switch will be turned ON.
If there are no saves, it will be turned OFF.

Delete Save function
--------------------
This plugin combines my earlier "Save Detector" plugin with a function to delete save files by setting
a variable to the Save's ID. After it deletes a save file, it automatically runs a check to see if all
of the saves have been removed, and changes the save detector switch accordingly.



Installation
-------------

To install the plugin, make sure that you have patched your project with cherry's DynRPG patch which
can be found here: http://cherrytree.at/dynrpg

1. Copy the "save_delete_and_detector.dll"into the DynPlugins folder of your own project.

2. Add the following (between the asterisks) to your DynRPG.ini 

**********************************************

[save_delete_and_detector]
SaveDetectorSwitch=4005
SaveDetectorCheckSwitch=4009
DeleteSaveVar=4002

**********************************************

3. Change the numeric value 4005 & 4009 to the switches of your choice. 

4. Change the numeric value 4002 to the variable of your choice.


Instructions
-------------
In your custom title screen map/common event, create a conditional branch that states IF SWITCH 4005
is ON, run title screen conditions (like pictures and menu commands) for when there are saves 
present, ELSE, run title screen conditions for when there are no saves.

An example use would be if you wanted "Continue/Load" to be grayed out when there are no save
games present.

Another example would be to create some kind of intro if you are opening the game for the first
time, or if there is a save present, go right to the title screen instead.

To use the delete save function, create a Common Event called "CallDeleteGame" set to "Call" and
add the following:

<>Variable Oper: [4002:DynRPG-DeleteFile] Set, ##

Or, set it to the value of another variable (so you can build it into your menu)

When this function is called, the plugin will delete both the .lsd and .dyn files without any
notification. You must build the notification into your menu yourself.

