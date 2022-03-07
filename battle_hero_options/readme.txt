========================================================================
Battle Hero Options v1.0
For RPG Maker 2003 with DynRPG v0.20 or higher
By PepsiOtaku
========================================================================

This plugin allows you to change some previously unchangeable hero options, namely:
Flags:
  Two Weapons
  Lock Equipment
  AI Control
  Mighty Guard
Condition Resistance
Attribute Resistance

These can be changed at any time via comment commands.

Also contained in this plugin is a "ShowDebug" flag you can add to DynRPG.ini that will show you a debug window, and tell you when the above flags/stats are changed since they can be seen in-game otherwise.

Installation
-------------

To install the plugin, make sure that you have patched your project with Cherry's DynRPG patch which
can be found on my site here: http://www.rewking.com/dynrpg

1. Copy the "battle_hero_options.dll" into the DynPlugins folder of your own project.

2. Add the following (between the asterisks) to your DynRPG.ini 

**********************************************

[battle_hero_options]
ShowDebug=true

**********************************************


Comment Commands/Instructions
-----------------------------

@hero_options_set - Sets hero options to a new value (Version for flags)
  - Parameter 1 (number): The ID of the hero
  - Parameter 2 (text): The flag to change (self explanatory)
		- "two_weapons"
		- "lock_equipment"
		- "ai_control"
		- "mighty_guard"
  - Parameter 3 (number): The value to set (1 for "checked", 0 for "unchecked")

@hero_options_set - Sets hero options to a new value (Version for resistances)
  - Parameter 1 (number): The ID of the hero
  - Parameter 2 (text): The resistance type to change (self explanatory)
		- "condition_resist"
		- "attribute_resist"
  - Parameter 3 (number): The resistance database ID to set (Condition/Attribute)
  - Parameter 4 (number or text): The value to set. This can be either textual with quotes ("A", "B", "C", "D", "E") or RM2k3's internal numeric values (0, 1, 2, 3, 4 respectively)

@hero_options_reset_flags - Reset all flags for a particular hero to the database default
  - Parameter 1 (number): The ID of the hero

@hero_options_reset_conditions - Reset all condition resistances for a particular hero to the database default
  - Parameter 1 (number): The ID of the hero

@hero_options_reset_attributes - Reset all attribute resistances for a particular hero to the database default
  - Parameter 1 (number): The ID of the hero


Debug only commands:
@hero_options_print_flags - Print the currently set flags for a particular hero
  - Parameter 1 (number): The ID of the hero

@hero_options_print_conditions - Print the currently set condition resistances for a particular hero
  - Parameter 1 (number): The ID of the hero

@hero_options_print_attributes - Print the currently set attribute resistances for a particular hero
  - Parameter 1 (number): The ID of the hero
  
Examples
--------

@hero_options_set 3, "two_weapons", 1 - Set "Two Weapons" for hero 3 to "checked"
@hero_options_set 5, "mighty_guard", 0 - Set "Mighty Guard" for hero 5 to "unchecked"
@hero_options_set 2, "attribute_resist", 4, "A" - Set Attribute #4 for hero 2 to "A"
@hero_options_set 2, "attribute_resist", 4, 0   - Set Attribute #4 for hero 2 to "A" (0)
@hero_options_set 7, "condition_resist", 12, 3 - Set Condition #12 for hero 7 to "D" (3)
@hero_options_reset_attributes 4 - Reset all attributes for hero 4 to the database default

@hero_options_print_flags 8 - Prints the following to the debug/console window (if enabled):
-------
Flags for Klaus:
  Two Weapons:    1
  Lock Equipment: 0
  AI Control:     0
  Mighty Guard:   1
-------