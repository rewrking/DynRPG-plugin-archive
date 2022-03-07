========================================================================
Battle Layout Changer v2.0
For RPG Maker 2003 with DynRPG v0.13 or higher
By PepsiOtaku
========================================================================

This plugin allows you to change the System2 set & Battle Layout setting (Traditional/Alternative/Gauge) by 
setting a variable for either, and setting Large/Short Windows & Window Transparency by switch!

New to v2.0: 
The plugin now keeps track of the default settings stored in the database and compares those values with the
variable/switch values stored in the save file and loads the settings accordingly. This makes for seemless
changing of battle layout settings between save files!


Installation
-------------

To install the plugin, make sure that you have patched your project with cherry's DynRPG patch which
can be found here: http://cherrytree.at/dynrpg

1. Copy the "battle_layout_changer.dll"into the DynPlugins folder of your own project.

2. Add the following (between the asterisks) to your DynRPG.ini 

**********************************************

[battle_layout_changer]
Sys2TriggerVar=4013
BattleLayoutVar=4014
LargeWindowSwitch=4034
TransparencySwitch=4035
Sys2Default=System2\EJsystem-alttrans.png
Sys2Image1=System2\EJsystem-gauge.png

**********************************************

3. Set the "Sys2TriggerVar" value to the variable of your choice. This variable will determine which 
   system2 set to use. 
      Set to "0" = The default system2 defined in "Sys2Default" will be used.
      Set to "#" = The system2 defined in "Sys2Image#" will be used. (Change "#' to the number of your choice)

4. Set the "BattleLayoutVar" value to the variable of your choice. This variable will determine whether to
   use Traditional/Alternative/Gauge battle layouts. The values are hard-coded to the following:
      Set to "1" = Traditional
      Set to "2" = Alternative
      Set to "3" = Gauge

5. Set the "LargeWindowSwitch" value to the switch of your choice. This will determine whether to use the
   large battle window or small.
      Set to "ON" = Large Window
      Set to "OFF" = Small Window

6. Set the "TransparencySwitch" value to the switch of your choice. This will determine whether to use
   transparent windows or not.
      Set to "ON" = Transparent
      Set to "OFF" = Opaque



Instructions
-------------
All of these options can be updated on the fly (even from battle), so simply set the variables/switches to the
layout you want to see. 

