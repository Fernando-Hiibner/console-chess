#ifndef UTILIDADES_HPP
#define UTILIDADES_HPP
#include "utilitys.hpp"
#endif

extern HANDLE hConsole;
extern chrono::system_clock::time_point lastCommandTime;
extern const int screenWidth, screenHeight;

using namespace std;
bool keyPressed(char key)
{
    //Acording to my researchs this 0x800 is basicaly the time that it will wait before refreshing and wait for another
    //0x80 its litle and 0x8000 its a lot
    if(0x800 && GetAsyncKeyState((unsigned short)key) && GetConsoleWindow() == GetForegroundWindow())
    {
        return true;
    }
    return false;
}
COORD moveCursor(int xOffset, int yOffset)
{
    COORD cursorPosition = actualCursorPosition();
    if(cursorPosition.X+xOffset < screenWidth && cursorPosition.Y+yOffset < screenHeight)
    {
        cursorPosition = {(SHORT)(cursorPosition.X+xOffset), (SHORT)(cursorPosition.Y+yOffset)};
    }
    SetConsoleCursorPosition(hConsole, cursorPosition);
    lastCommandTime = chrono::system_clock::now();
    return cursorPosition;
}
