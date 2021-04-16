# Console Chess

This project is basicaly a fully functional chess that runs on the Console and was made entirely in C++.  
Compiled using g++:  
~~~
g++ -DUNICODE chess.cpp -o chess
~~~

## How to play:  
WASD -> Moves the cursor;  
ENTER -> Select a piece;  
ENTER (With a selected piece) -> Place the piece in the cursor position (if the piece can do that move);  
ESC -> Deselect a selected piece;  
I -> Debug tool (Left as a cheat) that opens a menu to insert pieces on cursor position;  
O - > Debug tool (Left as a cheat) that deletes a piece;  

## IMPORTANT!!:  
If your chess start in a really bizarre shape, resize the screen to fit the exactly the chessboard size.
(Chessboard size is 8x8)

## Images:
### Game View:  
![Normal Game Init](/images/GameInitView.png)  
### Turn warning:
![Turn Warning](/images/TurnWarning.png)
### After some movements:  
![Game After Some Movements](/images/JustSomeMovements.png)  
### EnPassant:
![EnPassant 1](/images/EnPassant1.png)  
![EnPassant 2](/images/EnPassant2.png)  
### Short Castle:
![Short Castle 1](/images/ShortCastle1.png)
![Short Castle 2](/images/ShortCastle2.png)
### Long Castle:
![Long Castle 1](/images/LongCastle1.png)
![Long Castle 2](/images/LongCastle2.png)
### Color Changing:
![Color Change](/images/ColorChange.png)
