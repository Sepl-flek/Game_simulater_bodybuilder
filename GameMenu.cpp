#include "GameMenu.h"


game::GameMenu::GameMenu(sf::RenderWindow& window, float menux, float menuy, int sizeFont, int step, std::vector<sf::String>& name)
	:menu_X(menux), menu_Y(menuy), menu_Step(step), max_menu(static_cast<int>(name.size())), 
	size_font(sizeFont), mywindow(window),mainMenu(name.size())
{

	for (int i = 0, ypos = static_cast<int>(menu_Y); i < max_menu; i++, ypos += menu_Step)
		setTextStyle(mainMenu[i], menu_X, static_cast<float>(ypos),name[i]);
	mainMenuSelected = 0;
	mainMenu[mainMenuSelected].setFillColor(chose_text_color);
}
void game::GameMenu::setTextStyle(sf::Text& text, float x, float y, const sf::String& content)  // Изменено на sf::String
{
	text.setFont(AssetManager::GetFont("font/mainmenu.otf"));
	text.setPosition(x, y);
	text.setString(content);  // Здесь теперь тоже используется sf::String
	text.setCharacterSize(size_font);
	text.setFillColor(menu_text_color);
}



void game::GameMenu::AlignMenu(int posx)
{

	float nullx = 0;
	
	for (int i = 0; i < max_menu; i++) {

		switch (posx)
		{
		case 0:
			nullx = 0;
			break;
		case 1:
			nullx = mainMenu[i].getLocalBounds().width;
			break;
		case 2:
			nullx = menu_X - (mainMenu[i].getLocalBounds().width / 2);
			break;
		default:break;
		}

		mainMenu[i].setPosition(nullx, mainMenu[i].getPosition().y);
	}

}

void game::GameMenu::MoveUp()
{
	mainMenuSelected--;

	if (mainMenuSelected >= 0) {
		mainMenu[mainMenuSelected].setFillColor(chose_text_color);
		mainMenu[mainMenuSelected + 1].setFillColor(menu_text_color);
	}
	else
	{
		mainMenu[0].setFillColor(menu_text_color);
		mainMenuSelected = max_menu - 1;
		mainMenu[mainMenuSelected].setFillColor(chose_text_color);
	}
}

void game::GameMenu::MoveDown()
{
	mainMenuSelected++;

	if (mainMenuSelected < max_menu) {
		mainMenu[mainMenuSelected - 1].setFillColor(menu_text_color);
		mainMenu[mainMenuSelected].setFillColor(chose_text_color);
	}
	else
	{
		mainMenu[max_menu - 1].setFillColor(menu_text_color);
		mainMenuSelected = 0;
		mainMenu[mainMenuSelected].setFillColor(chose_text_color);
	}

}

void game::GameMenu::draw()
{
	for (int i = 0; i < max_menu; i++) mywindow.draw(mainMenu[i]);
}

void game::GameMenu::setColorTextMenu(sf::Color menColor, sf::Color ChoColor)
{
	menu_text_color = menColor;
	chose_text_color = ChoColor;


	for (int i = 0; i < max_menu; i++) {
		mainMenu[i].setFillColor(menu_text_color);
		
	}

	mainMenu[mainMenuSelected].setFillColor(chose_text_color);
}
	
void game::GameMenu::setNameMenu(sf::String const& name, int index)
{
	mainMenu[index].setString(name);
}
