Contributors:
Kevin Lam (Created combat, inventory, enemies, and player)
Sean Sullivan (Created loadRooms, ASCII arts, and rooms.txt as a sample dungeon file to play for the first time)

This project is a terminal-based text dungeon game based on the MUD lab from CS102 for CS202. It applies the same concept of utilizing a pointer to an array of room structures. However, it has been built upon to have actual playability by implementing a character, enemies, a somewhat basic combat system, stats, and an inventory with item usage utilizing an unordered_map (hash table). Furthermore, the project includes an improved version of the look command to print ASCII room art included inside of the file given via argument line.

How to run: ./mud (fileName)

How to create a file: Create a new file following the below formatting explanation. Make sure to create the rooms in order, as each room is assigned an index number from 0, to (numRooms - 1) based on when it's read (the program reads in the file from top to down). If there is no enemy, leave an empty line between the tildes (~) for the enemy name and art, then put 0 0 0 for its stats. Refer to rooms.txt if confused by the format. 

Format to Create a Dungeon:
Room Name
~
Description
~
Exit Index
~
Room Art
~
Enemy Name
~
EnemyHP EnemyATK
~
Enemy Art
~
Enemy Dialogue
~