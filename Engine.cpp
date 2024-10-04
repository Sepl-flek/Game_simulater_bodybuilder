#include "Engine.h"





void Engine::setTextStyle(sf::Text& text, float x, float y, float size, const sf::Color& color,const std::string& content)
{
	text.setPosition(x, y);
	text.setString(content);
	text.setCharacterSize(size);
	text.setFillColor(color);
}

void Engine::GameMenu()
{
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(),  L"BodyBuilder", sf::Style::Fullscreen);
	window.requestFocus();
	window.setActive(true);
	window.setMouseCursorVisible(false);


	std::vector<sf::String> name_menu = { L"Play","Exit" };
	game::GameMenu mymenu(window, 1250, 600, 100, 250, name_menu);
	

	mymenu.setColorTextMenu(sf::Color(235, 78, 78), sf::Color::Yellow);
	mymenu.AlignMenu(2);

	//Задний фон
	sf::RectangleShape background(sf::Vector2f(width, heght));

	background.setTexture(&AssetManager::GetTexture("image/menu.jpg"));

	sf::Text Titul;
	Titul.setFont(AssetManager::GetFont("font/mainmenu.otf"));

    
    setTextStyle(Titul, 770, 50, 120, sf::Color(235, 78, 78), "Bodybuilder Club");// параметры главного текста

    
    
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::KeyReleased:
                if (event.key.code == sf::Keyboard::Up) { mymenu.MoveUp(); break; }
                if (event.key.code == sf::Keyboard::Down) { mymenu.MoveDown(); break; }
                if (event.key.code == sf::Keyboard::Return)
                {
                    switch (mymenu.getSelectedMenuNumber())
                    {
                    case 0:  window.close(); return; break;
              
					case 2: exit(0); break;
                    default:break;
                    }
                } break;
            default:break;
            }
        }
        

        window.clear();
        window.draw(background);
        window.draw(Titul);
        mymenu.draw();
        window.display();
    }

}

void Engine::input()
{
	sf::Event event_play;
	while (window->pollEvent(event_play))
	{
		if (event_play.key.code == sf::Keyboard::Escape) { window->close(); }
	}
}

void Engine::update(sf::Time const& deltaTime)
{
}

void Engine::draw()
{
	window->clear();
	window->draw(background);
	
	window->display();
}

Engine::Engine()
{
	background.setTexture(&AssetManager::GetTexture("image/background.jpg"));

}

void Engine::run()
{
	GameMenu();
	sf::Clock clock;
	
	
	while (window->isOpen())
	{
		sf::Time dt = clock.restart();

		input();

		update(dt);

		draw();
	}
}



