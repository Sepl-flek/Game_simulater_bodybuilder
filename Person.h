#pragma once
#include<SFML/Graphics.hpp>
#include <memory>
#include "AssetManager.h"
#include <string>



class Person
{
public:
	Person(float scale);


	void move(sf::Vector2f move_rec,float wedth,float height);
	void set_position(float x, float y);
	void set_scale(float x, float y);
	void set_day(int _day);
	void draw(sf::RenderWindow& window); 
	void draw_interface(sf::RenderWindow& window,float scaleX,float scaleY);
	void animation(int trafic);
	sf::Vector2f get_position();
	sf::FloatRect get_global_bounds() const;

	void update_hunger(int procant); // увеличить голод
	void update_sleep(int procant); // увеличить желание спать
	void update_money(int coast);
	void update_day();
	//гетеры
	int get_hunger();
	int get_money();
	int get_lvl_sleep();
	int get_day();
	int get_leg_power();
	int get_chest_power();
	int get_back_power();


	void set_back_power(int tmp);
	void set_chest_power(int tmp);
	void set_leg_power(int tmp);


private:
	// механики
	int money = 1000;
	int lvl_sleep = 0; // 100 - max
	int hunger = 0; // 100 - max
	int day = 1;
	int leg_power = 0;
	int chest_power = 0;
	int back_power = 0;
	
	sf::Sprite meat;
	sf::Sprite energy;
	sf::RectangleShape rect_hunger = sf::RectangleShape(sf::Vector2f(200,50));
	sf::RectangleShape rect_lvl_sleep = sf::RectangleShape(sf::Vector2f(200, 50));

	sf::RectangleShape full_rect_hunger = sf::RectangleShape(sf::Vector2f(200, 50));
	sf::RectangleShape full_rect_lvl_sleep = sf::RectangleShape(sf::Vector2f(200, 50));

	sf::Sprite leg;
	sf::Sprite chest;
	sf::Sprite back;

	sf::RectangleShape rect_chest = sf::RectangleShape(sf::Vector2f(200, 50));
	sf::RectangleShape rect_leg = sf::RectangleShape(sf::Vector2f(200, 50));

	sf::RectangleShape rect_back = sf::RectangleShape(sf::Vector2f(200, 50));
	sf::RectangleShape full_rect_chest = sf::RectangleShape(sf::Vector2f(200, 50));

	sf::RectangleShape full_rect_leg = sf::RectangleShape(sf::Vector2f(200, 50));
	sf::RectangleShape full_rect_back = sf::RectangleShape(sf::Vector2f(200, 50));

	





	// спрайты
	sf::Sprite person;
	int step_animation = 0;
	std::vector<int> xsp{0,41,82,125,175,235,280,325,380,454,516,566,610};
	int ysp = 0,heightsp = 76;
	int yspl = 85;
	std::vector <int>xspl{ 620,572,506,458,417,364,295,228,174,131,72 };
	std::vector<int> widthsp{ 40 ,41,38,45,59,45,45,50,66,61,53,47,60};
	
};