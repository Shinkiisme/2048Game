#ifndef NEWGAME_H
#define NEWGAME_H

#include "2048Lib.h"

void newGame(sf::RenderWindow& window, const sf::Font& font, int**& bang, int& size, Node*& currentNode, char*& username, int& character, bool& isNewGame);

#endif
