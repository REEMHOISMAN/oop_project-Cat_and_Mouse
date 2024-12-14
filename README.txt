====== PROJECT - CAT AND MOUSE =====
name: Re'em Hoisman

---- Program info ----
this program presenting a cat mouse game by the following rules:
* the user controlls the mouse - he can move the mouse to one direction (left, right, up or down) each time
* the mouse cannot go through walls or doors (unlless its key's counter is greater than 0)
* the mouse stepped on a one of the four gifts 4:
1. if its "life gift" and its lives are less than 3 this number will increase by 1.
2. if its "freeze cats gift" all of the cats will be frozen for 5 seconds.
3. if its "time gift" the level timer will increase by 30 seconds.
4. if its "pop cat gift" one of the cats on level board will disappear.
* each level ends when the mouse eaten all of the cheese that was on board
* the user starts the game with '3 life' each time cats eat the mouse then the amount of lifes is being redused
  and the all cats and mouse gets back to theyre starting positions (without the objects that disasapear)
* if the level timer is up - the level will restart
* each object that the mouse eats and at the end of each level garentee a points reward
* the game runs until there is no more levels to read or if the mouse have 0 lifes

---- Files ----
consts.h - contains all const variables of the program

menu.h - contains the declaretions of class Menu and its functions, members
menu.cpp - the implement of class Menu functions and constructor, control the whole program
		   by the user choice (exit/help/new game) holds the buttons.

ResourcesManager.h - contains the declaretions of class Menu and its functions
ResourcesManager.cpp - the implement of class ResourcesManager functions and constructor, an singletone class
					  provide the wanted resource without being a member of any other class

Level.h - contains the declaretions of class Level and its functions, members
Level.cpp - the implement of class Level functions and constructor
			responsible for what appears on the level board

GameController.h - contains the declaretions of class GameController and its functions, members
GameController.cpp - the implement of class GameController functions and constructor
					responsible for all game managment - open files, check game and level conditions 
					and control all of the other objects depend on the current game situation.

GameInfo.h - contains the declaretions of class GameInfo and its functions
GameInfo.cpp - the implement of class GameInfo functions
			   to all of the prrinting of the game info while game is running, and also at the end of the game

GameObject.h - contains the declaretions of class GameController and its functions, member (sprite of the object)
GameObject.cpp - the "root" of the inheritance tree, abstract class that implement getters, setters, isCollusion and other functions

Entity.h - base class of the mouse and cats (not by using polimorphism)

Mouse.h - contains the declartion of class Mouse (members, function prototypes, derived class of Entity class)
Mouse.cpp - the implement of class Mouse functions and constructor
			responsible on the movement of the mouse (according to user choice), and implement the handle collusions
			with all Interactables objects

Cat.h - contains the declartion of class Cat (members, function prototypes, derived class of Entity class)
Cat.cpp - the implement of class Cat functions and constructor
		  responsible one the movement of the cat.

StaticObject.h - a "middle class" between GameObject and - class Door, class Wall, class InteractableObject

InteractableObject.h - base class of the classes: Cheese, Key, FreezeGift, LifeGift, PopCatGift, TimeGift
					   abstract class so each collusion with one of its derived classes is being use by double dispatch (polimorphism)

classes: Cheese, Key, FreezeGift, LifeGift, PopCatGift, TimeGift - all derived classes of InteractableObject each one have .cpp file
																  and .h file (all the same logic with double dispatch)

Wall.h - derived class of StaticObject class, contains the declaretions of class Wall and its function
Wall.cpp - Implement the constructor and the handleCollusion function.

Door.h - derived class of StaticObject class, contains the declaretions of class Door and its function
Door.cpp - Implement the constructor and the handleCollusion function, also have a boolian in order to know if the door need to be deleted to not.


---- Data base ----
Texture m_textures[] - holds all of the textures in the game
SoundBuffer m_sounds[] -  holds all of the sounds in the game
vector<sprites> m_buttons - holds the three buttons (new game/ help/ exit)
vector <Cat> m_cats - data base that contain all of the cats in the game
vector <Wall> m_walls - data base that contain all of the walls in the game
vector <Door> m_door - data base that contain all of the doors in the game
vector <InteractableObject*> m_objects - data base that contain all of the interactable objects in the game
vector <vector <vector2f> > positions - data base the contain the positions that lead from the mouse to the cat (bfs)
queue < Vector2f > queue - data base that contain the positions that have being check during bfs 
vector < vector < bool> > visited - mark if we have been in the check that position (bfs)

		 
---- Algorithems ----
**BFS**
the algorithm is being used in order to find the shortest path from the cat to the mouse.
after getting the vector of the door, and the vector of the walls the algorithm work by the following steps:
1. we create 3 data bases : vector < vector < bool> > visited, vector <Vector <Vector2f> >road, queue < Vector2f > queue
   (which describe in Data base section), we mark all of the doors and walls in the visited matrix as true (so the cat knows he cant go there)
2. we start by keeping the cat positions in 'road' this is our destination, put in our queue,
   and mark the that positions as 'true' in visited.
3. we entered into a while loop that continues until out the queue is empty/ we reached the mouse - that mean the all of the roads from
   the cat to the mouse have been checked (every path in that level at all) and we find the shortest one .
   in each iteration in the while loop we take out a positions from the queue in order to check all of the ways possible
   from that positions and on. if the direction is valid (means the cat go to that dircetion from the current positions) we put in
   the position we just entered the position we came from in 'positions' matrix - by doing it we makeing ourself a path in the matrix 
   'positions' which each position there lead to another.
   we keep push that new positions we read into our queue so we would know that we have to check all of the directions from that
   position.
   however if we block all of the direction to the cat, the algorithm will not work. and the cat will stay static

----Design----
the game runs by the following rules:
class Menu - at any moment the user can :exit/start new game/enter the help page by pressing on of the buttons.
			 if he pressed new game, than a game will run from level one.
Class GameController - manage all the game proccess. have members of Level, Mouse, Vector<Cat>, InfoGame, Menu&.
				     the game starts when the first level is being open and continues until there is no more levels from that playlist to read. 
				     each level we read the board of that is being loaded, by using the member m_level.  the GameController use the Mouse member 
                 	 and vector<Cat> member in order to make them move (each of them).
				     check the conditions of the game after the mouse and the cats have been moved.  
				     and update the game after each frame

Class Level - control and check all of the static objects in the game, update whatever need to be updated after a collusion with the mouse,
			  also every 15 sec a spawnGift function is being implement - gift can vbe spawn only on "empty erea" 

class mouse - when the user wants - this class handles and implement the user movement choice after a key (from the keyboard) has been entered.
		      if the user entered a valid key then it use class level information and double dispatch in order to check if the step the user
			  tries to do is valid or if there is any objects that the mouse stepped on.
		      if everything is good then the mouse will move to that direction otherwise he will be block (by wall for example)
		      in case of space is being entered than the mouse wont move at all (user chose to give up on his current turn).

class Cat - now its the program turn, by using a BFS method this class is resposibble to move the cat toword the mouse
			(if there is no walls or doors)
		    because the cat goal is to reach the mouse it uses a the reference of Mouse object so it can try to reach its positions.
			if the mouse/the cat is surrounded by walls. then the cat will not move at all (because he cannot reach the mouse anyway)

class InteractableObject - holds all of the interactable objects of the game, being use mostly in double dispatch (after the mouse movement)
						also every 15 sec, a random gift is inserted to the vector of that class pointr (being hold by class level).


---- Bugs ----

---- Notes ----
in order to add levels do as the following instructions in "resourses" file:
1. add your level file name into - "Playlist.txt" (in a new line!!).
2. then in "CmakeList.txt" (still in resources file) and add the name of your level to the configure_file.

the level format is "Level00X.txt" (while X is the level number - must be in order and not just a random level number!!)
for example: if you level called  "Level004.txt"
add it in new line at the end of Playlist.txt
and than in "CmakeList.txt" add this: (in a new line)
configure_file ("Level004.txt" ${CMAKE_BINARY_DIR} COPYONLY)

if new level is being used - use level of 34 cols and 22 rows **can fit smaller level but in this way itll look as i wished**
