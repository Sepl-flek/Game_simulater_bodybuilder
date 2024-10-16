#include "Food.h"

Food::Food(float x, float y, sf::Vector2f position, std::string texture,float width,float height)
{
	food.setTexture(AssetManager::GetTexture(texture));
	food.setTextureRect(sf::IntRect(x, y, width, height));
	food.setPosition(position);
}

void Food::draw(sf::RenderWindow& window)
{
	window.draw(food);
}
