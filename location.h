#pragma once
#include "Person.h"
#include "SFML/Graphics.hpp"
#include "AssetManager.h"
#include "Collision.h"
#include "time.h"
#include <math.h>
#include <sstream> 


void GymPlay(Person& person, sf::RenderWindow& window);
void TrainigWheel(Person& person, sf::RenderWindow& window);
bool isPointClicked(sf::Vector2i mousePos, sf::CircleShape& dot);
void TrainingSquad(Person& person, sf::RenderWindow& window);
void workPlay(Person& person, sf::RenderWindow& window);