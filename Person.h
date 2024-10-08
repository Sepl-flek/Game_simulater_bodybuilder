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
	sf::Vector2f get_position();
	sf::FloatRect get_global_bounds() const;

private:
	int money = 1000;
	int lvl_sleep = 0;
	int hunger = 0;

	sf::Sprite person;
	int step_animation = 0;
	std::vector<int> xsp{0,41,82,125,175,235,280,325,380,454,516,567,610};
	int ysp = 0,heightsp = 76;
	int yspl = 85;
	std::vector <int>xspl{ 620,572,506,458,417,364,295,228,174,131,72 };
	std::vector<int> widthsp{ 40 ,41,38,45,59,45,45,50,66,61,53,49,60};
	
};