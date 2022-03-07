========================================================================
CMS Tools: Hero Rename v1.0
For RPG Maker 2003 with DynRPG v0.20 or higher
By PepsiOtaku
========================================================================

This plugin allows you to extract the name of a hero to a range of variables. Each variable represents the ASCII value of a letter. See the included ASCII table for a list of basic values (32-127). Extended ascii values are also supported, but instead of 128+, they need to be set to -1 to -127ish. You can experiment to find out what the values are. The actual extended ASCII table can be found here: http://www.ascii-code.com/

Additionally, you can set a range of variables to their ascii values manually, and then store it back into the hero's name.

Installation
-------------

To install the plugin, make sure that you have patched your project with cherry's DynRPG patch which
can be found here: 
http://share.cherrytree.at/showfile-12494/dynrpg.rar (Link for v0.20)
http://cherrytree.at/dynrpg

1. Copy the "game_hero_rename.dll" into the DynPlugins folder of your own project.

2. ????

3. Profit!


Comment Commands/Instructions
=============================

@dbname_to_vars - Extracts the Database name of the specified hero to a range of variables
  - Parameter 1 (number): Database ID of a hero
  - Parameter 2 (number): Variable of the first character in the name. Additional characters will be stored in subsequent variables up to 12. 
	Example: If the name is "Alex"
		Variable 1: 65 (A)
		Variable 2: 108 (l)
		Variable 3: 101 (e)
		Variable 4: 120 (x)
		
@vars_to_name - Takes 12 variables in a row, and matches the values to their ASCII characters, and looks for a "Change Hero Name" event command directly after it with "@dyn" in the "New Name" field. If @dyn is not found, the name will not be converted!
  - Parameter 1 (number): Database ID of the hero
  -	Parameter 2 (number): Variable of the first character in the name. It and subsequent variables (up to 12) will be converted to ASCII. If any of the 12 variables are 0, then the plugin will only read up to that variable. 
	Example:
		Variable 1: 65 (A)
		Variable 2: 108 (l)
		Variable 3: 101 (e)
		Variable 4: 120 (x)
		Variable 5: 0
		Variable 6: 74 (J)
		Variable 7: 114 (r)
		
	The name will still only be "Alex." The reason for this is because the string needs to use the 0 as an endpoint. If you wanted a space character instead, use "32."

	
Note: you can set any "number" parameter in DynRPG to the variable ID of your choice, so "V123" would be the value of variable 123.

