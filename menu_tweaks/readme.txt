========================================================================
CMS Tools: Menu Transition Tweaks v1.0
For RPG Maker 2003 with DynRPG v0.13 or higher
By PepsiOtaku
========================================================================

When the menu goes from Save/Order/Quit to a Switch ON state using one of the other CMS Tools
plugins, there was a transition bug that showed the screen before the Switch ON event could act. This makes
this transition "Hide Screen" when you go to the Save/Order/Quit command, allowing the developer to
manually control the transition via a "Show Screen" command. The recommended use is to initialize
all of your images (Show Picture), and then show the screen.


Installation
-------------

To install the plugin, make sure that you have patched your project with Cherry's DynRPG patch which
can be found here: http://cherrytree.at/dynrpg

1. Copy the "menu_tweaks.dll"into the DynPlugins folder of your own project.


Instructions
-------------

In your custom Save/Order/Quit screen, after image initialization, add a "Show Screen:Instant" command.
This will create a smooth transition from the main menu to your custom menu.

