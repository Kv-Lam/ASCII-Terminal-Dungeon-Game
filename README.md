Last Updated: May 3, 2024.

Contributors:
- Kevin Lam (Created combat, inventory, enemies, and player)
- Sean Sullivan (Created loadRooms, ASCII arts [ASCII arts were draw by me and fed into an image converter, which can be found here:
  https://www.asciiart.eu/image-to-ascii if you would like to make your own. As stated below the converter, "The ASCII Art generated from 'Image to ASCII Art' is free to use for any purpose, including personal and commercial projects." ], and rooms.txt as a sample dungeon file to play for the first time)

This project is a terminal-based text dungeon game based on the MUD lab from CS102 for CS202. It applies the same concept of utilizing a pointer to an array of room structures. However, it has been built upon to have actual playability by implementing a character, enemies, a somewhat basic combat system, stats, and an inventory with item usage utilizing an unordered_map (hash table). Furthermore, the project includes an improved version of the look command to print ASCII room art included inside of the file given via argument line.

How to run: ```./mud (fileName)```

How to create a file: Create a new file following the below formatting explanation. Make sure to create the rooms in order, as each room is assigned an index number from 0 to (numRooms - 1) based on when it's read (the program reads in the file from top to down) and to have a tilde (~) after each information section. If there is no enemy, leave an empty line between the tildes for the enemy name and art, then put 0 0 0 for its stats. Refer to rooms.txt if confused by the format. 

Format to Create a Dungeon: 
```
Room Name
~
Description
~
Exit Index ([Exit " " Index] i.e.  "n 15" This string would make the north exit of the current room lead to room #15)
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
```
Possible improvements to project: Adding currency (obtaining as a drop from mobs or from random treasure chests in rooms), shop to buy or sell items, and a more complicated combat system by implementing speed, defense (along with damage calculations), or other concepts to provide a fun gameplay.
