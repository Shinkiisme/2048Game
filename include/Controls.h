#ifndef CONTROLS_H
#define CONTROLS_H

#include <SFML/Graphics.hpp>
#include "Node.h"
#include "FreeMemory.h"

sf::Keyboard::Key control(sf::RenderWindow& window, int** bang, const int& size, Node*& currentNode, char*& username);

#endif
