#ifndef UNDODOREDO_H
#define UNDODOREDO_H

#include "2048Lib.h"

void newState(int** bang, const int& size, Node*& currentNode);
void undo(sf::RenderWindow& window, const sf::Font& font, int** bang, const int& size, const int& character, Node*& currentNode);
void redo(sf::RenderWindow &window, const sf::Font& font, int** bang, const int& size, const int& character, Node*& currentNode);

#endif
