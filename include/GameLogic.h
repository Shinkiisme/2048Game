#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "2048Lib.h"

int** makeGrid(const int& size);
void randNumber(int** bang, const int& size);
void mergeRow(int** bang, const int& size, const char& button);
void mergeCol(int** bang, const int& size, const char& button);
bool winCheck(int** bang, const int& size, const bool& afterWin);
bool loseCheck(int** bang, const int& size);
int score(int** bang, const int& size);

#endif
