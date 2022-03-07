XInput/Xbox 360 Controller Integration
======================================
v1.2
For RPG Maker 2003 with DynRPG v0.20 or higher
By PepsiOtaku


This plugin enables full support for Xinput-based controllers, including the Xbox 360 controller family (guitars, drums, dance pads, etc).
Wireless controllers require the Xbox 360 Wireless Gaming Receiver for Windows
	http://www.amazon.com/Xbox-360-Wireless-Gaming-Receiver-Windows/dp/B000HZFCT2/

Wired controllers work as-is assuming you have the drivers installed. They are found here:
	http://www.microsoft.com/hardware/en-us/d/xbox-360-wireless-controller-for-windows

This plugin supports key-bindings via virtual keycodes set in DynRPG.ini. See virtual_keycodes.txt for a full list of values.
It also has full rumble support, set via comment command, with numerous settings. See Installation section below for more details
about the keybindings.

Also, the Guide button is SUPPORTED. Microsoft doesn't allow for this out of the box, but there are ways to circumvent that.
However, it is recommended to disable Microsoft's "XboxStat.exe" process (battery popup) in the task manager to remove any conflicts
between the key binding you define, and the battery popup.
You can also disable it completely via msconfig (Start > Run > "msconfig" > Startup Tab > Uncheck XboxStat.exe). I'm working on a better solution for a future version of this plugin. You can also choose not to set any keybindings for it.

The Guide button also integrates with my Game Jolt (www.gamejolt.com) plugin as its default value to call the game jolt menu
is set to Shift-Tab. In that menu, you'll see achivements & leaderboards (like Steam or Google Play).
As of 3/4/15, the plugin is not yet released, but is VERY close. I just need to fix one bug and do some beta testing for it. Stay tuned!

NOTE: Xbox One controllers do not work with windows yet. If/when they do, I'll look into supporting them.


Changelog
---------

1.2 - Fixed some bugs with Analog stick mapping, added Analog axis output to variables (works just like the trigger axis)
1.1 - Added onDrawScreen handling for input as well, for future plugins that use scene numbers greater than 8
1.0 - First release

Installation
-------------

To install the plugin, make sure that you have patched your project with Cherry's DynRPG patch which
can be found here: http://share.cherrytree.at/showfile-12494/dynrpg.rar (v0.20)
Additional Information:
	http://cherrytree.at/dynrpg

1. Purchase a wired Xbox 360 controller, or the wireless gaming receiver for windows with wireless xbox 360 controller.

2. Install the drivers obtained via MS's website.

3. Copy the "xbox_controller.dll" into the DynPlugins folder of your project.

4. Add the following (between the asterisks) to your DynRPG.ini

**********************************************

[xbox_controller]
; Note: Supports all Wired & Wireless controllers
;   Wireless controllers require the "Wireless Gaming Receiver for Windows"
;   and drivers should be installed obviously...
; =========================================
; Switch to use for the plugin to tell RPG Maker if a controller is plugged in and detected
; Usage: Use @xbox_controller_check to check if a controller is plugged in and update the RM2k3 switch
XboxControllerSwitch=4057
; ============Force Feedback===============
; In any comment parameters related to time (Rumble Timer, Rumble Fade Out/In),
;   this is the frame multiplier (Default=60, since 2k3 runs at 60fps)
;   and also the minimum amount of frames the rumble should last for.
; 60 = Full second, 30 = Half second, etc.
TimeMultiplier=60
; Battle Events to rumble for.
; Scenarios: When a hero is hit by an attack, or by a spell
BattleRumbleEvents=true
; Same as TimeMultiplier, but for BattleRumbleEvents (Default=30)
; This is not adjustable within the maker.
; When a hero is attacked, the rumble lasts for BattleTimeMultiplier*1, and
;   the Rumble for spells lasts for BattleTimeMultiplier*3
BattleTimeMultiplier=30
; Game ini filename (For Rumble On/Off feature)
; Default: Settings.ini
GameIniFilename=Settings.ini
; =============Key Assignments===============
; Set any of the following with default mapping to "0" to remove mapping entirely for that button
; Set it to blank (ie. "XboxA=") to use the default
; Left analog stick and D-Pad are mapped to the arrow keys by default.
; Set SeparateDpadStick=true to map each one separately, otherwise, leave it set to false.
SeparateDpadStick=false
; ----------D-Pad-----------
; D-Pad Default = Mapped to Arrow Keys
XboxDpadUp=
XboxDpadDown=
XboxDpadLeft=
XboxDpadRight=
; -----Left analog stick to keyboard key----
; Fill out only if SeparateDpadStick=true, otherwise leave blank
XboxLStickUp=
XboxLStickDown=
XboxLStickLeft=
XboxLStickRight=
; -----Right analog stick to keyboard key----
XboxRStickUp=
XboxRStickDown=
XboxRStickLeft=
XboxRStickRight=
; ---------Triggers----------
; Xbox Trigger values get sent to a variable. Define it below
; If the variable is between -1000 & -1, the Left Trigger is held down. -1000 means the
;   trigger is pressed down all the way
; If the variable is between 1 & 1000, the Right Trigger is held down. 1000 means the trigger
;   is pressed down all the way
; Sensitivity can be changed in your event scripting by detecting values closer to 0 and
;   greater/less than depending on the trigger
; The variable will reset to 0 if the triggers are not held down
XboxTriggerAxisVar=
; Mapping to variables for the Analog sticks
; Each one has an X axis and a Y axis. If the value is negative, the stick is left or up
; The value is going to vary based on where the stick is.
; If you need to check for both axis (example: holding down-right), check for values greater
;   than 500 or 600, because the stick will not be all the way to the edge (1000).
; Imagine it like a circle inside of a square, with its 4 quadrants. The Axis will not be
;   outside of the circle.
; Set XboxLStickAxis or XboxRStickAxis to true to map the Left or Right sticks to a variable
;   These flags disable all Stick to key mapping above
; The variables will reset to 0 if the analog sticks are not held down
; -----Left analog stick axis to variable----
XboxLStickAxis=false
XboxLStickAxisX=
XboxLStickAxisY=
; -----Right analog stick axis to variable----
XboxRStickAxis=false
XboxRStickAxisX=
XboxRStickAxisY=
; XboxA Default = Decision (Enter,Z,Space)
XboxA=
; XboxB Default = Cancel (Esc,X)
XboxB=
; XboxX Default = Shift
XboxX=
XboxY=
; XboxLB Default = Shift
XboxLB=
; XboxRB Default = Shift
XboxRB=
XboxLThumb=
XboxRThumb=
; XboxStart Default = Cancel (Esc,X)
XboxStart=
; XboxBack Default = Switches/Variables in Test Play (F9)
XboxBack=
; XboxGuide Default = Shift+Tab
; It is recommended to disable Microsoft's "XboxStat.exe" process (battery popup) in the task
;   manager to remove any conflicts
; You can also disable it completely via msconfig
XboxGuide=

**********************************************

5. Add the following (between the asterisks) to your Settings.ini (User settings)
	If it does not exist, create one in your games root directory, and add "[Settings]" to the first line

**********************************************

; =============XInput=============
; If using the Xbox 360 Controller, turns the rumble On or Off
RumbleOn=1
;

**********************************************

6. Read the notes and change any settings you desire, but it's recommended to at least test it first!

NOTE: If you get an error about "XINPUT1_3.DLL" not being found at game's startup, simply install DirectX 9.0c or later.

NOTE 2: This plugin automatically disables RM2k3's native joystick support, so you'll have no conflicts.


Commands
--------
Supports 7 different commands, documented below

@xbox_rumble p1, p2
@xbox_rumble p1, p2, p3, p4
@xbox_rumble p1, p2, p3, p4, p5, p6
@xbox_rumble p1, p2, p3, p4, p5, p6, p7, p8
@xbox_rumble p1, p2, p3, p4, p5, p6, p7, p8, p9
 - Enables a controller rumble
	p1: left motor strength (% from 0 to 100)
	p2: right motor strength (% from 0 to 100)
	p3: left motor duration (x*TimeMultiplier frames)
	p4: right motor duration
	p5: left motor fade out time
	p6: right motor fade out time
	p7: left motor fade in time
	p8: right motor fade in time
	p9: rumble delay
	note: All time-related parameters are based on the TimeMultiplier setting. If set to 60, "1" is a second. If set to 30, "1" is a half-second, etc. See ini documentation

	examples: @xbox_rumble 30, 50, 2, 2, 1, 1, 3, 3, 5 - Rumbles with left motor strength set to 30%, right to 50%, fades outs to 0% for 2*TimeMultiplier frames long, lasts for 1*TimeMultiplier frames, and then fades out for 3*TimeMultiplier frames BUT starts entire process after a 5*TimeMultipler frame delay. See parameter patterns above for the allowed set of parameters


@xbox_rumble_off
 - Turns rumble off regardless of rumble settings.

@xbox_controller_check
 - Checks whether a controller is plugged in, and passes the value to a switch (for conditional branching)
	no params: Uses the switch ID set in "XboxControllerSwitch" within DynRPG.ini
@xbox_controller_check p1
	p1: switch ID to send the controller's state to. ON = controller is ON and detected, OFF = controller is OFF or not detected.

@get_controller_type p1
 - Gets the controller's type and passes it to a variable (for conditional branching)
	p1: variable to pass the controller's type to
	values:
		-1 - Unknown, or no controller
		 1 - Gamepad
		 2 - Wheel
		 3 - Arcade Stick
		 4 - Flight Stick
		 5 - Dance Pad
		 6 - Guitar
		 7 - Guitar Alt (??)
		 8 - Drum Kit
		11 - Bass Guitar
		18 - Arcade Pad (??)

@get_battery_type p1
 - Gets the battery type and passes it to a variable (for conditional branching)
	p1: Variable to pass the battery type to
	values:
		 -1 - Disconnected
		  1 - Wired
		  2 - Alkaline Batteries (AA's)
		  3 - NIMH Batteries (Rechargeable)
		255 - Unknown

@get_battery_level p1
 - Gets the battery level and passes it to a variable (for conditional branching)
	p1: Variable to pass the battery level to
	values:
		 -1 - Empty (Controller would also be shut off technically)
		  1 - Low
		  2 - Medium
		  3 - Full


@settings_ini_xbox p1, p2, p3
@settings_ini_xbox p1, p2, p3, p4
 - Adds a user-controlled setting to turn the rumble feature on or off. If off, any @xbox_rumble requestes will do nothing
	p1: ini key name. Set to "RumbleOn" since that's the only one supported at the moment
	p2: 1 for write mode, 0 for read mode
	p3: switch ID, or ON flag. If in write mode, the only value this takes is "1" WITH quotes. If in

	examples: @settings_ini_xbox "RumbleOn", 0, 4057 - Reads from the INI. If RumbleOn=1, switch 4057 is turned ON
			  @settings_ini_xbox "RumbleOn", 1, "0" - Writes RumbleOn=0 to INI.
			  @settings_ini_xbox "RumbleOn", 1, "1" - Writes RumbleOn=1 to INI.
			  @settings_ini_xbox "RumbleOn", 1, "0", 4057 - Writes RumbleOn=0 to INI and sets switch 4057 to OFF.
			  @settings_ini_xbox "RumbleOn", 1, "1", 4057 - Writes RumbleOn=1 to INI and sets switch 4057 to ON.

	note: for other Settings.ini uses, see System Display Options plugin here: https://github.com/rewrking/game_settings