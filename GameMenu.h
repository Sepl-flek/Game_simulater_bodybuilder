#pragma once
#include<SFML/Graphics.hpp>
#include <memory>
#include "AssetManager.h"
namespace game {
	class GameMenu
	{
	public:
		GameMenu(sf::RenderWindow& window, float menux, float menuy, int sizeFont, int step, std::vector<sf::String>& name);

		void draw();                                     // отрисовка меню

		void MoveUp();									//перемещение меню вверх

		void MoveDown();                                 // перемещение меню вниз


		void setColorTextMenu(sf::Color menColor, sf::Color ChoColor); // цвет меню
		void setNameMenu(sf::String const& name, int index);
		void AlignMenu(int posx);       // выравнивание положения меню

		int getSelectedMenuNumber() const     //возвращение нмоер выбранного элемента
		{
			return mainMenuSelected;
		}



	private:
		float menu_X;                                     // координаты меню по X
		float menu_Y;				                      // Коорденяты меню по Y
		int menu_Step;                                    // Расстояние между пунктами
		int max_menu;                                     // Максимальное количесвто пунктов меню
		int size_font;                                    // размер шрифта
		int mainMenuSelected;                             // Номер текущего пункта меню
		sf::Font font;                                    // 
		std::vector<sf::Text> mainMenu;                   // Названия меню

		sf::Color menu_text_color = sf::Color::White;      // цвет меню
		sf::Color chose_text_color = sf::Color::Yellow;    // цвет выбора меню


		// настройки текста меню
		void setTextStyle(sf::Text& text, float x, float y, const sf::String& content);

		sf::RenderWindow& mywindow;                       // ссылка на графическое окно


	};
}

