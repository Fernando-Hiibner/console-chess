//Considering that almost every single code include this one, i decided to import almost every single built-in library here
#define _WIN32_WINNT 0x0500
#include <Windows.h>
#include <iostream>
#include <vector>
#include <chrono>

extern HANDLE hConsole;
CONSOLE_SCREEN_BUFFER_INFO csbi;
extern const int chessboardSquareWidth, chessboardSquareHeight;

using namespace std;
//Holds PieceData - Id and Coord
typedef struct PieceData
{
    wchar_t pieceId;
    COORD pieceCoord;
public:
    PieceData(wchar_t id, COORD coord)
    {
        pieceId = id;
        pieceCoord = coord;
    }
    PieceData(wchar_t id)
    {
        pieceId = id;
    }
    PieceData(COORD coord)
    {
        pieceCoord = coord;
    }
    PieceData();
    void defineCoord(COORD coord)
    {
        pieceCoord = coord;
    }
}PieceData;

COORD actualCursorPosition()
{
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    COORD cursorPosition = csbi.dwCursorPosition;

    return cursorPosition;      
}
//true - if equals / false - if not
bool compareCoordinates(COORD firstCoord, COORD secondCoord)
{
    if(firstCoord.X == secondCoord.X
    && firstCoord.Y == secondCoord.Y)
    {
        return true;
    }
    return false;
}
//Reduce basicaly means reducing large ints that the the game can have, in tiny ints used in the conversion of 2D to 1D coord
COORD reduceCoord(COORD coordToBeReduced)
{
    return {(SHORT)(coordToBeReduced.X/chessboardSquareWidth),(SHORT)(coordToBeReduced.Y/chessboardSquareHeight)};
}
