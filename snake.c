// snake02.c
// Mochilote - www.cpcmania.com
////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TILE_HEIGHT 10  //pixel
#define TILE_WIDTH 8  //pixel (4 bytes) 
#define MODE0_HEIGHT 200
#define MODE0_WIDTH 160
#define NUM_TILES_WIDTH MODE0_WIDTH / TILE_WIDTH
#define NUM_TILES_HEIGHT MODE0_HEIGHT / TILE_HEIGHT

enum _eTileType
{
  TileType_None,
  TileType_Border,
  TileType_Rock,
  TileType_Snake
}_eTileType;

enum _eTileType aBackgroundTiles[NUM_TILES_WIDTH][NUM_TILES_HEIGHT]; //20x20

#define NUM_COLORS 4
const unsigned char Palette[NUM_COLORS] = {0, 26, 12, 6};

typedef struct _tSnakePiece
{
  unsigned char nX;
  unsigned char nY;
}_tSnakePiece;

#define MAX_SNAKE_PIECES 50

_tSnakePiece aSnake[MAX_SNAKE_PIECES];
unsigned int nSnakePieces = 0;

enum _eDirection
{
  Direction_Up,
  Direction_Down,
  Direction_Left,
  Direction_Right
}_eDirection;

enum _eDirection eDirection = Direction_Right;

////////////////////////////////////////////////////////////////////////
//GetTime()
////////////////////////////////////////////////////////////////////////
unsigned char char3,char4;

unsigned int GetTime()
{
  unsigned int nTime = 0;

  __asm
    CALL #0xBD0D ;KL TIME PLEASE
    PUSH HL
    POP DE
    LD HL, #_char3
    LD (HL), D
    LD HL, #_char4
    LD (HL), E
  __endasm;

  nTime = (char3 << 8) + char4;

  return nTime;
}
////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////
//GetChar()
////////////////////////////////////////////////////////////////////////
char nGetChar;
char GetChar()
{
  __asm
    LD HL, #_nGetChar
    LD (HL), #0
    CALL #0xBB09 ;KM READ CHAR
    JP NC, _end_getchar
    LD (HL), A
    _end_getchar:
  __endasm;
  
  return nGetChar;
}
////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////
//DrawTile
////////////////////////////////////////////////////////////////////////
void DrawTile(unsigned char nTileX, unsigned char nTileY)
{
  enum _eTileType eTileType = aBackgroundTiles[nTileX][nTileY];
  unsigned int nRow = 0;

  for(nRow = 0; nRow < TILE_HEIGHT; nRow++)
  {
    unsigned int nY = nTileY * TILE_HEIGHT + nRow;
    unsigned int nX = nTileX * TILE_WIDTH;
    unsigned char *pScreen = (unsigned char *)0xC000 + ((nY / 8) * 80) + ((nY % 8) * 2048) + (nX / 2);
    unsigned char nColor = 0;
    
    switch(eTileType)
    {
      case TileType_None: nColor = 0; break;
      case TileType_Border: nColor = 192; break; //11000000
      case TileType_Rock: nColor = 12; break; //00001100
      case TileType_Snake: nColor = 204; break; //11001100
    }

    memset(pScreen, nColor, TILE_WIDTH / 2);
  }
}
////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////
//SetColor
////////////////////////////////////////////////////////////////////////
void SetColor(unsigned char nColorIndex, unsigned char nPaletteIndex)
{
  __asm
    ld a, 4 (ix)
    ld b, 5 (ix)
    ld c, b
    call #0xBC32 ;SCR SET INK
  __endasm;
}
////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////
//SetMode
////////////////////////////////////////////////////////////////////////
void SetMode(unsigned char nMode)
{
  __asm
    ld a, 4 (ix)
    call #0xBC0E ;SCR_SET_MODE
  __endasm;
}
////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////
//SetCursor
////////////////////////////////////////////////////////////////////////
void SetCursor(unsigned char nColum, unsigned char nLine)
{
  __asm
    ld h, 4 (ix)
    ld l, 5 (ix)
    call #0xBB75 ;TXT SET CURSOR
  __endasm;
}
////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////
//InitMode0
////////////////////////////////////////////////////////////////////////
void InitMode0()
{
  SetMode(0);

  //SCR SET BORDER 0
  __asm
    ld b, #0 ;black
    ld c, b
    call #0xBC38
  __endasm;
}
////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////
//InitGame
////////////////////////////////////////////////////////////////////////
void InitGame()
{
  unsigned char nColor = 0;
  unsigned int nX = 0;
  unsigned int nY = 0;

  for(nColor = 0; nColor < NUM_COLORS; nColor++)
    SetColor(nColor, Palette[nColor]);

  for(nX = 0; nX < NUM_TILES_WIDTH; nX++)
    for(nY = 0; nY < NUM_TILES_HEIGHT; nY++)
      aBackgroundTiles[nX][nY] = TileType_None;

  for(nX = 0; nX < NUM_TILES_WIDTH; nX++)
  {
    aBackgroundTiles[nX][0] = TileType_Border;
    aBackgroundTiles[nX][NUM_TILES_WIDTH - 1] = TileType_Border;
  }

  for(nY = 0; nY < NUM_TILES_HEIGHT; nY++)
  {
    aBackgroundTiles[0][nY] = TileType_Border;
    aBackgroundTiles[NUM_TILES_HEIGHT - 1][nY] = TileType_Border;
  }

  aBackgroundTiles[4][4] = TileType_Rock;
  aBackgroundTiles[15][4] = TileType_Rock;
  aBackgroundTiles[4][15] = TileType_Rock;
  aBackgroundTiles[15][15] = TileType_Rock;
  aBackgroundTiles[9][9] = TileType_Rock;
  aBackgroundTiles[9][10] = TileType_Rock;
  aBackgroundTiles[10][9] = TileType_Rock;
  aBackgroundTiles[10][10] = TileType_Rock;
  
  nSnakePieces = 0;
  eDirection = Direction_Right;

  for(nX = 0; nX < MAX_SNAKE_PIECES; nX++)
  {
    aSnake[nX].nX = 0;
    aSnake[nX].nY = 0;
  }

  for(nX = 0; nX < 5; nX++)
  {
    aSnake[nX].nX = nX + 5;
    aSnake[nX].nY = 12;

    aBackgroundTiles[aSnake[nX].nX][aSnake[nX].nY] = TileType_Snake;
    nSnakePieces++;
  }

  for(nX = 0; nX < NUM_TILES_WIDTH; nX++)
    for(nY = 0; nY < NUM_TILES_HEIGHT; nY++)
      if(aBackgroundTiles[nX][nY] != TileType_None)
        DrawTile(nX, nY);
}
////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////
//KeyboardProcess
////////////////////////////////////////////////////////////////////////
void KeyboardProcess()
{
  char nChar = GetChar();

  if(nChar == 'Q' || nChar == 'q' || nChar == -16) //Up
  {
    if(eDirection == Direction_Left || eDirection == Direction_Right)
      eDirection = Direction_Up;
  }
  else if(nChar == 'A' || nChar == 'a' || nChar == -15) //Down
  {
    if(eDirection == Direction_Left || eDirection == Direction_Right)
      eDirection = Direction_Down;
  }
  else if(nChar == 'O' || nChar == 'o' || nChar == -14) //Left
  {
    if(eDirection == Direction_Up || eDirection == Direction_Down)
      eDirection = Direction_Left;
  }
  else if(nChar == 'P' || nChar == 'p' || nChar == -13) //Right
  {
    if(eDirection == Direction_Up || eDirection == Direction_Down)
      eDirection = Direction_Right;
  }
}
////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////
//MoveSnake
////////////////////////////////////////////////////////////////////////
unsigned char MoveSnake(unsigned char bGrow)
{
  
  _tSnakePiece *pSnakePieceHead = &aSnake[nSnakePieces - 1];

  //new piece
  switch(eDirection)
  {
    case Direction_Right:
      aSnake[nSnakePieces].nX = pSnakePieceHead->nX + 1;
      aSnake[nSnakePieces].nY = pSnakePieceHead->nY;
      break;
    case Direction_Left:
      aSnake[nSnakePieces].nX = pSnakePieceHead->nX - 1;
      aSnake[nSnakePieces].nY = pSnakePieceHead->nY;
      break;
    case Direction_Up:
      aSnake[nSnakePieces].nX = pSnakePieceHead->nX;
      aSnake[nSnakePieces].nY = pSnakePieceHead->nY - 1;
      break;
    case Direction_Down:
      aSnake[nSnakePieces].nX = pSnakePieceHead->nX;
      aSnake[nSnakePieces].nY = pSnakePieceHead->nY + 1;
      break;
  }

  //has crashed
  if(aBackgroundTiles[aSnake[nSnakePieces].nX][aSnake[nSnakePieces].nY] != TileType_None)
    return 0;

  aBackgroundTiles[aSnake[nSnakePieces].nX][aSnake[nSnakePieces].nY] = TileType_Snake;
  DrawTile(aSnake[nSnakePieces].nX, aSnake[nSnakePieces].nY);

  nSnakePieces++;

  if(bGrow && nSnakePieces < MAX_SNAKE_PIECES)
    return 1;

  //delete tail of the snake
  aBackgroundTiles[aSnake[0].nX][aSnake[0].nY] = TileType_None;
  DrawTile(aSnake[0].nX, aSnake[0].nY);

  nSnakePieces--;
  memcpy(aSnake, &aSnake[1], sizeof(_tSnakePiece) * nSnakePieces);

  return 1;
}
////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////
//Game
////////////////////////////////////////////////////////////////////////
void Game()
{
  unsigned int nLastMoveTime = GetTime();
  unsigned int nGameMovements = 0;
  unsigned int nGameSpeed = 50;
  unsigned char bGrowSnake = 0;

  InitMode0();
  InitGame();

  while(1)
  {
    KeyboardProcess();

    if(GetTime() - nLastMoveTime < nGameSpeed)
      continue;

    nLastMoveTime = GetTime();
    nGameMovements++;

    if(nGameMovements % 20 == 0)
    {
      if(nGameSpeed > 15)
        nGameSpeed -= 2;

      bGrowSnake = 1;
    }

    if(!MoveSnake(bGrowSnake))
      break;

    bGrowSnake = 0;
  }

  SetMode(1);

  SetCursor(6, 7);
  printf("You have reached %d Movements", nGameMovements);

  SetCursor(8, 14);
  printf("Press Enter to play again");

  while(GetChar() != 13) {}
}
////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////
//ShowMenu
////////////////////////////////////////////////////////////////////////
void ShowMenu()
{
  SetMode(1);

  SetCursor(17, 5);
  printf("SNAKE");

  SetCursor(1, 8);
  printf("Use cursors or 'opqa' to move the snake");

  SetCursor(8, 16);
  printf("Press Enter to start game");

  SetCursor(3, 24);
  printf("Mochilote - www.cpcmania.com - 2012");

  while(GetChar() != 13) {}
}
////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////
//main
////////////////////////////////////////////////////////////////////////
void main()
{
  ShowMenu();

  while(1)
  {
    Game();
  }
}