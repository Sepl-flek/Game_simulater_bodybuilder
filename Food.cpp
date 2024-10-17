#include "Food.h"

Food::Food(float x, float y, sf::Vector2f position, std::string texture, int coast, float scaleX, float scaleY, float width,float height): coast(coast)
{
	food.setTexture(AssetManager::GetTexture(texture));
	food.setTextureRect(sf::IntRect(x, y, width, height));
	food.setPosition(position);
	border.setOutlineThickness(5);
	border.setPosition(position);
	border.setFillColor(sf::Color(0, 0, 0, 0));
	border.setSize(sf::Vector2f(width, height));
	border.setOutlineColor(sf::Color(0, 0, 0, 0));
	border.setScale(scaleX, scaleY);
	food.setScale(scaleX, scaleY);
}

void Food::draw(sf::RenderWindow& window)
{
	window.draw(food);
	window.draw(border);
}

void Food::change_color(sf::Color color)
{
	border.setOutlineColor(color);
}
