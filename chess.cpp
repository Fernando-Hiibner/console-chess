#ifndef GRAFICOS_HPP
#define GRAFICOS_HPP
#include "libs/graphics.hpp"
#endif
#ifndef COMANDOS_HPP
#define COMANDOS_HPP
#include "libs/commands.hpp"
#endif
#ifndef MOVIMENTOS_HPP
#define MOVIMENTOS_HPP
#include "libs/movements.hpp"
#endif

//This essentialy create the screen "write buffer", with pre-define width and height
extern const int screenWidth = 80, screenHeight = 40;
wchar_t *screen = new wchar_t[screenWidth*screenHeight];
HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);;

wstring piecesPositon; //Holds the pieces position on a wstring that can be easily processed by the graphical function
COORD selectedPiecePosition;
extern enPassantData enPassant; 
vector<PieceData> coordMapedPiecesPosition; //Holds the pieces Id and COORD
const SHORT defaultSelectedPiecePositon = 100;
chrono::system_clock::time_point lastCommandTime = chrono::system_clock::now();
extern const short enterKey = 0x0D, escKey = 0x1B; //These are just virtual key codes for the Esc and Enter keys
extern const int mapWidth = 8;

//Holds the King position, updated everytime it moves
COORD whiteKingCoord = {(SHORT)40, (SHORT)35};
COORD blackKingCoord = {(SHORT)40, (SHORT)0};

using namespace std;
int main()
{
    /*
        This piece of code can be used to change the color of the game:
        SetConsoleMode(hConsole, ENABLE_VIRTUAL_TERMINAL_PROCESSING);
        SetConsoleTextAttribute(hConsole, 7);
        Just change the color attribute from SetConsoleTextAttribute to a number corresponding to the desired color
        Colors can be found in:
        https://docs.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences
        On the "Text Formating" section
    */

    SetConsoleActiveScreenBuffer(hConsole);

    HWND consoleWindow = GetConsoleWindow();

    MoveWindow(consoleWindow, 0, 0, 656, 680, TRUE);

    //Remove this function from comment if you dont want the screen to be resizable
    //SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);    

    DWORD bytesWritten = 0;

    wstring chessboard; //Holds the chessboard squares on a wsring that can be easily processed by the graphical function
    chessboard += L" # # # #";
    chessboard += L"# # # # ";
    chessboard += L" # # # #";
    chessboard += L"# # # # ";
    chessboard += L" # # # #";
    chessboard += L"# # # # ";
    chessboard += L" # # # #";
    chessboard += L"# # # # ";

    /*
        My original code before translation was in brazilian portuguese, so the pieces Id are on pt-br, so:
        T/t = Tower/Rook
        C/c = Horse/Knight
        B/b = Bishops
        D/d = Queen
        R/r = King
        P/p = Pawn
        Upper Char = White Pieces
        Lower Char = Black Pieces
    */
    piecesPositon += L"tcbdrbct";
    piecesPositon += L"pppppppp";
    piecesPositon += L"........";
    piecesPositon += L"........";
    piecesPositon += L"........";
    piecesPositon += L"........";
    piecesPositon += L"PPPPPPPP";
    piecesPositon += L"TCBDRBCT";

    //Frame times, used to count time passed betwen commands
    auto lastFrameTime = chrono::system_clock::now();
    auto thisFrameTime = chrono::system_clock::now();

    selectedPiecePosition = {defaultSelectedPiecePositon, defaultSelectedPiecePositon};
    bool selectedPiece = false;
    wchar_t selectedPieceId;

    bool checkmateOnWhite = false, checkmateOnBlack = false;

    int safeCheckOrMateOnWhite = 0, safeCheckOrMateOnBlack = 0; //0 - Safe / 1 - Check / 2 - Checkmate   
    bool calculateCheck = false;
    
    bool moveOf = false; //false = white move / true - black move
    
    //Game Loop
    while(!checkmateOnWhite && !checkmateOnBlack)
    {
        drawChessboard(screen, chessboard);

        coordMapedPiecesPosition = drawAndMapPieces(screen, chessboard, piecesPositon);
        //This calculates if the kings are safe or not
        if(calculateCheck)
        {
            safeCheckOrMateOnWhite = safeCheckOrMate('R', whiteKingCoord);
            safeCheckOrMateOnBlack = safeCheckOrMate('r', blackKingCoord);
            calculateCheck = false;
        }
        
        //Calculates time passed betwen frames and convert ir to seconds, used to determine if the program can read inputs
        thisFrameTime = chrono::system_clock::now();
        chrono::duration<float> timeDiferenceBetwenFrames = thisFrameTime-lastFrameTime;
        chrono::duration<float> timeDiferenceBetwenCommands = thisFrameTime-lastCommandTime;
        lastFrameTime = thisFrameTime;
        float frameTime = timeDiferenceBetwenFrames.count();
        float timeSpentSinceLastFrame = timeDiferenceBetwenCommands.count();

        bool canReadCommands = false;
        if(timeSpentSinceLastFrame > 0.2f)
        {
            canReadCommands = true;
        }

        //This piece of code can be used as Debug or as in game Cheat
        if(canReadCommands)
        {
            //Insert pieces on cursor position
            if(keyPressed('I'))
            {
                COORD actualPosition = reduceCoord(actualCursorPosition());
                //This math formula is explained in line 258
                int index = (int)(actualPosition.Y*mapWidth+actualPosition.X);
                while(!keyPressed(escKey))
                {
                    swprintf_s(screen, 100, L"Press: B - White / P - Black / ESC - Exit");
                    if(keyPressed('B'))
                    {
                        while(!keyPressed(escKey))
                        {
                            swprintf_s(screen, 95, L"Press: C - Knight / T - Rook / B - Bishop / D - Queen / R - King / P - Pawn /    ESC - Exit");
                            if(keyPressed('C'))
                            {
                                piecesPositon[index] = 'C';
                                coordMapedPiecesPosition = drawAndMapPieces(screen, chessboard, piecesPositon);
                            }
                            else if(keyPressed('T'))
                            {
                                piecesPositon[index] = 'T';
                                coordMapedPiecesPosition = drawAndMapPieces(screen, chessboard, piecesPositon);
                            }
                            else if(keyPressed('B'))
                            {
                                piecesPositon[index] = 'B';
                                coordMapedPiecesPosition = drawAndMapPieces(screen, chessboard, piecesPositon);
                            }
                            else if(keyPressed('D'))
                            {
                                piecesPositon[index] = 'D';
                                coordMapedPiecesPosition = drawAndMapPieces(screen, chessboard, piecesPositon);
                            }
                            else if(keyPressed('R'))
                            {
                                piecesPositon[index] = 'R';
                                coordMapedPiecesPosition = drawAndMapPieces(screen, chessboard, piecesPositon);
                            }
                            else if(keyPressed('P'))
                            {
                                piecesPositon[index] = 'P';
                                coordMapedPiecesPosition = drawAndMapPieces(screen, chessboard, piecesPositon);
                            }
                            WriteConsoleOutputCharacter(hConsole, screen, screenWidth * screenHeight, {0, 0}, &bytesWritten);                            
                        }
                    }
                    else if(keyPressed('P'))
                    {
                        while(!keyPressed(escKey))
                        {
                            swprintf_s(screen, 95, L"Press: C - Knight / T - Rook / B - Bishop / D - Queen / R - King / P - Pawn /    ESC - Exit");
                            if(keyPressed('C'))
                            {
                                piecesPositon[index] = 'c';
                                coordMapedPiecesPosition = drawAndMapPieces(screen, chessboard, piecesPositon);
                            }
                            else if(keyPressed('T'))
                            {
                                piecesPositon[index] = 't';
                                coordMapedPiecesPosition = drawAndMapPieces(screen, chessboard, piecesPositon);
                            }
                            else if(keyPressed('B'))
                            {
                                piecesPositon[index] = 'b';
                                coordMapedPiecesPosition = drawAndMapPieces(screen, chessboard, piecesPositon);
                            }
                            else if(keyPressed('D'))
                            {
                                piecesPositon[index] = 'd';
                                coordMapedPiecesPosition = drawAndMapPieces(screen, chessboard, piecesPositon);
                            }
                            else if(keyPressed('R'))
                            {
                                piecesPositon[index] = 'r';
                                coordMapedPiecesPosition = drawAndMapPieces(screen, chessboard, piecesPositon);
                            }
                            else if(keyPressed('P'))
                            {
                                piecesPositon[index] = 'p';
                                coordMapedPiecesPosition = drawAndMapPieces(screen, chessboard, piecesPositon);
                            }
                            WriteConsoleOutputCharacter(hConsole, screen, screenWidth * screenHeight, {0, 0}, &bytesWritten);                            
                        }
                    }
                    WriteConsoleOutputCharacter(hConsole, screen, screenWidth * screenHeight, {0, 0}, &bytesWritten);
                }
            }
            //Delete pieces on cursor position
            if(keyPressed('O'))
            {
                COORD actualPosition = reduceCoord(actualCursorPosition());
                //This math formula is explained in line 258
                int index = (int)(actualPosition.Y*mapWidth+actualPosition.X);
                piecesPositon[index] = '.';
            }
        }

        //Controls
        if(canReadCommands)
        {
            if(keyPressed('W'))
            {
                //Up
                moveCursor(0, -5);
            }
            else if(keyPressed('A'))
            {
                //Left
                moveCursor(-10, 0);
            }
            else if(keyPressed('S'))
            {
                //Down
                moveCursor(0, 5);
            }
            else if(keyPressed('D'))
            {
                //Right
                moveCursor(10, 0);
            }
            else if(keyPressed(enterKey) && !selectedPiece)
            {
                COORD reducedCursorPosition = reduceCoord(actualCursorPosition());                

                /*
                    This math formula basically converts X and Y coords (2D coords) into a single Index coord (1D coords)
                    Basicaly you have a string (1D coord) with only one line and want to read it as multiple lines with X and Y coords
                    To do that you multiply the Y coord (equivalent to line) by the amount of characteres of each line (in this case 8)
                    and then sum with the X coord, resulting in a converted 2D coord to 1D
                    Ex:
                        X = 3 -> char position in line
                        Y = 7 -> line that you want to get the X char
                        lineWidth = 8 -> amount of char per line

                        7*8+3 = 56+3 = 59
                        This on a 64 char string (8x8) would return the 59º character wich is equivalent to the 3º char in the 7º line
                */
                wchar_t pieceToBeSelected = piecesPositon[reducedCursorPosition.Y*mapWidth+reducedCursorPosition.X];

                //Only select if the moveOf corresponds to the desired piece color
                if(pieceToBeSelected != '.' && ((moveOf && islower(pieceToBeSelected)) || (!moveOf && isupper(pieceToBeSelected))))
                {
                    selectedPiecePosition = actualCursorPosition();
                    selectedPieceId = pieceToBeSelected;
                    selectedPiece = true;
                }
                else if(moveOf && isupper(pieceToBeSelected))
                {
                    while(!keyPressed(escKey))
                    {
                        swprintf_s(screen, 60, L"Black pieces turn! Press ESC to continue...");
                        WriteConsoleOutputCharacter(hConsole, screen, screenWidth * screenHeight, {0, 0}, &bytesWritten);
                    }
                }
                else if(!moveOf && islower(pieceToBeSelected))
                {
                    while(!keyPressed(escKey))
                    {
                        swprintf_s(screen, 60, L"White pieces turn! Press ESC to continue...");
                        WriteConsoleOutputCharacter(hConsole, screen, screenWidth * screenHeight, {0, 0}, &bytesWritten);
                    }
                }
                lastCommandTime = chrono::system_clock::now();
            }
            else if(keyPressed(enterKey) && selectedPiece)
            {
                COORD desiredPosition = actualCursorPosition();                

                if(canMove(selectedPieceId, selectedPiecePosition, desiredPosition))
                {
                    COORD reducedSelectedPiecePosition = reduceCoord(selectedPiecePosition);
                    COORD reducedDesiredPosition = reduceCoord(actualCursorPosition());

                    //This exception is to correctly draw a pawn that just did EnPassant
                    if(selectedPieceId == 'P' || selectedPieceId == 'p')
                    {
                        if(compareCoordinates(enPassant.vulnerablePositionCoord, desiredPosition))
                        {
                            COORD reducedEnPassantCoord = reduceCoord(enPassant.pieceCoord);
                        
                            piecesPositon[reducedEnPassantCoord.Y*mapWidth+reducedEnPassantCoord.X] = '.';
                        }
                    }
                    calculateCheck = true;
                    
                    piecesPositon[reducedDesiredPosition.Y*mapWidth+reducedDesiredPosition.X] = selectedPieceId;
                    piecesPositon[reducedSelectedPiecePosition.Y*mapWidth+reducedSelectedPiecePosition.X] = '.';
                    selectedPiecePosition = {defaultSelectedPiecePositon, defaultSelectedPiecePositon};
                    selectedPiece = false;
                    moveOf = !moveOf; //Swith turns
                }
                else if(!canMove(selectedPieceId, selectedPiecePosition, desiredPosition))
                {
                    while(!keyPressed(escKey))
                    {
                        swprintf_s(screen, 60, L"Invalid position! Press ESC to continue...");
                        WriteConsoleOutputCharacter(hConsole, screen, screenWidth * screenHeight, {0, 0}, &bytesWritten);
                    }
                }

                lastCommandTime = chrono::system_clock::now();
            }
            //Unselect selected piece
            else if(keyPressed(escKey) && selectedPiece)
            {
                selectedPiecePosition = {defaultSelectedPiecePositon, defaultSelectedPiecePositon};
                selectedPiece = false;
                lastCommandTime = chrono::system_clock::now();
            } 
        }

        //If so, it means that the king is in danger
        if(safeCheckOrMateOnWhite > 0)
        {
            if(safeCheckOrMateOnWhite == 1)
            {
                swprintf_s(screen, 40, L"White is on check!");
            }
            else if(safeCheckOrMateOnWhite == 2)
            {
                checkmateOnWhite = true;
            }
        }
        if(safeCheckOrMateOnBlack > 0)
        {
            if(safeCheckOrMateOnBlack == 1)
            {
                swprintf_s(screen, 40, L"Black is on check!");
            }
            else if(safeCheckOrMateOnBlack == 2)
            {
                checkmateOnBlack = true;
            }
        }

        WriteConsoleOutputCharacter(hConsole, screen, screenWidth * screenHeight, {0, 0}, &bytesWritten);
    }

    //End game loop
    while(1)
    {
        if(checkmateOnWhite)
        {
            swprintf_s(screen, 40, L"Checkmate on White!");
            WriteConsoleOutputCharacter(hConsole, screen, screenWidth * screenHeight, {0, 0}, &bytesWritten);
        }
        else if(checkmateOnBlack)
        {
            swprintf_s(screen, 40, L"Checkmate on Black!");
            WriteConsoleOutputCharacter(hConsole, screen, screenWidth * screenHeight, {0, 0}, &bytesWritten);
        }
    }

    return 0;
}