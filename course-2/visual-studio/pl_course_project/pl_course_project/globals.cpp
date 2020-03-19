#include "globals.h"

char board[8][8] = { 0 };

bool gameMode;

USHORT
  wndWidth = 425,
  wndHeight = 568,

  fieldWidth,
  fieldHeight,

  xInit = 5,
  yInit = 5,
  boardSize = 400,

  blackScore = 0,
  whiteScore = 0,
  whoMoves = 0;

WCHAR
  firstString_buff[32] = { 0 },
  secondString_buff[32] = { 0 };
