#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "2048Lib.h"

sf::Color cellColor(const int& number);
sf::Color numberColor(const int& number);
void printWelcomeScreen(sf::RenderWindow& window, const sf::Font& font);
int Menu(sf::RenderWindow& window, const sf::Font& font);
void nameInput(sf::RenderWindow& window, const sf::Font& font, char* username);
int characterChoose(sf::RenderWindow& window, const sf::Font& font);
int Return(sf::RenderWindow& window, const sf::Font& font);
int customizeSize(sf::RenderWindow& window, const sf::Font& font);
int sizeInput(sf::RenderWindow& window, const sf::Font& font);
void playWindow(sf::RenderWindow& window, const int& size);
void printGrid(sf::RenderWindow& window, const sf::Font& font, int** bang, const int& size, const int& character);
int winScreen(sf::RenderWindow& window, const sf::Font& font);
int loseScreen(sf::RenderWindow& window, const sf::Font& font, int** bang, const int& size, const int& character);
void displayLeaderboard(sf::RenderWindow& window, const sf::Font& font, const int& size, char** players, const int* scores, int curBoardSize, int maxDisplay);

#endif
