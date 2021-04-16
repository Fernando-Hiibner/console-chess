#ifndef UTILIDADES_HPP
#define UTILIDADES_HPP
#include "utilitys.hpp"
#endif

//Holds EnPassant data
typedef struct enPassantData
{
    bool canSufferEnPassant;
    COORD pieceCoord;
    COORD vulnerablePositionCoord;

    enPassantData(bool canSuffer, COORD vulnerableCoord)
    {
        canSufferEnPassant = canSuffer;
        vulnerablePositionCoord = vulnerableCoord;
    }
    enPassantData(bool canSuffer)
    {
        canSufferEnPassant = canSuffer;
    }
    void defineEnPassantData(bool canSuffer, COORD vulnerableCoord, COORD actualPieceCoord)
    {
        canSufferEnPassant = canSuffer;
        pieceCoord = actualPieceCoord;
        vulnerablePositionCoord = vulnerableCoord;
    }
}enPassantData;

enPassantData enPassant(false); //Initializes and EnPassant with false on canSufferEnPassant variable
extern COORD whiteKingCoord;
extern COORD blackKingCoord;
extern vector<PieceData> coordMapedPiecesPosition;
extern const int screenWidth, screenHeight, mapWidth;

const int whitePawnInitialYCoord = 30, blackPawnInitialYCoord = 5; //Initial Y pawn positions on COORD


const int upOffset = -5, downOffset = 5, leftOffset = -10, rightOffset = 10; //These are used to determine the offset betwen chessboardSquares
const COORD leftWhiteRookInitialCoord = {(SHORT)0, (SHORT)35};
const COORD rightWhiteRookInitialCoord = {(SHORT)70, (SHORT)35};
const COORD leftBlackRookInitialCoord = {(SHORT)0, (SHORT)0};
const COORD rightBlackRookInitialCoord = {(SHORT)70, (SHORT)0};
const COORD whiteKingInitialCoord = {(SHORT)40, (SHORT)35};
const COORD blackKingInitialCoord = {(SHORT)40, (SHORT)0};

bool leftWhiteRookMoved = false, rightWhiteRookMoved = false;
bool leftBlackRookMoved = false, rightBlackRookMoved = false;
bool whiteKingMoved = false, blackKingMoved = false;

extern wstring piecesPositon;

using namespace std;
//Move functions
vector<COORD> pawnMoves(wchar_t pieceId, COORD pieceCoord)
{
    vector<COORD> possibleMovesForThisPawn;
    //If this pawn is white
    if(isupper(pieceId))
    {
        //Calculates if this pawn can move forward by one
        COORD desiredPosition = {(SHORT)pieceCoord.X, (SHORT)(pieceCoord.Y-5)};
        bool canGoOneForward = true;

        for(int i = 0; i < coordMapedPiecesPosition.size();i++)
        {
            if(compareCoordinates(coordMapedPiecesPosition[i].pieceCoord, desiredPosition))
            {
                canGoOneForward = false;
                break;
            }            
        }
        if(canGoOneForward && pieceId == 'P')
        {
            possibleMovesForThisPawn.push_back(desiredPosition);
        }

        //Calculates if this pawn can move forward by two
        if(pieceCoord.Y == whitePawnInitialYCoord && canGoOneForward && pieceId == 'P')
        {
            COORD desiredPosition = {(SHORT)pieceCoord.X, (SHORT)(pieceCoord.Y-10)};
            bool canGoTwoForward = true;
            for(int i = 0; i < coordMapedPiecesPosition.size(); i++)
            {
                if(compareCoordinates(coordMapedPiecesPosition[i].pieceCoord, desiredPosition))
                {
                    canGoTwoForward = false;
                    break;
                }
            }
            if(canGoTwoForward)
            {
                possibleMovesForThisPawn.push_back(desiredPosition);
            }
        }

        //Calculates normal attacks and EnPassant
        COORD leftDiagonal = {(SHORT)(pieceCoord.X-10), (SHORT)(pieceCoord.Y-5)};
        COORD rightDiagonal = {(SHORT)(pieceCoord.X+10), (SHORT)(pieceCoord.Y-5)};
        bool canAttackOnLeftDiagonal = false;
        bool canAttackOnRightDiagonal = false;

        for(int i = 0; i < coordMapedPiecesPosition.size(); i++)
        {
            if(canAttackOnLeftDiagonal && canAttackOnRightDiagonal)
            {
                break;
            }
            else if(compareCoordinates(coordMapedPiecesPosition[i].pieceCoord, leftDiagonal)
            && islower(coordMapedPiecesPosition[i].pieceId))
            {
                canAttackOnLeftDiagonal = true;
            }
            else if(compareCoordinates(coordMapedPiecesPosition[i].pieceCoord, rightDiagonal)
            && islower(coordMapedPiecesPosition[i].pieceId))
            {
                canAttackOnRightDiagonal = true;
            }
        }
        if(canAttackOnLeftDiagonal)
        {
            possibleMovesForThisPawn.push_back(leftDiagonal);
        }
        if(canAttackOnRightDiagonal)
        {
            possibleMovesForThisPawn.push_back(rightDiagonal);
        }

        if(enPassant.canSufferEnPassant && pieceId == 'P') 
        {
            COORD desiredPosition = enPassant.vulnerablePositionCoord;
            if(compareCoordinates(rightDiagonal, desiredPosition)
            || compareCoordinates(leftDiagonal, desiredPosition))
            {
                possibleMovesForThisPawn.push_back(desiredPosition);
            }
        }
    }
    //If this pawn is black
    else if(islower(pieceId))
    {
        //Calculates if this pawn can move forward by one
        COORD desiredPosition = {(SHORT)pieceCoord.X, (SHORT)(pieceCoord.Y+5)};
        bool canGoOneForward = true;

        for(int i = 0; i < coordMapedPiecesPosition.size();i++)
        {
            if(compareCoordinates(coordMapedPiecesPosition[i].pieceCoord, desiredPosition))
            {
                canGoOneForward = false;
                break;
            }            
        }
        if(canGoOneForward && pieceId == 'p')
        {
            possibleMovesForThisPawn.push_back(desiredPosition);
        }

        //Calculates if this pawn can move forward by two
        if(pieceCoord.Y == blackPawnInitialYCoord && canGoOneForward && pieceId == 'p')
        {
            COORD desiredPosition = {(SHORT)pieceCoord.X, (SHORT)(pieceCoord.Y+10)};
            bool canGoTwoForward = true;
            for(int i = 0; i < coordMapedPiecesPosition.size(); i++)
            {
                if(compareCoordinates(coordMapedPiecesPosition[i].pieceCoord, desiredPosition))
                {
                    canGoTwoForward = false;
                    break;
                }
            }
            if(canGoTwoForward)
            {
                possibleMovesForThisPawn.push_back(desiredPosition);
            }
        }

        //Calculates normal attacks and EnPassant
        COORD leftDiagonal = {(SHORT)(pieceCoord.X-10), (SHORT)(pieceCoord.Y+5)};
        COORD rightDiagonal = {(SHORT)(pieceCoord.X+10), (SHORT)(pieceCoord.Y+5)};
        bool canAttackOnLeftDiagonal = false;
        bool canAttackOnRightDiagonal = false;

        for(int i = 0; i < coordMapedPiecesPosition.size(); i++)
        {
            if(canAttackOnLeftDiagonal && canAttackOnRightDiagonal)
            {
                break;
            }
            else if(compareCoordinates(coordMapedPiecesPosition[i].pieceCoord, leftDiagonal)
            && isupper(coordMapedPiecesPosition[i].pieceId))
            {
                canAttackOnLeftDiagonal = true;
            }
            else if(compareCoordinates(coordMapedPiecesPosition[i].pieceCoord, rightDiagonal)
            && isupper(coordMapedPiecesPosition[i].pieceId))
            {
                canAttackOnRightDiagonal = true;
            }
        }
        if(canAttackOnLeftDiagonal)
        {
            possibleMovesForThisPawn.push_back(leftDiagonal);
        }
        if(canAttackOnRightDiagonal)
        {
            possibleMovesForThisPawn.push_back(rightDiagonal);
        }

        if(enPassant.canSufferEnPassant && pieceId == 'p')
        {
            COORD desiredPosition = enPassant.vulnerablePositionCoord;
            if(compareCoordinates(rightDiagonal, desiredPosition)
            || compareCoordinates(leftDiagonal, desiredPosition))
            {
                possibleMovesForThisPawn.push_back(desiredPosition);
            }
        }
    }
    return possibleMovesForThisPawn;
}
vector<COORD> rookMoves(wchar_t pieceId, COORD pieceCoord)
{
    vector<COORD> possibleMovesForThisRook;
    //Calculates upward movement
    for(int coordY = pieceCoord.Y+upOffset; coordY >= 0; coordY -= 5)
    {
        COORD desiredPosition = {(SHORT)pieceCoord.X, (SHORT)coordY};
        bool canGo = true; //If can go to desired position
        bool final = false; //If can go to desired position by attacking other piece
        for(int i = 0; i < coordMapedPiecesPosition.size(); i++)
        {
            if(compareCoordinates(coordMapedPiecesPosition[i].pieceCoord, desiredPosition))
            {
                if(isupper(pieceId) && isupper(coordMapedPiecesPosition[i].pieceId))
                {
                    canGo = false;
                    break;
                }
                else if(islower(pieceId) && islower(coordMapedPiecesPosition[i].pieceId))
                {
                    canGo = false;
                    break;
                }
                else if(isupper(pieceId) && islower(coordMapedPiecesPosition[i].pieceId))
                {
                    final = true;
                    break;
                }
                else if(islower(pieceId) && isupper(coordMapedPiecesPosition[i].pieceId))
                {
                    final = true;
                    break;
                }
            }
        }
        if(canGo)
        {
            possibleMovesForThisRook.push_back(desiredPosition);
            if(final)
            {
                break;
            }
        }
        else if(!canGo)
        {
            break;
        }
    }
    //Calculates left movement
    for(int coordX = pieceCoord.X+leftOffset; coordX >= 0; coordX -= 10)
    {
        COORD desiredPosition = {(SHORT)coordX, (SHORT)pieceCoord.Y};
        bool canGo = true; //If can go to desired position
        bool final = false; //If can go to desired position by attacking other piece
        for(int i = 0; i < coordMapedPiecesPosition.size(); i++)
        {
            if(compareCoordinates(coordMapedPiecesPosition[i].pieceCoord, desiredPosition))
            {
                if(isupper(pieceId) && isupper(coordMapedPiecesPosition[i].pieceId))
                {
                    canGo = false;
                    break;
                }
                else if(islower(pieceId) && islower(coordMapedPiecesPosition[i].pieceId))
                {
                    canGo = false;
                    break;
                }
                else if(isupper(pieceId) && islower(coordMapedPiecesPosition[i].pieceId))
                {
                    final = true;
                    break;
                }
                else if(islower(pieceId) && isupper(coordMapedPiecesPosition[i].pieceId))
                {
                    final = true;
                    break;
                }
            }
        }
        if(canGo)
        {
            possibleMovesForThisRook.push_back(desiredPosition);
            if(final)
            {
                break;
            }
        }
        else if(!canGo)
        {
            break;
        }
    }
    //Calculates downward movements
    for(int coordY = pieceCoord.Y+downOffset; coordY < screenHeight; coordY += 5)
    {
        COORD desiredPosition = {(SHORT)pieceCoord.X, (SHORT)coordY};
        bool canGo = true; //If can go to desired position
        bool final = false; //If can go to desired position by attacking other piece
        for(int i = 0; i < coordMapedPiecesPosition.size(); i++)
        {
            if(compareCoordinates(coordMapedPiecesPosition[i].pieceCoord, desiredPosition))
            {
                if(isupper(pieceId) && isupper(coordMapedPiecesPosition[i].pieceId))
                {
                    canGo = false;
                    break;
                }
                else if(islower(pieceId) && islower(coordMapedPiecesPosition[i].pieceId))
                {
                    canGo = false;
                    break;
                }
                else if(isupper(pieceId) && islower(coordMapedPiecesPosition[i].pieceId))
                {
                    final = true;
                    break;
                }
                else if(islower(pieceId) && isupper(coordMapedPiecesPosition[i].pieceId))
                {
                    final = true;
                    break;
                }
            }
        }
        if(canGo)
        {
            possibleMovesForThisRook.push_back(desiredPosition);
            if(final)
            {
                break;
            }
        }
        else if(!canGo)
        {
            break;
        }
    }
    //Calculates right movements
    for(int coordX = pieceCoord.X+rightOffset; coordX < screenWidth; coordX += 10)
    {
        COORD desiredPosition = {(SHORT)coordX, (SHORT)pieceCoord.Y};
        bool canGo = true; //If can go to desired position
        bool final = false; //If can go to desired position by attacking other piece
        for(int i = 0; i < coordMapedPiecesPosition.size(); i++)
        {
            if(compareCoordinates(coordMapedPiecesPosition[i].pieceCoord, desiredPosition))
            {
                if(isupper(pieceId) && isupper(coordMapedPiecesPosition[i].pieceId))
                {
                    canGo = false;
                    break;
                }
                else if(islower(pieceId) && islower(coordMapedPiecesPosition[i].pieceId))
                {
                    canGo = false;
                    break;
                }
                else if(isupper(pieceId) && islower(coordMapedPiecesPosition[i].pieceId))
                {
                    final = true;
                    break;
                }
                else if(islower(pieceId) && isupper(coordMapedPiecesPosition[i].pieceId))
                {
                    final = true;
                    break;
                }
            }
        }
        if(canGo)
        {
            possibleMovesForThisRook.push_back(desiredPosition);
            if(final)
            {
                break;
            }
        }
        else if(!canGo)
        {
            break;
        }
    }

    return possibleMovesForThisRook;
}
vector<COORD> bishopMoves(wchar_t pieceId, COORD pieceCoord)
{
    vector<COORD> possibleMovesForThisBishop;
    //Up left diagonal
    for(int coordX = pieceCoord.X+leftOffset, coordY = pieceCoord.Y+upOffset;
    coordX >= 0 && coordY >= 0; coordX -= 10, coordY -= 5)
    {
        COORD desiredPosition = {(SHORT)coordX, (SHORT)coordY};
        bool canGo = true; //If can go to desired position
        bool final = false; //If can go to desired position by attacking other piece
        for(int i = 0; i < coordMapedPiecesPosition.size(); i++)
        {
            if(compareCoordinates(coordMapedPiecesPosition[i].pieceCoord, desiredPosition))
            {
                if(isupper(pieceId) && isupper(coordMapedPiecesPosition[i].pieceId))
                {
                    canGo = false;
                    break;
                }
                else if(islower(pieceId) && islower(coordMapedPiecesPosition[i].pieceId))
                {
                    canGo = false;
                    break;
                }
                else if(isupper(pieceId) && islower(coordMapedPiecesPosition[i].pieceId))
                {
                    final = true;
                    break;
                }
                else if(islower(pieceId) && isupper(coordMapedPiecesPosition[i].pieceId))
                {
                    final = true;
                    break;
                }                
            }
        }
        if(canGo)
        {
            possibleMovesForThisBishop.push_back(desiredPosition);
            if(final)
            {
                break;
            }
        }
        else if(!canGo)
        {
            break;
        }
    }
    //Up Right Diagonal
    for(int coordX = pieceCoord.X+rightOffset, coordY = pieceCoord.Y+upOffset;
    coordX < screenWidth && coordY >= 0; coordX += 10, coordY -= 5)
    {
        COORD desiredPosition = {(SHORT)coordX, (SHORT)coordY};
        bool canGo = true; //If can go to desired position
        bool final = false; //If can go to desired position by attacking other piece
        for(int i = 0; i < coordMapedPiecesPosition.size(); i++)
        {
            if(compareCoordinates(coordMapedPiecesPosition[i].pieceCoord, desiredPosition))
            {
                if(isupper(pieceId) && isupper(coordMapedPiecesPosition[i].pieceId))
                {
                    canGo = false;
                    break;
                }
                else if(islower(pieceId) && islower(coordMapedPiecesPosition[i].pieceId))
                {
                    canGo = false;
                    break;
                }
                else if(isupper(pieceId) && islower(coordMapedPiecesPosition[i].pieceId))
                {
                    final = true;
                    break;
                }
                else if(islower(pieceId) && isupper(coordMapedPiecesPosition[i].pieceId))
                {
                    final = true;
                    break;
                }                
            }
        }
        if(canGo)
        {
            possibleMovesForThisBishop.push_back(desiredPosition);
            if(final)
            {
                break;
            }
        }
        else if(!canGo)
        {
            break;
        }
    }
    //Down left diagonal
    for(int coordX = pieceCoord.X+leftOffset, coordY = pieceCoord.Y+downOffset;
    coordX >= 0 && coordY < screenHeight; coordX -= 10, coordY += 5)
    {
        COORD desiredPosition = {(SHORT)coordX, (SHORT)coordY};
        bool canGo = true; //If can go to desired position
        bool final = false; //If can go to desired position by attacking other piece
        for(int i = 0; i < coordMapedPiecesPosition.size(); i++)
        {
            if(compareCoordinates(coordMapedPiecesPosition[i].pieceCoord, desiredPosition))
            {
                if(isupper(pieceId) && isupper(coordMapedPiecesPosition[i].pieceId))
                {
                    canGo = false;
                    break;
                }
                else if(islower(pieceId) && islower(coordMapedPiecesPosition[i].pieceId))
                {
                    canGo = false;
                    break;
                }
                else if(isupper(pieceId) && islower(coordMapedPiecesPosition[i].pieceId))
                {
                    final = true;
                    break;
                }
                else if(islower(pieceId) && isupper(coordMapedPiecesPosition[i].pieceId))
                {
                    final = true;
                    break;
                }                
            }
        }
        if(canGo)
        {
            possibleMovesForThisBishop.push_back(desiredPosition);
            if(final)
            {
                break;
            }
        }
        else if(!canGo)
        {
            break;
        }
    }
    //Down right diagonal
    for(int coordX = pieceCoord.X+rightOffset, coordY = pieceCoord.Y+downOffset;
    coordX < screenWidth && coordY < screenHeight; coordX += 10, coordY += 5)
    {
        COORD desiredPosition = {(SHORT)coordX, (SHORT)coordY};
        bool canGo = true; //If can go to desired position
        bool final = false; //If can go to desired position by attacking other piece
        for(int i = 0; i < coordMapedPiecesPosition.size(); i++)
        {
            if(compareCoordinates(coordMapedPiecesPosition[i].pieceCoord, desiredPosition))
            {
                if(isupper(pieceId) && isupper(coordMapedPiecesPosition[i].pieceId))
                {
                    canGo = false;
                    break;
                }
                else if(islower(pieceId) && islower(coordMapedPiecesPosition[i].pieceId))
                {
                    canGo = false;
                    break;
                }
                else if(isupper(pieceId) && islower(coordMapedPiecesPosition[i].pieceId))
                {
                    final = true;
                    break;
                }
                else if(islower(pieceId) && isupper(coordMapedPiecesPosition[i].pieceId))
                {
                    final = true;
                    break;
                }                
            }
        }
        if(canGo)
        {
            possibleMovesForThisBishop.push_back(desiredPosition);
            if(final)
            {
                break;
            }
        }
        else if(!canGo)
        {
            break;
        }
    }

    return possibleMovesForThisBishop;
}
vector<COORD> queenMoves(wchar_t pieceId, COORD pieceCoord)
{
    vector<COORD> possibleMovesForThisQueen = bishopMoves(pieceId, pieceCoord);
    vector<COORD> straightMovements = rookMoves(pieceId, pieceCoord);
    possibleMovesForThisQueen.insert(possibleMovesForThisQueen.end(), straightMovements.begin(), straightMovements.end());

    return possibleMovesForThisQueen;
}
vector<COORD> knightMoves(wchar_t pieceId, COORD pieceCoord)
{
    vector<COORD> possibleMovesForThisKnight;
    possibleMovesForThisKnight.push_back({(SHORT)(pieceCoord.X-10), (SHORT)(pieceCoord.Y+10)}); //Down Left    
    possibleMovesForThisKnight.push_back({(SHORT)(pieceCoord.X+10), (SHORT)(pieceCoord.Y-10)}); //Up Right
    possibleMovesForThisKnight.push_back({(SHORT)(pieceCoord.X-10), (SHORT)(pieceCoord.Y-10)}); //Up left
    possibleMovesForThisKnight.push_back({(SHORT)(pieceCoord.X+10), (SHORT)(pieceCoord.Y+10)}); //Down right
    possibleMovesForThisKnight.push_back({(SHORT)(pieceCoord.X-20), (SHORT)(pieceCoord.Y+5)});  //Left down
    possibleMovesForThisKnight.push_back({(SHORT)(pieceCoord.X-20), (SHORT)(pieceCoord.Y-5)});  //Left up
    possibleMovesForThisKnight.push_back({(SHORT)(pieceCoord.X+20), (SHORT)(pieceCoord.Y+5)});  //Right down
    possibleMovesForThisKnight.push_back({(SHORT)(pieceCoord.X+20), (SHORT)(pieceCoord.Y-5)});  //Right up

    //Check if the position its not out of bond or ontop of allied pieces
    for(int i = 0; i < coordMapedPiecesPosition.size(); i++)
    {
        for(int j = 0; j < possibleMovesForThisKnight.size(); j++)
        {
            if(possibleMovesForThisKnight[j].X < 0 || possibleMovesForThisKnight[j].Y < 0)
            {
                possibleMovesForThisKnight.erase(possibleMovesForThisKnight.begin()+j);
                continue;
            }
            else if(compareCoordinates(possibleMovesForThisKnight[j], coordMapedPiecesPosition[i].pieceCoord))
            {
                if(isupper(pieceId) && isupper(coordMapedPiecesPosition[i].pieceId))
                {
                    possibleMovesForThisKnight.erase(possibleMovesForThisKnight.begin()+j);
                    continue;
                }
                else if(islower(pieceId) && islower(coordMapedPiecesPosition[i].pieceId))
                {
                    possibleMovesForThisKnight.erase(possibleMovesForThisKnight.begin()+j);
                    continue;
                }
            }
        }
    }

    return possibleMovesForThisKnight;
}
vector<COORD> kingMoves(wchar_t pieceId, COORD pieceCoord)
{
    vector<COORD> possibleMovesForThisKing;
    //DiagBaixoEsquerda / DiagBaixoDireita / DiagCimaEsquerda / DiagCimaDireita
    //Esquerda / Direita / Baixo / Cima
    possibleMovesForThisKing.push_back({(SHORT)(pieceCoord.X-10), (SHORT)(pieceCoord.Y+5)}); //Diagonal down left
    possibleMovesForThisKing.push_back({(SHORT)(pieceCoord.X+10), (SHORT)(pieceCoord.Y+5)}); //Diagonal down right
    possibleMovesForThisKing.push_back({(SHORT)(pieceCoord.X-10), (SHORT)(pieceCoord.Y-5)}); //Diagonal up left
    possibleMovesForThisKing.push_back({(SHORT)(pieceCoord.X+10), (SHORT)(pieceCoord.Y-5)}); //Diagonal up right
    possibleMovesForThisKing.push_back({(SHORT)(pieceCoord.X-10), (SHORT)(pieceCoord.Y)});   //Left
    possibleMovesForThisKing.push_back({(SHORT)(pieceCoord.X+10), (SHORT)(pieceCoord.Y)});   //Right
    possibleMovesForThisKing.push_back({(SHORT)(pieceCoord.X), (SHORT)(pieceCoord.Y+5)});    //Down
    possibleMovesForThisKing.push_back({(SHORT)(pieceCoord.X), (SHORT)(pieceCoord.Y-5)});    //Up

    //Check if the position its not out of bond or ontop of allied pieces
    for(int i = 0; i < coordMapedPiecesPosition.size(); i++)
    {
        for(int j = 0; j < possibleMovesForThisKing.size(); j++)
        {
            if(possibleMovesForThisKing[j].X < 0 || possibleMovesForThisKing[j].Y < 0)
            {
                possibleMovesForThisKing.erase(possibleMovesForThisKing.begin()+j);
                continue;
            }
            else if(possibleMovesForThisKing[j].X > 70 || possibleMovesForThisKing[j].Y > 35)
            {
                possibleMovesForThisKing.erase(possibleMovesForThisKing.begin()+j);
                continue;
            }
            else if(compareCoordinates(possibleMovesForThisKing[j], coordMapedPiecesPosition[i].pieceCoord))
            {
                if(isupper(pieceId) && isupper(coordMapedPiecesPosition[i].pieceId))
                {
                    possibleMovesForThisKing.erase(possibleMovesForThisKing.begin()+j);
                    continue;
                }
                else if(islower(pieceId) && islower(coordMapedPiecesPosition[i].pieceId))
                {
                    possibleMovesForThisKing.erase(possibleMovesForThisKing.begin()+j);
                    continue;
                }
            }
        }
    }

    return possibleMovesForThisKing;
}
//This function will automaticaly detect the necessary move function for a unknown piece ID
vector<COORD> calculateMoves(wchar_t pieceId, COORD pieceCoord)
{
    if(pieceId == 'P' || pieceId == 'p')
    {
        vector<COORD> possibleMovesForThisPiece = pawnMoves(pieceId, pieceCoord);
        return possibleMovesForThisPiece;
    }
    else if(pieceId == 'T' || pieceId == 't')
    {
        vector<COORD> possibleMovesForThisPiece = rookMoves(pieceId, pieceCoord);
        return possibleMovesForThisPiece;
    }
    else if(pieceId == 'B' || pieceId == 'b')
    {
        vector<COORD> possibleMovesForThisPiece = bishopMoves(pieceId, pieceCoord);
        return possibleMovesForThisPiece;
    }
    else if(pieceId == 'D' || pieceId == 'd')
    {
        vector<COORD> possibleMovesForThisPiece = queenMoves(pieceId, pieceCoord);
        return possibleMovesForThisPiece;
    }
    else if(pieceId == 'C' || pieceId == 'c')
    {
        vector<COORD> possibleMovesForThisPiece = knightMoves(pieceId, pieceCoord);
        return possibleMovesForThisPiece;
    }
    else if(pieceId == 'R' || pieceId == 'r')
    {
        vector<COORD> possibleMovesForThisPiece = kingMoves(pieceId, pieceCoord);
        return possibleMovesForThisPiece;
    }
}
//This functions cast move rays from the king that simulates other pieces moves, used to detect check
bool castRaysFromTheKing(wchar_t pieceId, COORD desiredCoord)
{
    //Creates a backup that will be used after the simulation, since the simulation messes with the original one
    vector<PieceData> coordMapedPiecesPositionBackup = coordMapedPiecesPosition;
    for(int i = 0; i < coordMapedPiecesPosition.size(); i++)
    {
        wchar_t pieceIdToBeAnalised = coordMapedPiecesPosition[i].pieceId;
        COORD pieceCoordToBeAnalised = coordMapedPiecesPosition[i].pieceCoord;
        //See if there is another piece on the desiredCoord to cast the rays (only applies when it differs from the king coord, more on that later)
        //If so, see if there is enemies in that position, if true simulate an attack at that enemy, after that (attacking or not) changes the king coord to the desired one
        if(compareCoordinates(pieceCoordToBeAnalised, desiredCoord))
        {
            if(isupper(pieceIdToBeAnalised) && islower(pieceId))
            {
                coordMapedPiecesPosition.erase(coordMapedPiecesPosition.begin()+i);
                break;
            }
            else if(islower(pieceIdToBeAnalised) && isupper(pieceId))
            {
                coordMapedPiecesPosition.erase(coordMapedPiecesPosition.begin()+i);
                break;
            }
        }
        else if(pieceIdToBeAnalised == pieceId)
        {
            coordMapedPiecesPosition[i].defineCoord(desiredCoord);
        }
    }

    vector<COORD> simulateKnight = knightMoves(pieceId, desiredCoord);
    vector<COORD> simulateQueen = queenMoves(pieceId, desiredCoord); //Include the moves of Rooks and Bishops
    vector<COORD> simulatePawn = pawnMoves(pieceId, desiredCoord);

    //Will check every coord on these simulations, if any of them have a attack possibility it means that the king is (or would be) on check, returning false
    for(int i = 0; i < coordMapedPiecesPosition.size(); i++)
    {
        //Diagonals and Straights
        for(int j = 0; j < simulateQueen.size(); j++)
        {
            if(compareCoordinates(coordMapedPiecesPosition[i].pieceCoord, simulateQueen[j]))
            {
                if(isupper(pieceId))
                {
                    if(coordMapedPiecesPosition[i].pieceId == 'd'
                    || (coordMapedPiecesPosition[i].pieceId == 'b' && (desiredCoord.X != coordMapedPiecesPosition[i].pieceCoord.X && desiredCoord.Y != coordMapedPiecesPosition[i].pieceCoord.Y ))
                    || (coordMapedPiecesPosition[i].pieceId == 't' && (desiredCoord.X == coordMapedPiecesPosition[i].pieceCoord.X || desiredCoord.Y == coordMapedPiecesPosition[i].pieceCoord.Y )))
                    {
                        coordMapedPiecesPosition = coordMapedPiecesPositionBackup;
                        return false;
                    }   
                }
                else if(islower(pieceId))
                {
                    if(coordMapedPiecesPosition[i].pieceId == 'D'
                    || (coordMapedPiecesPosition[i].pieceId == 'B' && (desiredCoord.X != coordMapedPiecesPosition[i].pieceCoord.X && desiredCoord.Y != coordMapedPiecesPosition[i].pieceCoord.Y ))
                    || (coordMapedPiecesPosition[i].pieceId == 'T' && (desiredCoord.X == coordMapedPiecesPosition[i].pieceCoord.X || desiredCoord.Y == coordMapedPiecesPosition[i].pieceCoord.Y )))
                    {
                        coordMapedPiecesPosition = coordMapedPiecesPositionBackup;
                        return false;
                    }   
                }
            }
        }
        //Knight
        for(int j = 0; j < simulateKnight.size(); j++)
        {
            if(compareCoordinates(coordMapedPiecesPosition[i].pieceCoord, simulateKnight[j]))
            {
                if(isupper(pieceId))
                {
                    if(coordMapedPiecesPosition[i].pieceId == 'c')
                    {
                        coordMapedPiecesPosition = coordMapedPiecesPositionBackup;
                        return false;
                    }
                }
                else if(islower(pieceId))
                {
                    if(coordMapedPiecesPosition[i].pieceId == 'C')
                    {
                        coordMapedPiecesPosition = coordMapedPiecesPositionBackup;
                        return false;
                    }
                }
            }
        }
        //Pawn
        for(int j = 0; j < simulatePawn.size(); j++)
        {
            if(compareCoordinates(coordMapedPiecesPosition[i].pieceCoord, simulatePawn[j]))
            {
                if(desiredCoord.X != coordMapedPiecesPosition[i].pieceCoord.X)
                {
                    if(isupper(pieceId))
                    {
                        if(coordMapedPiecesPosition[i].pieceId == 'p')
                        {
                            coordMapedPiecesPosition = coordMapedPiecesPositionBackup;
                            return false;
                        }
                    }
                    else if(islower(pieceId))
                    {
                        if(coordMapedPiecesPosition[i].pieceId == 'P')
                        {
                            coordMapedPiecesPosition = coordMapedPiecesPositionBackup;
                            return false;
                        }
                    }
                }
            }
        }
    }
    //If all the tests passes and the function didnt return, the king is safe and the backup is restaured
    coordMapedPiecesPosition = coordMapedPiecesPositionBackup;
    return true;
}
//Check if the king can go to a desired coord, first checking if this coord is in possibleMoves and then checking if it would be on check
bool theKingCanGo(wchar_t pieceId, COORD pieceCoord, COORD desiredCoord)
{
    vector<COORD> generalKingMoves = kingMoves(pieceId, pieceCoord);

    bool hasInGeneralMoves = false;
    for(int i = 0; i < generalKingMoves.size(); i++)
    {
        if(compareCoordinates(generalKingMoves[i], desiredCoord))
        {
            hasInGeneralMoves = true;
            break;
        }
    }
    if(!hasInGeneralMoves) return false;

    return castRaysFromTheKing(pieceId, desiredCoord);
}
//Calculates if the king its safe, on check or in checkmate
int safeCheckOrMate(wchar_t pieceId, COORD pieceCoord)
{
    vector<COORD> possibleMovesForThisPiece = kingMoves(pieceId, pieceCoord);

    //If the castRaysFromTheKing returns false it means check on that coord
    if(!castRaysFromTheKing(pieceId, pieceCoord))
    {
        //Will try to find a escape that the king can do alone without ally moves
        vector<COORD> posibleEscapes;
        for(int i = 0; i < possibleMovesForThisPiece.size();i++)
        {
            if(castRaysFromTheKing(pieceId, possibleMovesForThisPiece[i]))
            {
                posibleEscapes.push_back(possibleMovesForThisPiece[i]);
            }
        }
        //If the king can get to safety alone it means check and just check, so there is no need to calculate nothing more, return 1
        if(posibleEscapes.size() > 0) return 1;
        //If he cant, this else if is responsible to detect if his allies can save him
        //This is done simulating every move from every ally and checking if any of then makes the king safe
        //If one does, the function stops and return 1, "just" check
        else if(posibleEscapes.size() == 0)
        {
            vector<PieceData> coordMapedPiecesPositionBackup = coordMapedPiecesPosition;
            for(int i = 0; i < coordMapedPiecesPosition.size(); i++)
            {
                coordMapedPiecesPosition = coordMapedPiecesPositionBackup;
                if(isupper(pieceId) && isupper(coordMapedPiecesPosition[i].pieceId))
                {
                    vector<COORD> movimentosDoAmigo = calculateMoves(coordMapedPiecesPosition[i].pieceId, coordMapedPiecesPosition[i].pieceCoord);
                    for(int j = 0; j < movimentosDoAmigo.size(); j++)
                    {
                        COORD coordAmigoOriginal = coordMapedPiecesPosition[i].pieceCoord;
                        coordMapedPiecesPosition[i].defineCoord(movimentosDoAmigo[j]);
                        if(castRaysFromTheKing(pieceId, pieceCoord))
                        {
                            coordMapedPiecesPosition = coordMapedPiecesPositionBackup;
                            return 1;
                        }
                        else
                        {
                            coordMapedPiecesPosition[i].defineCoord(coordAmigoOriginal);
                        }
                    }
                }
                else if(islower(pieceId) && islower(coordMapedPiecesPosition[i].pieceId))
                {
                    vector<COORD> movimentosDoAmigo = calculateMoves(coordMapedPiecesPosition[i].pieceId, coordMapedPiecesPosition[i].pieceCoord);
                    for(int j = 0; j < movimentosDoAmigo.size(); j++)
                    {
                        COORD coordAmigoOriginal = coordMapedPiecesPosition[i].pieceCoord;
                        coordMapedPiecesPosition[i].defineCoord(movimentosDoAmigo[j]);
                        if(castRaysFromTheKing(pieceId, pieceCoord))
                        {
                            coordMapedPiecesPosition = coordMapedPiecesPositionBackup;
                            return 1;
                        }
                        else
                        {
                            coordMapedPiecesPosition[i].defineCoord(coordAmigoOriginal);
                        }
                    }
                }
            }
            //If any of them can save the king, and the king can do it either, return 2, checkmate
            coordMapedPiecesPosition = coordMapedPiecesPositionBackup;
            return 2;
        }
    }
    //If fails on the first if, it means safety, return 0
    return 0;
}
//Calculates if the king can castle with one of its rooks
bool canCastle(wchar_t pieceId, COORD pieceCoord, COORD desiredCoord)
{
    //It return false if the king moved or if its two rooks moved
    if(isupper(pieceId) && whiteKingMoved)
    {
        return false;
    }
    else if(isupper(pieceId) && rightWhiteRookMoved && leftWhiteRookMoved)
    {
        return false;
    }
    else if(islower(pieceId) && blackKingMoved)
    {
        return false;
    }
    else if(islower(pieceId) && rightBlackRookMoved && leftBlackRookMoved)
    {
        return false;
    }
    /*
        Calculates by first setting the two Castle envolved coords, being the secondCastleCoord the one closest to the king
        After that calculates the rook movement and see if the one closest to the king its in its moves, if so, it means that nothing its betwen then
        Then check if castle envolved coord would not be in check, if not, changes the tower pos on piecesPosition and return true
    */
    else if(isupper(pieceId) && safeCheckOrMate(pieceId, pieceCoord) == 0)
    {
        //Long Caslte
        if(desiredCoord.X == 20 && !leftWhiteRookMoved)
        {
            COORD firstCastleCoord = {(SHORT)20, (SHORT) 35}, secondCastleCoord = {(SHORT)30, (SHORT) 35};
            vector<COORD> rookMovements = rookMoves(pieceId, leftWhiteRookInitialCoord);
            bool cleanPathToTheKing = false;
            for(int i = 0; i < rookMovements.size(); i++)
            {
                if(compareCoordinates(rookMovements[i], secondCastleCoord))
                {
                    cleanPathToTheKing = true;
                    break;
                }
            }
            if(!cleanPathToTheKing) return false;

            if(safeCheckOrMate('R', firstCastleCoord) == 0 && safeCheckOrMate('R', secondCastleCoord) == 0)
            {
                COORD rookCoordPosCastle = reduceCoord(secondCastleCoord);
                COORD rookCoordPreCastle = reduceCoord(leftWhiteRookInitialCoord);
                int xPreCastle = (int)rookCoordPreCastle.X, yPreCastle = (int)rookCoordPreCastle.Y;
                int xPosCastle = (int)rookCoordPosCastle.X, yPosCastle = (int)rookCoordPosCastle.Y;
                
                piecesPositon[yPreCastle*mapWidth+xPreCastle] = '.';
                piecesPositon[yPosCastle*mapWidth+xPosCastle] = 'T';
                leftWhiteRookMoved = true;
                return true;
            }
        }
        //Short Castle
        else if(desiredCoord.X == 60 && !rightWhiteRookMoved)
        {
            COORD firstCastleCoord = {(SHORT)60, (SHORT) 35}, secondCastleCoord = {(SHORT)50, (SHORT) 35};
            vector<COORD> rookMovements = rookMoves(pieceId, rightWhiteRookInitialCoord);
            bool cleanPathToTheKing = false;
            for(int i = 0; i < rookMovements.size(); i++)
            {
                if(compareCoordinates(rookMovements[i], secondCastleCoord))
                {
                    cleanPathToTheKing = true;
                    break;
                }
            }
            if(!cleanPathToTheKing) return false;
            if(safeCheckOrMate('R', firstCastleCoord) == 0 && safeCheckOrMate('R', secondCastleCoord) == 0)
            {
                COORD rookCoordPosCastle = reduceCoord(secondCastleCoord);
                COORD rookCoordPreCastle = reduceCoord(rightWhiteRookInitialCoord);
                int xPreCastle = (int)rookCoordPreCastle.X, yPreCastle = (int)rookCoordPreCastle.Y;
                int xPosCastle = (int)rookCoordPosCastle.X, yPosCastle = (int)rookCoordPosCastle.Y;
                
                piecesPositon[yPreCastle*mapWidth+xPreCastle] = '.';
                piecesPositon[yPosCastle*mapWidth+xPosCastle] = 'T';
                rightWhiteRookMoved = true;
                return true;                
            }
        }
    }
    else if(islower(pieceId) && safeCheckOrMate(pieceId, pieceCoord) == 0)
    {
        //Long Caslte
        if(desiredCoord.X == 20 && !leftBlackRookMoved)
        {
            COORD firstCastleCoord = {(SHORT)20, (SHORT) 0}, secondCastleCoord = {(SHORT)30, (SHORT) 0};
            vector<COORD> rookMovements = rookMoves(pieceId, leftBlackRookInitialCoord);
            bool cleanPathToTheKing = false;
            for(int i = 0; i < rookMovements.size(); i++)
            {
                if(compareCoordinates(rookMovements[i], secondCastleCoord))
                {
                    cleanPathToTheKing = true;
                    break;
                }
            }
            if(!cleanPathToTheKing) return false;
            if(safeCheckOrMate('r', firstCastleCoord) == 0 && safeCheckOrMate('r', secondCastleCoord) == 0)
            {
                COORD rookCoordPosCastle = reduceCoord(secondCastleCoord);
                COORD rookCoordPreCastle = reduceCoord(leftBlackRookInitialCoord);
                int xPreCastle = (int)rookCoordPreCastle.X, yPreCastle = (int)rookCoordPreCastle.Y;
                int xPosCastle = (int)rookCoordPosCastle.X, yPosCastle = (int)rookCoordPosCastle.Y;
                
                piecesPositon[yPreCastle*mapWidth+xPreCastle] = '.';
                piecesPositon[yPosCastle*mapWidth+xPosCastle] = 't';
                leftBlackRookMoved = true;
                return true; 
            }
        }
        //Short Castle
        else if(desiredCoord.X == 60 && !rightBlackRookMoved)
        {
            COORD firstCastleCoord = {(SHORT)60, (SHORT) 0}, secondCastleCoord = {(SHORT)50, (SHORT) 0};
            vector<COORD> rookMovements = rookMoves(pieceId, rightBlackRookInitialCoord);
            bool cleanPathToTheKing = false;
            for(int i = 0; i < rookMovements.size(); i++)
            {
                if(compareCoordinates(rookMovements[i], secondCastleCoord))
                {
                    cleanPathToTheKing = true;
                    break;
                }
            }
            if(!cleanPathToTheKing) return false;
            if(safeCheckOrMate('r', firstCastleCoord) == 0 && safeCheckOrMate('r', secondCastleCoord) == 0)
            {
                COORD rookCoordPosCastle = reduceCoord(secondCastleCoord);
                COORD rookCoordPreCastle = reduceCoord(rightBlackRookInitialCoord);
                int xPreCastle = (int)rookCoordPreCastle.X, yPreCastle = (int)rookCoordPreCastle.Y;
                int xPosCastle = (int)rookCoordPosCastle.X, yPosCastle = (int)rookCoordPosCastle.Y;
                
                piecesPositon[yPreCastle*mapWidth+xPreCastle] = '.';
                piecesPositon[yPosCastle*mapWidth+xPosCastle] = 't';
                rightBlackRookMoved = true;
                return true; 
            }
        }
    }
    //If pass trought everything and reach this line, just return false
    return false;
}
//Just save some time downwards simple calculating if desired coord is in the possibleCoords of some piece
bool checkIfDesiredCoordIsInPossibleCoords(COORD desiredCoord, vector<COORD> posibleCoords)
{
    for(int i = 0; i < posibleCoords.size(); i++)
    {
        if(compareCoordinates(posibleCoords[i], desiredCoord))
        {
            return true;
        }
    }
    return false;
}
//Check if a piece can move without putting the king in danger
bool thePieceCanMoveWithoutRiskingTheKing(wchar_t pieceId, COORD pieceCoord, COORD desiredCoord)
{
    vector<PieceData> coordMapedPiecesPositionBackup = coordMapedPiecesPosition;
    for(int i = 0; i < coordMapedPiecesPosition.size(); i++)
    {
        if(compareCoordinates(coordMapedPiecesPosition[i].pieceCoord, pieceCoord))
        {
            coordMapedPiecesPosition[i].defineCoord(desiredCoord);
            break;
        }
    }
    if(isupper(pieceId))
    {
        if(safeCheckOrMate('R', whiteKingCoord) != 0)
        {
            coordMapedPiecesPosition = coordMapedPiecesPositionBackup;
            return false;
        }
        else
        {
            coordMapedPiecesPosition = coordMapedPiecesPositionBackup;
            return true;
        }
    }
    if(islower(pieceId))
    {
        if(safeCheckOrMate('r', blackKingCoord) != 0)
        {
            coordMapedPiecesPosition = coordMapedPiecesPositionBackup;
            return false;
        }
        else
        {
            coordMapedPiecesPosition = coordMapedPiecesPositionBackup;
            return true;
        }
    }
    return false;
}
//This function its the convergence point of this hpp, it will detect the piece id and do the necessary checks to se if it can move or not
bool canMove(wchar_t pieceId, COORD pieceCoord, COORD desiredCoord)
{
    if(pieceId == 'P' || pieceId == 'p')
    {
        vector<COORD> possibleMovesForThisPiece = pawnMoves(pieceId, pieceCoord);
        if(isupper(pieceId))
        {
            if(pieceCoord.Y-desiredCoord.Y == 10 && checkIfDesiredCoordIsInPossibleCoords(desiredCoord, possibleMovesForThisPiece)
            && thePieceCanMoveWithoutRiskingTheKing(pieceId, pieceCoord, desiredCoord))
            {
                COORD enPassantAttackCoord = {(SHORT)(pieceCoord.X), (SHORT)(pieceCoord.Y-5)};
                enPassant.defineEnPassantData(true, enPassantAttackCoord, desiredCoord);
                return true;
            }
            else if(checkIfDesiredCoordIsInPossibleCoords(desiredCoord, possibleMovesForThisPiece)
            && thePieceCanMoveWithoutRiskingTheKing(pieceId, pieceCoord, desiredCoord))
            {
                enPassant.canSufferEnPassant = false;
                return true;
            }
            else
            {
                return false;
            }
        } 
        else if(islower(pieceId))
        {
            if(desiredCoord.Y-pieceCoord.Y == 10 && checkIfDesiredCoordIsInPossibleCoords(desiredCoord, possibleMovesForThisPiece)
            && thePieceCanMoveWithoutRiskingTheKing(pieceId, pieceCoord, desiredCoord))
            {
                COORD enPassantAttackCoord = {(SHORT)(pieceCoord.X), (SHORT)(pieceCoord.Y+5)};
                enPassant.defineEnPassantData(true, enPassantAttackCoord, desiredCoord);
                return true;
            }
            else if(checkIfDesiredCoordIsInPossibleCoords(desiredCoord, possibleMovesForThisPiece)
            && thePieceCanMoveWithoutRiskingTheKing(pieceId, pieceCoord, desiredCoord))
            {
                enPassant.canSufferEnPassant = false;
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    else if(pieceId == 'T' || pieceId == 't')
    {
        vector<COORD> possibleMovesForThisPiece = rookMoves(pieceId, pieceCoord);
        if(checkIfDesiredCoordIsInPossibleCoords(desiredCoord, possibleMovesForThisPiece)
        && thePieceCanMoveWithoutRiskingTheKing(pieceId, pieceCoord, desiredCoord))
        {
            if(compareCoordinates(pieceCoord, rightWhiteRookInitialCoord))
            {
                rightWhiteRookMoved = true;
                return true;
            }
            else if(compareCoordinates(pieceCoord, leftWhiteRookInitialCoord))
            {
                leftWhiteRookMoved = true;
                return true;
            }
            else if(compareCoordinates(pieceCoord, rightBlackRookInitialCoord))
            {
                rightBlackRookMoved = true;
                return true;
            }
            else if(compareCoordinates(pieceCoord, leftBlackRookInitialCoord))
            {
                leftBlackRookMoved = true;
                return true;
            }
            else
            {
                return true;
            }
        }
        else
        {
            return false;
        }
    }
    else if(pieceId == 'B' || pieceId == 'b')
    {
        vector<COORD> possibleMovesForThisPiece = bishopMoves(pieceId, pieceCoord);
        if(checkIfDesiredCoordIsInPossibleCoords(desiredCoord, possibleMovesForThisPiece) && thePieceCanMoveWithoutRiskingTheKing(pieceId, pieceCoord, desiredCoord))
        {
            return true;
        }
        else
        {
            return false;
        }
    } 
    else if(pieceId == 'D' || pieceId == 'd')
    {
        vector<COORD> possibleMovesForThisPiece = queenMoves(pieceId, pieceCoord);
        if(checkIfDesiredCoordIsInPossibleCoords(desiredCoord, possibleMovesForThisPiece) && thePieceCanMoveWithoutRiskingTheKing(pieceId, pieceCoord, desiredCoord))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if(pieceId == 'C' || pieceId == 'c')
    {
        vector<COORD> possibleMovesForThisPiece = knightMoves(pieceId, pieceCoord);
        if(checkIfDesiredCoordIsInPossibleCoords(desiredCoord, possibleMovesForThisPiece) && thePieceCanMoveWithoutRiskingTheKing(pieceId, pieceCoord, desiredCoord))
        {
            return true;
        }
        else
        {
            return false;
        } 
    }
    else if(pieceId == 'R' || pieceId == 'r')
    {
        if(desiredCoord.X - pieceCoord.X == 20 || pieceCoord.X - desiredCoord.X == 20)
        {
            if(canCastle(pieceId, pieceCoord, desiredCoord))
            {
                if(compareCoordinates(pieceCoord, whiteKingInitialCoord))
                {
                    whiteKingCoord = desiredCoord;
                    whiteKingMoved = true;
                    return true;
                }
                else if(compareCoordinates(pieceCoord, blackKingInitialCoord))
                {
                    blackKingCoord = desiredCoord;
                    blackKingMoved = true;
                    return true;
                }
                else if(isupper(pieceId))
                {
                    whiteKingCoord = desiredCoord;
                    return true;
                }
                else if(islower(pieceId))
                {
                    blackKingCoord = desiredCoord;
                    return true;
                }
            }
        }
        else if(theKingCanGo(pieceId, pieceCoord, desiredCoord))
        {
            if(compareCoordinates(pieceCoord, whiteKingInitialCoord))
            {
                whiteKingCoord = desiredCoord;
                whiteKingMoved = true;
                return true;
            }
            else if(compareCoordinates(pieceCoord, blackKingInitialCoord))
            {
                blackKingCoord = desiredCoord;
                blackKingMoved = true;
                return true;
            }
            else if(isupper(pieceId))
            {
                whiteKingCoord = desiredCoord;
                return true;
            }
            else if(islower(pieceId))
            {
                blackKingCoord = desiredCoord;
                return true;
            }
        }
    }
    return false;
}