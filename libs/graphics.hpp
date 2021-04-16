#ifndef UTILIDADES_HPP
#define UTILIDADES_HPP
#include "utilitys.hpp"
#endif


const int chessboardSquareWidth = 10, chessboardSquareHeight = 5;
extern COORD selectedPiecePosition;
extern const short whiteColor = 0x2588, lightGrayColor = 0x2593, grayColor = 0x2591;
extern const int screenWidth, screenHeight, mapWidth;

using namespace std;
//This function read the chessboard wstring and use it to draw the chessboard int the screen buffer
void drawChessboard(wchar_t *screen, wstring chessboard)
{
    for(int coordX = 0; coordX < screenWidth; coordX++)
    {
        for(int coordY = 0; coordY < screenHeight; coordY++)
        {
            //Equivalent to reducing coords but made individualy
            int reducedXCoord = (int)(coordX/10);
            int reducedYCoord = (int)(coordY/5);
            
            wchar_t charInChessboard = chessboard[reducedYCoord*mapWidth+reducedXCoord];
            
            short chessboardSquareColor = ' ';

            if(charInChessboard == '#')
            {
                chessboardSquareColor = whiteColor;
                screen[coordY*screenWidth+coordX] = chessboardSquareColor;
            }
            if(charInChessboard == ' ')
            {
                chessboardSquareColor = ' ';
                screen[coordY*screenWidth+coordX] = chessboardSquareColor;
            }
        }
    }
}
//Draw a highlight on top of the piece where the cursor is now
wstring highlight(wstring piece)
{
    wstring highlight;
    highlight += L"00......00";
    highlight += L"0........0";
    highlight += L"..........";
    highlight += L"0........0";
    highlight += L"00......00";

    for(int coordX = 0; coordX < chessboardSquareWidth; coordX++)
    {
        for(int coordY = 0; coordY < chessboardSquareHeight; coordY++)
        {
            wchar_t charInHighlight = highlight[coordY*chessboardSquareWidth+coordX];

            if(charInHighlight == '0')
            {
                piece[coordY*chessboardSquareWidth+coordX] = '0';
            }
        }
    }

    return piece;
}
//Will receive a piece id and return the corresponding piece "texture", with applied highlight if under the cursor
wstring createPiece(wchar_t pieceId, COORD pieceCoord)
{
    wstring piece;
    if(pieceId == 'P')
    {
        piece += L"....##....";
        piece += L"...####...";
        piece += L"....##....";
        piece += L"...####...";
        piece += L".########.";

        if(compareCoordinates(pieceCoord, selectedPiecePosition)
        || compareCoordinates(pieceCoord, actualCursorPosition()))
        {
            piece = highlight(piece);
        }
        return piece;
    }
    else if(pieceId == 'T')
    {
        piece += L"#.#.##.#.#";
        piece += L".########.";
        piece += L"....##....";
        piece += L"...####...";
        piece += L".########.";

        if(compareCoordinates(pieceCoord, selectedPiecePosition)
        || compareCoordinates(pieceCoord, actualCursorPosition()))
        {
            piece = highlight(piece);
        }
        return piece;
    }
    else if(pieceId == 'C')
    {
        piece += L".#######..";
        piece += L"#########.";
        piece += L"##..######";
        piece += L"...######.";
        piece += L"..########";

        if(compareCoordinates(pieceCoord, selectedPiecePosition)
        || compareCoordinates(pieceCoord, actualCursorPosition()))
        {
            piece = highlight(piece);
        }
        return piece;
    }
    else if(pieceId == 'B')
    {
        piece += L"....##....";
        piece += L"...####...";
        piece += L"...####...";
        piece += L"....##....";
        piece += L".########.";

        if(compareCoordinates(pieceCoord, selectedPiecePosition)
        || compareCoordinates(pieceCoord, actualCursorPosition()))
        {
            piece = highlight(piece);
        }
        return piece;
    }   
    else if(pieceId == 'R')
    {
        piece += L"....##....";
        piece += L"..######..";
        piece += L".##.##.##.";
        piece += L".########.";
        piece += L"##########";

        if(compareCoordinates(pieceCoord, selectedPiecePosition)
        || compareCoordinates(pieceCoord, actualCursorPosition()))
        {
            piece = highlight(piece);
        }
        return piece;
    }
    else if(pieceId == 'D')
    {
        piece += L"#.#.##.#.#";
        piece += L"#.#.##.#.#";
        piece += L".#.####.#.";
        piece += L"##########";
        piece += L"##########";

        if(compareCoordinates(pieceCoord, selectedPiecePosition)
        || compareCoordinates(pieceCoord, actualCursorPosition()))
        {
            piece = highlight(piece);
        }
        return piece;
    }
    //This basically is a blank piece representing blank spaces, used to draw the cursor highlight where there is no piece
    else if(pieceId == 'V')
    {
        piece += L"..........";
        piece += L"..........";
        piece += L"..........";
        piece += L"..........";
        piece += L"..........";

        if(compareCoordinates(pieceCoord, selectedPiecePosition)
        || compareCoordinates(pieceCoord, actualCursorPosition()))
        {
            piece = highlight(piece);
        }
        return piece;
    }
    return piece;    
}
void drawPieces(wchar_t *screen, wchar_t charInChessboard, wchar_t charInPiecesPosition, COORD pieceCoord)
{
    wstring piece = createPiece(toupper(charInPiecesPosition), pieceCoord); //Pass to uper because in this part there is no need to distinct piece color
    short chessboardSquareColor = ' ';

    int pieceCoordX = pieceCoord.X;
    int pieceCoordY = pieceCoord.Y;

    for(int coordX = 0; coordX < chessboardSquareWidth; coordX++)
    {
        for(int coordY = 0; coordY < chessboardSquareHeight; coordY++)
        {
            int xCoordOfThisPiece = pieceCoordX + coordX;
            int yCoordOfThisPiece = pieceCoordY + coordY;
            if(charInChessboard == '#')
            {
                chessboardSquareColor = whiteColor;
                if(piece[coordY*chessboardSquareWidth+coordX] == '.')
                {
                    screen[yCoordOfThisPiece*screenWidth+xCoordOfThisPiece] = chessboardSquareColor;
                }
                else if(piece[coordY*chessboardSquareWidth+coordX] == '0')
                {
                    if(isupper(charInPiecesPosition))
                    {
                        screen[yCoordOfThisPiece*screenWidth+xCoordOfThisPiece] = grayColor;
                    }
                    else if(islower(charInPiecesPosition))
                    {
                        screen[yCoordOfThisPiece*screenWidth+xCoordOfThisPiece] = lightGrayColor;
                    }
                    else if(charInPiecesPosition == '.')
                    {
                        screen[yCoordOfThisPiece*screenWidth+xCoordOfThisPiece] = grayColor;
                    }
                }
                else if(piece[coordY*chessboardSquareWidth+coordX] == '#')
                {
                    if(isupper(charInPiecesPosition))
                    {
                        screen[yCoordOfThisPiece*screenWidth+xCoordOfThisPiece] = lightGrayColor;
                    }
                    else
                    {
                        screen[yCoordOfThisPiece*screenWidth+xCoordOfThisPiece] = grayColor;
                    }
                }
            }
            if(charInChessboard == ' ')
            {
                chessboardSquareColor = ' ';

                if(piece[coordY*chessboardSquareWidth+coordX] == '.')
                {
                    screen[yCoordOfThisPiece*screenWidth+xCoordOfThisPiece] = chessboardSquareColor;
                }
                else if(piece[coordY*chessboardSquareWidth+coordX] == '0')
                {
                    if(isupper(charInPiecesPosition) && charInPiecesPosition != 'V')
                    {
                        screen[yCoordOfThisPiece*screenWidth+xCoordOfThisPiece] = grayColor;
                    }
                    else if(islower(charInPiecesPosition) || charInPiecesPosition == 'V')
                    {
                        screen[yCoordOfThisPiece*screenWidth+xCoordOfThisPiece] = lightGrayColor;
                    }
                    else if(charInPiecesPosition == '.')
                    {
                        screen[yCoordOfThisPiece*screenWidth+xCoordOfThisPiece] = lightGrayColor;
                    }
                }
                else if(piece[coordY*chessboardSquareWidth+coordX] == '#')
                {
                    if(isupper(charInPiecesPosition))
                    {
                        screen[yCoordOfThisPiece*screenWidth+xCoordOfThisPiece] = lightGrayColor;
                    }
                    else
                    {
                        screen[yCoordOfThisPiece*screenWidth+xCoordOfThisPiece] = grayColor;
                    }
                }
            }
        }
    }
}
//Will call all the necessary draw functions and map all the pieces in the coordMapedPiecesPosition, its the convergence point of this hpp
vector<PieceData> drawAndMapPieces(wchar_t *screen, wstring chessboard, wstring piecesPositon)
{
    vector<PieceData> coordMapedPiecesPosition;
    for(int coordX = 0; coordX < screenWidth; coordX += 10)
    {
        for(int coordY = 0; coordY < screenHeight; coordY += 5)
        {
            int reducedXCoord = (int)(coordX/10);
            int reducedYCoord = (int)(coordY/5);
            
            wchar_t charInPiecesPosition = piecesPositon[reducedYCoord*mapWidth+reducedXCoord];
            
            wchar_t charInChessboard = chessboard[reducedYCoord*mapWidth+reducedXCoord];

            COORD pieceCoord = {(SHORT)coordX, (SHORT)coordY};

            if(charInPiecesPosition != '.')
            {
                //Map
                PieceData dadosDaPeca(charInPiecesPosition, pieceCoord);
                coordMapedPiecesPosition.push_back(dadosDaPeca);

                //Draw
                drawPieces(screen, charInChessboard, charInPiecesPosition, pieceCoord);
            }
            if(charInPiecesPosition == '.')
            {
                //Draw
                drawPieces(screen, charInChessboard, 'V', pieceCoord);
            }
        }
    }
    return coordMapedPiecesPosition;
}

