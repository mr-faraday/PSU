#pragma once

#include <Windows.h>

#define M_PI 3.14159265358979323846
#define BLACK_s 1
#define WHITE_s 2
#define BLACK_can_move 3
#define WHITE_can_move 4

// Игровая доска
// 0 - пустая клетка
// 1 - чёрная сторона фишки
// 2 - белая сторона фишки
// 3 - возможность хода для чёрных
// 4 - возможность хода для белых
extern char board[8][8];

extern bool gameMode;  // Режим игры: 0 - Игра с ИИ, 1 - игра на 2 игрока

extern USHORT
  wndWidth,       // Ширина окна
  wndHeight,      // Высота окна

  fieldWidth,     // Ширина рабочей зоны
  fieldHeight,    // Высота рабочей зоны

  xInit,          // Место размещения доски
  yInit,
  boardSize,      // Размер доски

  blackScore,     // Кол-во фишек у чёрных
  whiteScore,     // Кол-во фишек у белых
  whoMoves;       // Кто ходит

extern WCHAR
  firstString_buff[32],   // Буфер пераой строки
  secondString_buff[32];  // Буфер второй строки
