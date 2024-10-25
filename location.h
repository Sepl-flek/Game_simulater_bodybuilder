#pragma once
#include "Person.h"
#include "SFML/Graphics.hpp"
#include "AssetManager.h"
#include "Collision.h"
#include "time.h"
#include <math.h>

void GymPlay(Person& person, sf::RenderWindow& window);
void TrainigWheel(Person& person, sf::RenderWindow& window);
bool isPointClicked(sf::Vector2i mousePos, sf::CircleShape& dot);