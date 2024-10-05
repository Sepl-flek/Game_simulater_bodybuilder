#pragma once
#include<SFML/Graphics.hpp>
#include <memory>
#include "AssetManager.h"
class Person
{
public:
	Person(float scale);
	void PlayerMove(sf::Sprite& person, sf::Vector2f& moveRec);
	void move(float& time); 
	void set_position(float x, float y);
	void set_scale(float x, float y);
	void draw(sf::RenderWindow& window); 
	void animation();

private:
	sf::Sprite person;

	std::vector<int> xsp{0,41,82,125,175,235,280,325,380,454,516,567,610};
	int ysp = 0,height = 76;
	std::vector<int> width{ 40 ,41,38,45,59,45,45,50,66,61,53,49,60};
	
};