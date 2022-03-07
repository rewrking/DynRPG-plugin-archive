========================================================================
Game Jolt Integration v1.32
For RPG Maker 2003 with DynRPG v0.20 or higher
By PepsiOtaku
========================================================================

Demonstration: https://www.youtube.com/watch?v=Mo39ZkTiApk&hd=1

This plugin integrates with a gamejolt.com game profile to show trophies and multiple leaderboards. Once it's been setup by the game developer, it's very user friendly towards the player and allows them to login with a gamejolt ID and token (a "disposable" password) from within the in-game menu. The login info is saved in %AppData%\rpg2003\GameJolt.ini, and loaded across multiple games that use this plugin. Future sessions therefor automatically log in. Trophies and leaderboards will not work if a user is not logged in.

By default, sessions login at the title screen and show a "toast" message with either the user that has logged in, or "Press Shift+Tab to log in", but you can disable it and call it via @gamejolt_login_toast if you want it to display at certain times (example: if you have a custom title screen/intro)

Use @gamejolt_award_trophy to award a user with a trophy and show a popup. 

Use @gamejolt_award_score to add a score to a particular leaderboard. This does not show anything on-screen, but the leaderboard will be updated with it.


You can also choose to disable the trophies or leaderboards menus if you don't want to use one of them. The plugin also supports different color schemes for the UI elements and a customizable background color.

Leaderboards pull a maximum of 100 scores per leaderboard (gamejolt.com limitation), but you can set an alternative max scores value if you want less than that.

Changelog
---------
1.32 - Limited the Game Jolt menu to only display in Scenes 0-29 (See RPG::Scene object)
1.31 - Fixed a small but gross bug with saving the user/token to the %AppData%\rpg2003\GameJolt.ini file. PLEASE UPDATE
1.3 - Added server error messages (wrong user/token, connection failures, etc) & changed [root]\Settings.ini to an automatically created %AppData%\rpg2003\GameJolt.ini in order to be used per windows user account and across multiple RM2k3/DynRPG/GameJolt games. :D
1.2 - Tokens (passwords that can be used in games) now get obfuscated by asterisks (****) when being entered. To-do in a future update: Add some kind of encryption when it's stored in Settings.ini. At the moment, I don't know jack about that stuff. :)
1.1 - Fixed a bug where if the GJ menu is called at the very end of battle, it could trigger the battle to restart (wtfomg). Some conditions were added to prevent the menu from being called upon a battle victory
1.0 - First release

Installation/Instructions
-------------------------

To install the plugin, make sure that you have patched your project with Cherry's DynRPG patch which can be found here: http://share.cherrytree.at/showfile-12494/dynrpg.rar (v0.20) 
Additional Information:
	http://cherrytree.at/dynrpg

REQUIRED: Microsoft Visual C++ 2013 Redistributable (x86):
	http://www.microsoft.com/en-us/download/details.aspx?id=40784 (vcredist_x86.exe)
	If it's not installed, you'll get an error related to "MSCVR120.dll."

1. Sign up and create a game page on gamejolt.com for your project.

2. Under "Dashboard > Manage Your Games > (Game) > Achievements" you'll find sections for Trophies and High Scores. Create some trophies if you wish, or create some high score tables. Leave the browser window/tab open for some of the ini declarations below.
	
3. Copy the "libcurl.dll" into the main directory folder of your own project.
	
4. Copy the "game_jolt.dll" into the DynPlugins folder of your own project.

5. Add the following (between the asterisks) to your DynRPG.ini 

**********************************************

[game_jolt]
; The name of your game. If left blank, the plugin will use the project name in RM2k3
; This will appear above trophies and leaderboards
GameName=
; Game ID & Private Key (required!!)
GameJoltGameId=
GameJoltPrivateKey=
; Declare trophies here, in the order that they should be shown in
TrophySort=
; Declare secret trophies here
TrophySecret=
; Hide secret trophies from the trophy list?
; If set to true, secret trophies will not appear in the trophy list unless achieved (like Steam)
; If set to false, secret trophies will have a description of "???" and a "?" image
HideSecretTrophies=false
; Declare score tables (leaderboards) here
ScoreTables=
; Maximum number of scores to show per leaderboard
MaxScores=
; Themes: Jams, Fireside, Fire, Water, Earth, Ice, Honey, SNES, GBOY
; Leave blank for default theme
Theme=
; Background color. Leave any of these blank to use the default
BackgroundRed=
BackgroundGreen=
BackgroundBlue=
; Disable either the Trophies or Leaderboards menus below
; Disable one or the other, or neither. Disabling both would make the plugin kinda useless don'tcha think?
DisableTrophies=false
DisableLeaderboards=false
DisableLoginAtTitle=false

**********************************************

6. Most of the instructions are above. In your browser tab/window that should still be open, you'll see a "Game Info" section on the right. Add the Game ID to "GameJoltGameId" above and the Private Key to "GameJoltPrivateKey"

7. Each of your trophies have a unique ID (Ex: 16115). Under "TrophySort" you must add these all manually in the sort order you want them to be displayed (first value is first, last value is last). Add them with a commma between with NO SPACES (Ex: TrophySort=16115,16116). Include secret trophies here as well, as they still need to be included in the sort. The trophies are counted, and the number of trophies that the player finds are shown in a counter at the top of the list (Ex: 16/50).
	
8. "TrophySecret" is set the same way as TrophySort, but you are defining which trophies are classified as secret. Even though there is a Yes/No field within the GameJolt site that sets this as well, you still need to define them here. If "HideSecretTrophies" is set to false, unachieved secret trophies will show a question mark image and a description of "???". If "HideSecretTrophies" is set to true, unachieved secret trophies will not be displayed at all. Regardless, secret trophies are included in the list's trophy counter. So if you have a list of 20 trophies, where 5 are secret and hidden, the counter will still show "#/20" and not "#/15"

	IMPORTANT: As a player gets trophies, they will be prioritized in the in-game trophy list as follows: Achieved, Unachieved, Secret. So if your sort order is 16115,16116,16117,16118,16119 where 16118 is a secret trophy, and the player gets 16117 & 16119, The trophy list will display in the order: 16117,16119,16115,16116,16118 OR 16117,16119,16115,16116 if you set "HideSecretTrophies" to true

9. Trophy images are NOT pulled directly from your gamejolt.com profile, because they would have to be converted to 256 color and resized to 32x32 (which could produce undesirable results), so you have to create and add them manually. Under your Pictures folder, trophy images should be 32x32 png files with 256 colors and the naming scheme "trophy_#####" where ##### is the trophy's ID. Images are then detected automatically in the trophy list.

10. Leaderboards work the same way as trophies. Each one you create is given an ID, and you must explicitly declare them under "ScoreTables" in the same format (Ex: 45995,45996). Players can switch between leaderboards with the left or right key once in the leaderboard section of the UI.

11. Set "MaxScores" to a value below 100 to only show that many scores. Gamejolt.com limits visible scores to 100 (but higher numbers are still stored), so this plugin has to adhere to that limit as well. However, if you only want to show a top 10 or something, you can define that here, but it affects all leaderboards.

12. Set "Theme to a value of your choice (Ex: Theme=SNES)

13. Set "BackgroundRed," "BackgroundGreen" and "BackgroundBlue" to define a custom background color if you do not like the one included in a particular theme. These values are RGB format, so you must use a value between 0 and 255. If one of the 3 fields is not defined, then the default theme background will still be used.

14. "DisableTrophies" hides the Trophies option from the menu UI, but you can still call it with @gamejolt_show_trophylist

15. "DisableLeaderboards" hides the Trophies option from the menu UI, but you can still call it with @gamejolt_show_leaderboard

16. "DisableLoginAtTitle" should be self-explanitory. It disables the automatic login/popup message at the title screen.

17. You can either leave them blank, so the user enters their info using the UI, or add your user name and token here. The Token is NOT your password. It is a temporary password that you can use in games. Create one if you don't already have one. It's simply under the Status bar after you've logged into the website.
	NOTE: Before releasing your game, be sure to remove your user info from the Settings.ini.

18. You're done! Well, almost. You still need to award your players with trophies and scores! Use the @gamejolt_award_trophy comment command for trophies, and the @gamejolt_award_score to save a score from a variable.


Commands
--------
In your events, create a "Insert Comment" command and use one of the following:
Any numeric parameters can be substituted for "V####" which takes the value of a particular variable

@gamejolt_award_trophy p1
  -Awards the currently logged in user with a trophy
	p1: The trophy ID (numeric)
	example: @gamejolt_award_trophy 16115
	
@gamejolt_award_score p1, p2, p3
@gamejolt_award_score p1, p2, p3 (optional: p4, p5, p6...)
  -Adds a score to a particular leaderboard. Scores take 2 values: A numeric score value (p2), and a string for the score (p3+). The numeric value is what's used to sort the scores, and the string is what is displayed in the leaderboard itself.
	p1: The leaderboard ID (numeric)
	p2: The numeric score (numeric)
	p3: The string value for the score
	~OR~
	p3: The first part of the score string (numeric or string)
	p4: The second part of the score string (numeric or string)
	p5: The third part... (numeric or string)
	p6: The fourth part... (numeric or string)
	etc...
	
	This allows you to create complex string values for your leaderboard. For example, if you want to show both the time played, and the average level of your party.
	
	p3+ also takes two special commands (so far):
		"gj_time" - Converts p2 to a clock format (Ex: 48206 would become "13:23:26"
		"gj_guest" - Instead of the currently logged in user, you can define a user's name as a guest. The user's name will be the next parameter. Use for testing scenarios when you want to see some names on your leaderboard.
		
	examples:
		@gamejolt_award_score 45995, V25, V25 - Adds a score of the value of variable 25 to the leaderboard 45995 for the user logged in. The string value is exactly the same as the numeric value in this case
		@gamejolt_award_score 45995, 48206, "Lvl ", V26, "    ", "gj_time" - If variable 26 is 93, this outputs "Lvl 93    13:23:26" to leaderboard 45995 for the user logged in.
		@gamejolt_award_score 45995, 48206, "gj_guest", "CoolGuy1234", "gj_time" - Outputs "CoolGuy1234 (Guest)" as the user, and "13:23:26" as the score.
		
@gamejolt_login_toast
  -Attempts to log in using the User Name and Token defined in GameJolt.ini, and shows a toast message whether login was successful or not
  
@gamejolt_login_screen
  -Loads the login screen. This is the same as hitting Shift-Tab.
  
@gamejolt_show_trophylist
  -Loads the trophy list.
  
@gamejolt_show_leaderboard
@gamejolt_show_leaderboard p1
  -If no parameters, loads the "primary" trophy list. Use "Make Primary" in the High Scores section of you game's gamejolt page to set a leaderboard as primary. Otherwise, it loads a specific leaderboard
	p1: The leaderboard's ID (Ex: 45995)
  
@gamejolt_is_user_connected p1
  -Checks whether a user is logged in, and sets a switch to ON/OFF. You can then use the switch in a conditional branch.
	p1: The switch ID to pass the value to (numeric)