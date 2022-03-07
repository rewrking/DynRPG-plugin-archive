========================================================================
Epic Run Key v1.0
For RPG Maker 2003 with DynRPG v0.14a or higher
By PepsiOtaku
========================================================================

This plugin allows you to easily add a run key system to your game, and will automatically change the
hero's charset according to a speed threshold parameter you set. For instance, if you want the walk speed
to be set to "3" and the run speed to "4" Setting the threshold to "4" will use the running charset
when the hero is at speed 4. 

The speed value is equal to the movement frequency:
  1. One-Eighth Normal
  2. One-Fourth Normal
  3. Half Normal
  4. Normal
  5. Twice Normal
  6. Four Times Normal


Installation
-------------

To install the plugin, make sure that you have patched your project with cherry's DynRPG patch which
can be found here: http://cherrytree.at/dynrpg

1. Copy the "epic_run_key.dll" into the DynPlugins folder of your own project.

2. Add the following (between the asterisks) to your DynRPG.ini

**********************************************

[epic_run_key]
ChangeCharset=true

**********************************************

3. Change the value of "ChangeCharset" to either true or false depending on if you want the charset to change.

4. If the above is "true" Make a copy of your hero's charset, and add "-run" to the end of it. 
   ("hero1" would become "hero1-run")

5. Edit your new run charset accordingly.


Instructions
-------------
This plugin takes two commands:
  @run_key - sets a run key
  @run_key_off - turns the run key off, and resets the charset

@run_key takes 5 parameters:
  Parameter 1: The keycode value to use for your Run key. See "epic_run_key_keycodes.txt" for a full list
  Parameter 2: The Movement Frequency Value for "Walk" (where no key is pressed) 
  Parameter 3: The Movement Frequency value for "Run" (where the key in parameter 1 is pressed)
  Parameter 4: The Switch value that needs to be ON in order for the run key to work
  Parameter 5: The Movement Frequency threshold required to change the charset. (would have no effect if ChangeCharset=false)

@run_key_off takes 1 parameter:
  Parameter 1: The Movement Frequency value to be forced back to. This will also reset the charset (if ChangeCharset=true)

So if you wanted to set your run key to "A" (keycode of 65) with a walk value of 3, a run value of 4, a switch value of 4951, 
and a threshold of 4, your comment command would be:

  @run_key 65, 3, 4, 4951, 4

To get this working, you need to add it to a parallel process event. Go into your comment events, create a new one with
the Trigger Switch set to the switch value you want to use (4951 in my example), add that comment command, followed by 
a "Wait" command so the plugin doesn't get called too often. (See the included image)

Then, you can create another common event with a "Call" trigger (and no switch) that will use "@run_key_off 3" to 
reset the hero's speed.


IMPORTANT: To use this in practice, turn ON your run switch when you give the player control of the hero, and 
keep it OFF during cutscenes or any time you need to use a hero charset other than the default. If you change the 
hero set, and then call the plugin, it will look for the filename of that charset with "-run" at the end, which 
could crash RPG_RT.exe if the file doesn't exist (just like any time an event references a file that does not exist).


