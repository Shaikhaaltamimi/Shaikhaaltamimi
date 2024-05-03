
# Ludo Board Game 

This project is a Ludo Board game project. It showcases the objected oriented programming concepts (OOP) and dynamic memory allocation. 




## Overview of Game 

Ludo is a board game that will be played with four players. The game board is divided into four colored quadrants, each for a player, in red, green, yellow, and blue. There are pathways that interconnect the quadrants, forming a track for the game pieces to traverse. 


The starting point for each player’s tokens are determined by their color specific path on the board, the colored strips.  Each player has four colored tokens (of the same color), and with these tokens, their objective is to move each of them around the board in a clockwise direction (depicted by the motion of the purple arrow) until they reach the center of the board, called the "home" or "safe" zone.




## How to Use Ludo Game 

1. The first thing that will pop up is to enter the number of players 

2. After number of players, it will prompt for names of the players 

3. The game shall start now and the dice is has began to roll. 

This is what will happen: 

Winning condition: The winner is determined when one player has all four of their four tokens at the edge of the board, which is known as the “home squares.”
Game board: Some squares on the board are designated as safe zones. These safe zones include the home columns (red, green, yellow, and blue squares)
Rule #1: Players take turns in a clockwise order, starting with the player who rolls the highest number on the dice to determine who goes first. The dice used is a regular six-sided die, with faces labeled "1" through "6." The number rolled on the dice indicates how many steps the player can move one of their tokens forward on the board.
Rule #2: Rolling a "six" allows the player to move a dice. If the roll does not result in a "six," the player moves one of their tokens according to the die roll and then the turn passes to the next player.
Rule #3: a player must move all their tokens into their home pathway of the corresponding color, located at the edge of the board. At the start of the game, players can choose any token to move.
Rule #4: When a player's token lands on a square occupied by an opponent's token, the opponent's token is removed by the other token, and it cannot re-enter the game again. 



              Enjoy! 
## User Manual: how to use the program

Use Visual Studio Code to run the program. As explained in the report, ANSII escape codes might cause issues on certain compilers due to discrepency in terminal behavior across different IDEs. 

Run the following comand on visual studio code. Make sure you are in the correct directory. We have saved the file in the desktop. 

```bash
  cd desktop 
```

After that, run the program with c++11, some declerations might cause issues in some compilers again. Use the following command: 

```bash
  g++ -std=c++11 new_ludo.cpp 
```

Then, an executable file should come out. For example a.out. You should run it this way: 


```bash
  ./a.out  
```
This should work and you should  see the program running. 



    
## Lessons Learned: Challenges and Improvements 

- We encountered and overcame multiple challenges, including issues with compiling ANSI codes in environments other than C++11 and discrepancies in terminal behavior across different development environments (e.g., Visual Studio Code vs. Xcode). These challenges were significant in teaching us about the importance of environment testing and compatibility in software development.

- One of the initial hurdles was establishing proper getters and setters for the various classes in the project. This process involved a lot of trial and error to ensure that the data encapsulation principles of Object-Oriented Programming (OOP) were properly implemented


- Another challenge was passing the Board object as a parameter throughout the code to make necessary changes to it. This required careful consideration of the design and architecture of the program to ensure that changes made in one part of the codebase were reflected correctly in other parts.

- We encountered an issue where the screen was moving too fast, which affected the user experience. To address this, we included code snippets to pause the screen during critical moments, such as when the dice is rolling. This enhancement required some research to implement effectively and improve the overall gameplay experience

 
