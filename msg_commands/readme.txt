Message Commands:

(RM2k3 Defaults)
\C[n] & \c[n] Show a text color, where n=a number(1 to 19)
\S[n] & \s[n] Set the text speed, where n=a number(1 to 20) 1 is the fastest(without pauses) and 20 is the slowest.
\N[n] & \n[n] Show the name of a hero, where n=hero's number.Note that 0 will write the name of your party's leader.
\V[n] & \v[n] Show a variable value where n=variable's number.
\$ A box appears showing your current money.
\! Put that before a word. You will have to press enter to show that word but it will be in the same box than the others.
\. 1/4 of delay before the next letter.
\| 1 delay before the next letter.
\^ The message end without you need to press enter.
\> \< Displays the part of the message between \> and \< instantly.
\\ Shows "\".
\_ Shows half a space.


(msg_commands plugin)
\A[n] & \a[n] The name of an attribute (from the Attribute tab of the database), where n=database id

\B[n] & \b[n] The name of a battle command (from the Battle Layout tab of the database), where n=array id

\D[n] & \d[n] Hero's degree/class, where n=hero's id.

\I[n] Item Name, where n=item id
\i[n] Item Description, where n=item id

\K[n] Skill Name, where n=skill id
\k[n] Skill Description, where n=skill id

\M[n] Monster Name, where n=monster id
\m[n] Monster Item ID, where n=monster id

\O[n] & \o[n] - Condition, where n=condition id

\R[n] & \r[n] The name of a database string (from the String tab of the database), where n=**SEE CHART BELOW**

\T[n] & \t[n] The name of a terrain (from the Terrain tab of the database), where n=terrain id




Usage
-----
Add a comment line with:

    @process_cmd

...followed by the message box with one of the commands above.

Commands can still be combined (Example: \I[\m[\V[123]]] would give you the item name dropped by the monster with the ID stored within variable 123).

Since version 1.1: Allows you to put brackets around a complex command. Example if variable 123 was "5" and monster 5's item drop name was "Potion", the command "[\I[\m[\V[123]]]]" would return "[Potion]"
(In the previous version of this plugin, all closing brackets got parsed out, so it would have returned "[Potion")





Database String IDs (RPG::vocabulary in DynRPG)
--------------------------------------------
String Page 1 

 0: Message at the Beginning of Each Battle
 1: Initiative Message
 2: Escape Failure Message
 3: Victory Message
 4: Defeat Message
 5: Experience Gain Message (Field 2)
 6: Money Acquisition Message (Field 1)
 7: Money Acquisition Message (Field 3)
 8: Item Discovery Message

The following are not in the Strings tab... (but accessible via Resource Hacker)

 9: attacks
10: A critical hit! (target = monster)
11: A critical hit! (target = hero)
12: defends.
13: is waiting and watching.
14: is building strength.
15: pounces.
16: runs away!
17: transformed
18: HP is lost (target = monster)
19: Dodged (target = monster)
20: HP is lost (target = hero)
21: dodged (target = hero)
22: got out of the way (magic)
23: needs more practice (magic)
24: was not affected (magic)
25: dodged (physical)
26: used
27: recovered!
28: raises!
29: drops
30: is taken!
31: is taken!
32: Defense increases!
33: Defense decreases!

Strings Page 2

34: Level Up (Field 2)
35: Skill Learned (Field 2)
36: ??
37: ??
38: ??
39: ??
40: ??

Strings Page 4

41: Items Possessed
42: Item Equipped
43: Currency

Strings Page 5

44: Fight
45: Auto-Fight
46: Escape

????

47: "Attack"
48: "Defend"

Strings Page 5 (continued)

49: Item
50: Skill
51: Equipment
52: Save
53: Quit
54: New Game
55: Load Game
56: Quit Game
57: Level
58: HP
59: MP
60: Normal Status
61: Experience
62: Level (Short Form)
63: HP (Short Form)
64: MP (Short Form)
65: MP Consumed
66: Attack
67: Defense
68: Intelligence
69: Agility
70: Weapon
71: Shield
72: Armor
73: Helmet
74: Accessory
75: Choosing a Save Slot
76: Choosing Which Slot to Load
77: Confirm Quit
78: File
79: Yes
80: No
81: Status
82: Order
83: Row
84: Wait ON
85: Wait OFF

????

86: ??

String Page 1 (continued)

87:  "Miss" Message
