========================================================================
CMS Tools: Quit Switch v1.0
For RPG Maker 2003 with DynRPG v0.13 or higher
By PepsiOtaku
========================================================================

This plugin overrides the default "Quit" command in the main menu and turns on a switch. This allows
you to design a custom menu via common event, and go to it directly from the main menu, the same way
Cherry's CustomSaveLoad patch does with the "Save" menu.


Installation
-------------

To install the plugin, make sure that you have patched your project with Cherry's DynRPG patch which
can be found here: http://cherrytree.at/dynrpg

1. Copy the "quit_switch.dll"into the DynPlugins folder of your own project.

2. Add the following (between the asterisks) to your DynRPG.ini 

**********************************************

[quit_switch]
QuitSwitch=4025


**********************************************

3. Change the numeric value "4025" to the switch of your choice. 



Instructions
-------------
1. Go to Database > String > Page 5 and change "Quit" to the name of the menu you want to make.
   In Everlasting Journey (rpgmaker.net/games/20), I changed this to "System" so I could make a custom
   system menu that not only quits the game, but can change settings like the battle speed, walk/run
   settings, and text speed. 

2. Go into your Common Events, and create a new one with the Trigger Switch set to your "QuitSwitch" in
   the DynRPG.ini (4025 in my example). Set your Trigger to "Autostart" and add the following commands:
**********************************************
<>Show Screen: Instant
<>Message: Hello World!
<>Switch Operation: [4025:QuitSwitch] OFF
<>Open Main Menu
**********************************************

This will get you to your custom menu from the main menu, and back to the menu. From there, design your menu!
Be sure to use pictures & labels to display your menu portions and labels to loop the user around the menu
functions
