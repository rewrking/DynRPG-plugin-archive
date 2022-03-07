========================================================================
CMS Tools: Order Switch v1.0
For RPG Maker 2003 with DynRPG v0.13 or higher
By PepsiOtaku
========================================================================

This plugin overrides the default "Order" command in the main menu and turns on a switch. This allows
you to design a custom menu via common event, and go to it directly from the main menu, the same way
Cherry's CustomSaveLoad patch does with the "Save" menu.


Installation
-------------

To install the plugin, make sure that you have patched your project with Cherry's DynRPG patch which
can be found here: http://cherrytree.at/dynrpg

1. Copy the "order_switch.dll"into the DynPlugins folder of your own project.

2. Add the following (between the asterisks) to your DynRPG.ini 

**********************************************

[order_switch]
OrderSwitch=4008


**********************************************

3. Change the numeric value "4008" to the switch of your choice. 



Instructions
-------------
1. Go to Database > String > Page 5 and change "Order" to the name of the menu you want to make.
   In Everlasting Journey (rpgmaker.net/games/20), I use the default "Save" command for the "Party" menu
   so I can disable it when I need to with the enable/disable save menu command. I then use the 
   "Order" command for "Save/Load" since it will always be accessible. 

2. Go into your Common Events, and create a new one with the Trigger Switch set to your "OrderSwitch" in
   the DynRPG.ini (4008 in my example). Set your Trigger to "Autostart" and add the following commands:
**********************************************
<>Show Screen: Instant
<>Message: Hello World!
<>Switch Operation: [4008:OrderSwitch] OFF
<>Open Main Menu
**********************************************

This will get you to your custom menu from the main menu, and back to the menu. From there, design your menu!
Be sure to use pictures & labels to display your menu portions and labels to loop the user around the menu
functions
