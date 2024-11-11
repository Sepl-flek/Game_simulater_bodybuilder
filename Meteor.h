#pragma once

#include <SFML/Graphics.hpp>
class Meteor
{
public:
	Meteor();
	~Meteor();

	void move(float& time); // �������� �������
	void draw(sf::RenderWindow& window); // ��������� �������
	void animation(); // �������� �������
	bool collision(sf::FloatRect object); // ������������ �������
	virtual void restart(); // ��������� ����� ���������
	sf::FloatRect get_meteor_bounds(); // ��������� ���������� ���������
	sf::Vector2f getPosBonus()
	{
		return PosBonus;
	}
	bool new_born;

protected:
	sf::Sprite space_object;  //������ ��������
	sf::Texture texture_object; // �������� ��������
	sf::Vector2f PosBonus;
	int width = sf::VideoMode::getDesktopMode().width;
	int height = sf::VideoMode::getDesktopMode().height;

private:
	

	int max_x;
	int  max_y;
	int xsp[5]{ 3,73,135,198,262 };       // ���������� �������� �� x
	int ysp[6]{ 3,68,132,200,265,325 };   // ���������� �������� �� y

	int ix, iy = 0; // �������� �� x y
	int st = 0; // ��� �������� 
};
