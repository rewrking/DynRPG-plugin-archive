========================================================================
System: Display Options v1.1
For RPG Maker 2003 with DynRPG v0.20 or higher
By PepsiOtaku
========================================================================

This plugin enables RPG_RT.ini settings like starting in a window or fullscreen, and 
enables Cherry's "AnotherFullscreenMode" tool, with in-game controls for all.

With it, you can create a "Display Settings" menu in-game with several options, and the ability
to add your own default ini settings of any kind that the user can change easily if they wish

v1.1: Fixed a bug with the AfmFolder definition.


Installation
-------------

To install the plugin, make sure that you have patched your project with cherry's DynRPG patch which
can be found here: 
http://share.cherrytree.at/showfile-12494/dynrpg.rar (Link for v0.20)
http://cherrytree.at/dynrpg

1. Copy the DynPlugins folder into your project. It contains "game_settings.dll" and "game_settings_afm.exe"

2. Add to DynRPG.ini:

[game_settings]
; Sets a new FPS on startup. Leave blank to use default (80)
SetFPS=
; Alternate RPG_RT.exe name to check for during a restart (for Moleboxed games, etc.)
; Example: Game.exe
AlternateExeName=Game.exe
; Folder where game_settings_afm.exe resides (Default: DynPlugins)
AfmFolder=DynPlugins
; Game ini filename 
; Default: Settings.ini
GameIniFilename=Settings.ini

3. Add to Settings.ini:

[Settings]
; if AnotherFullscreenMode=1 & StarWindowed=1, it must boot into fullscreen mode briefly
; 0=No, 1=Yes
StartWindowed=0
; AnotherFullscreenMode: An experimental screen mode created by Cherry
; It allows for scale2x and hq2x filtering
; Unfortunately, it causes a drop in framerate
; 0=No, 1=Yes
AnotherFullscreenMode=0
; Render Mode: 0=No filtering (Not recommended), 1=scale2x, 2=hq2x
RenderMode=1
; Horizontal & Vertical screen resolutions ONLY in AnotherFullscreenMode
; This is necessary since it stretches to whatever the screen resolution is
; Should be 4:3 screen ratio
; Default: 640x480
ResHorizontal=640
ResVertical=480


To differentiate the two, Settings are "safe" changes that the end-user can have access to, 
while DynRPG.ini settings is internal stuff meant for the developer.


Comment Commands/Instructions
=============================

@toggle_fullscreen - Same as the F4 key, only it can be called in-game. Switches between
      fullscreen & windowed. If in "AnotherFullscreenMode," it is equivalent to F6.
  - No parameters

@toggle_window_size - Same as the F5 key, only it can be called in game. If in the normal 
      display mode, this will toggle between the two window sizes. In "AnotherFullscreenMode", 
      this does nothing.
  - No parameters

@toggle_displaymode - If in "AnotherFullscreenMode", this will toggle between Normal rendering
      mode, Scale2x & Hq2x. This is equivalent to F8.
  - No parameters

@force_restart - Restarts RPG_RT.exe. This is needed if you want to switch between Normal/AnotherFullscreenMode       ingame, and should only be used in custom title screens, where data doesn't need to be saved.
  - No parameters

@settings_ini - Performs read/write to the "Settings" section in RPG_RT.ini via comment command.
  - Parameter 1 (text): Ini Key (StartWindowed, AnotherFullscreenMode, RenderMode, ResHorizontal, ResVertical)
  - Parameter 2 (number): Read/Write mode. 0=read, 1=write

  Read Mode (0):
  - Parameter 3 (number): Variable ID to read the value to. You can then use that variable in-game to 
        check for specific settings

  Write Mode (1):
  - Parameter 3 (text): value to save to the ini file. Numbers must be surrounded by quotation marks

Examples:
  @settings_ini "AnotherFullscreenMode", 1, "1"
  - Would set AnotherFullscreenMode to "1", if the value was previously 0, this would turn on AnotherFullscreenMode
    the next time the game is restarted (hence the need for @force_restart)

  @settings_ini "AnotherFullscreenMode", 0, 4024
  - Would read the ini value of AnotherFullscreenMode, and save it to variable 4024


