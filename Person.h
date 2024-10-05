#pragma once
#include<SFML/Graphics.hpp>
#include <memory>
#include "AssetManager.h"
class Person
{
public:
	Person(float scale);

	void move(sf::Vector2f move_rec,float wedth,float height);
	void set_position(float x, float y);
	void set_scale(float x, float y);
	void draw(sf::RenderWindow& window); 
	void animation(int trafic);

private:
	sf::Sprite person;
	
	std::vector<int> xsp{0,41,82,125,175,235,280,325,380,454,516,567,610};
	int ysp = 0,heightsp = 76;
	std::vector<int> widthsp{ 40 ,41,38,45,59,45,45,50,66,61,53,49,60};
	
};