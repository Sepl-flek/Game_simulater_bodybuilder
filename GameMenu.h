#pragma once
#include<SFML/Graphics.hpp>
#include <memory>
#include "AssetManager.h"
namespace game {
	class GameMenu
	{
	public:
		GameMenu(sf::RenderWindow& window, float menux, float menuy, int sizeFont, int step, std::vector<sf::String>& name);

		void draw();                                     // ��������� ����

		void MoveUp();									//����������� ���� �����

		void MoveDown();                                 // ����������� ���� ����


		void setColorTextMenu(sf::Color menColor, sf::Color ChoColor); // ���� ����
		void setNameMenu(sf::String const& name, int index);
		void AlignMenu(int posx);       // ������������ ��������� ����

		int getSelectedMenuNumber() const     //����������� ����� ���������� ��������
		{
			return mainMenuSelected;
		}



	private:
		float menu_X;                                     // ���������� ���� �� X
		float menu_Y;				                      // ���������� ���� �� Y
		int menu_Step;                                    // ���������� ����� ��������
		int max_menu;                                     // ������������ ���������� ������� ����
		int size_font;                                    // ������ ������
		int mainMenuSelected;                             // ����� �������� ������ ����
		sf::Font font;                                    // 
		std::vector<sf::Text> mainMenu;                   // �������� ����

		sf::Color menu_text_color = sf::Color::White;      // ���� ����
		sf::Color chose_text_color = sf::Color::Yellow;    // ���� ������ ����


		// ��������� ������ ����
		void setTextStyle(sf::Text& text, float x, float y, const sf::String& content);

		sf::RenderWindow& mywindow;                       // ������ �� ����������� ����


	};
}

