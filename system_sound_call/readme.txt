========================================================================
System/Custom Sound & Music Player v1.0
For RPG Maker 2003 with DynRPG v0.14a or higher
By PepsiOtaku
========================================================================

This plugin calls system sound effects and music from any event script via comment command. You can also set your own
custom se/bgm assignments via DynRPG.ini and call them, along with any of the usual parameters allowed.



Installation
-------------

To install the plugin, make sure that you have patched your project with cherry's DynRPG patch which
can be found here: http://cherrytree.at/dynrpg

1. Copy the "system_sound_call.dll" into the DynPlugins folder of your own project.

2. Add the following (between the asterisks) to your DynRPG.ini 

**********************************************

[se_custom]
test=monster1

[bgm_custom]
test=canyon

**********************************************

3. Change the value before the "=" to the name you want to assign your se/bgm to. 

4. Change the value after the "=" to the filename of your se/bgm, WITHOUT the file extension (canyon.mid would
   be "canyon").


Instructions
-------------
Commands are controlled via event comments with a "@" prefix. 

This is a list of the default commands (names should be pretty self-explanitory):

**************
  se_cursor
  se_decision / se_choice
  se_cancel
  se_buzzer
  se_battle_start
  se_flee
  se_enemy_attack
  se_enemy_damage
  se_hero_damage
  se_evasion
  se_enemy_death
  se_item_used

  bgm_title
  bgm_battle
  bgm_victory
  bgm_inn
  bgm_skiff
  bgm_ship
  bgm_airship
  bgm_game_over

**************


They do not take any additional parameters, therefor, to call the cursor sound effect, you would add a comment 
with "@se_cursor" in your event script.

Custom sound & music assignments work differently. They use the following commands:

**************
  se_custom
  bgm_custom

**************

First, define your custom se/bgm in DynRPG.ini. For sounds, use the following command:

    @se_custom "test"

This would play the "monster1" sound effect with the default parameters. (volume of 100, tempo of 100, balance of 50). To set custom parameters, simply define them in the order you see them in rm2k3 after the sound name separated by commas.

    @se_custom "test", 90, 150, 50

This would play "monster1" with a volume of 90, tempo of 150, and a balance of 50.


Music is the same way, but takes a "Fade" parameter first (in seconds).

    @bgm_custom "test", 5, 90, 100, 50

This would play canyon.mid with a fade of 5 seconds, volume of 90, tempo of 100, and a balance of 50.

Parameter Min/Max values:
  Fade: 0 to 10 
  Volume: 0 to 100
  Tempo: 50 to 150
  Balance: 0 to 100

Finally, if the plugin doesn't recognize the custom sound command, it will play the default Buzzer sound effect. For music, it will play the default battle theme.
