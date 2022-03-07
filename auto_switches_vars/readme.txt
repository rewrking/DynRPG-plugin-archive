========================================================================
Auto Switches v2.0
For RPG Maker 2003 with DynRPG v0.20 or higher
By PepsiOtaku
========================================================================

This plugin allows for auto-switches by event # & page #, meaning you can add things like chests & 
searchable pots without using precious switches. Additionally, if you wanted to give something 
different search states (searched more than once) you can just add more pages.

These are stored in your SaveXX.dyn files and require no additional setup.

Custom variable importing/exporting has been removed in this version, but I might add it back in some way in a later release.

Installation
-------------

To install the plugin, make sure that you have patched your project with cherry's DynRPG patch which
can be found here: http://cherrytree.at/dynrpg

1. Copy the "auto_swithes_vars.dll" into the DynPlugins folder of your own project.

2. Add the following (between the asterisks) to your DynRPG.ini 

**********************************************

[auto_switches_vars]
MasterSwitch=4041

**********************************************

3. "MasterSwitch" will be the Switch ID that is set to yes/no based on the saved state of the event/page.


Commands
--------

Supports two commands, documented below:

@export_event_state p1
 - Exports the state based on the map ID, event & page #
    p1: If set to "0" then, the master switch will be set to OFF (resetting that event)

@import_event_state
 - Checks the state of the map ID, event & page # and passes it to "MasterSwitch"
    -If it doesn't exist yet, the master switch is turned OFF
    -If it does exist, the master switch is turned ON


Instructions
------------

To use @import_event_state and @export_event state, create an event on a map of your choice & add the following:

(This is just a simple example)
<>Comment: @import_event_state
<>Branch if Switch [XXXX:DynRPG-AutoSwMaster] is OFF
  <>Call Event: RandomLoot --- Common event that gives random loot
  <>Comment: @export_event_state
  <>
: Else Handler
  <>Call Event: SeenAlready --- Common event for when a chest has already been seen.
  <>
: End


You can potentially add this same code on multiple pages, and the plugin will make/get a different state for every page based on whatever other page conditions you set.

See the included test project for in-game examples!

