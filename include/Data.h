#ifndef DATA_H
#define DATA_H

#include "2048Lib.h"

void database(const char* fileName);
void playerName(sf::RenderWindow& window, const sf::Font& font, char* username);
int** loadSave(Node *&currentNode, int& size, const char* username, int& character);
void saveGame(Node* head, const int& size, const char* username, const int& character);
int max(int a, int b);
void addPlayerToList(const char* username, const char* playersFile);
int readLeaderboard(const char* filePath, char**& players, int*& scores);
void writeLeaderboard(const char* filePath, char** players, const int* scores, int curBoardSize);
void updateOrAddPlayer(char**& players, int*& scores, int& curBoardSize, const char* username, int point);
void sortLeaderboard(char** players, int* scores, int curBoardSize);
void leaderboard(sf::RenderWindow& window, const sf::Font& font, const int& size, const char* username, const int& point);

#endif