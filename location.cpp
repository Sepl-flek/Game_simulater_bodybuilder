#include "location.h"


void GymPlay(Person& person, sf::RenderWindow& window)
{
	float width = sf::VideoMode::getDesktopMode().width;
	float height = sf::VideoMode::getDesktopMode().height;
	float scaleY = height / 512;
	float scaleX = width / 512;
	person.set_position(5*scaleX,270*scaleY);


	sf::RectangleShape background(sf::Vector2f(width, height));
	background.setTexture(&AssetManager::GetTexture("image/black.png"));
	window.clear();
	window.draw(background);
	window.display();
	sf::sleep(sf::seconds(0.5));
	background.setTexture(&AssetManager::GetTexture("image/gym.png"));

	sf::Text day;
	day.setFont(AssetManager::GetFont("font/mainmenu.otf")); // Устанавливаем шрифт
	day.setCharacterSize(50); // Размер шрифта
	day.setFillColor(sf::Color::White); // Цвет текста

	sf::Text text;
	text.setFont(AssetManager::GetFont("font/mainmenu.otf")); // Устанавливаем шрифт
	text.setCharacterSize(50); // Размер шрифта
	text.setFillColor(sf::Color::White); // Цвет текста

	text.setPosition(10 * scaleX, 10 * scaleY);
	day.setPosition(70 * scaleX, 10 * scaleY);
	person.set_scale(3, 3);

	sf::Vector2f position = person.get_position();

	const float parametr = 2;
	int traffic = 0;
	sf::Vector2f moveRec;

	Collision exit(0, 287 * scaleY, 35 * scaleX, 35 * scaleX);
	Collision treadmills(260 * scaleX, 110 * scaleY, 180 * scaleX, 45 * scaleY);
	Collision wall(0, 110 * scaleY, 512 * scaleX, 27 * scaleY);
	Collision squat(440 * scaleX, 136 * scaleY, 70 * scaleX, 71 * scaleY);
	Collision soda(480 * scaleX, 217 * scaleY, 24 * scaleX, 50 * scaleY);
	Collision bench(365 * scaleX, 408 * scaleY, 111 * scaleX, 14 * scaleY);
	Collision bench2(413 * scaleX, 356 * scaleY, 21 * scaleX, 47 * scaleY);
	Collision wheel(265 * scaleX, 390 * scaleY, 70 * scaleX,  10 * scaleY);
	Collision bars(30 * scaleX, 425 * scaleY, 82 * scaleX, 18 * scaleY);
	Collision bars2(60 * scaleX, 390 * scaleY, 35 * scaleX, 30 * scaleY);

	std::vector<Collision> collisions { wall,treadmills, squat,soda, bench, bench2, wheel,bars, bars2};

	Collision wheel2(270 * scaleX, 390 * scaleY, 67 * scaleX, 53 * scaleY);
	Collision near_wheel(240 * scaleX, 390 * scaleY, 100 * scaleX, 76 * scaleY);
	Collision bench_w(390 * scaleX, 422 * scaleY, 64 * scaleX, 19 * scaleY);
	Collision near_bench(365 * scaleX, 411 * scaleY, 145 * scaleX, 98 * scaleY);
	Collision squat2(440 * scaleX, 140 * scaleY, 49 * scaleX, 120 * scaleY);
	Collision near_squat(380 * scaleX, 220 * scaleY, 109 * scaleX, 52 * scaleY);

	std::vector<Collision> trainers{ wheel2,bench_w,squat2 };
	std::vector<Collision> near_trainers{ near_wheel,near_bench,near_squat };

	float time;
	sf::Clock clock, clockAnimPlay;
	sf::Music backgroundmusic;
	backgroundmusic.openFromFile("sound/gymplay_back.wav");

	backgroundmusic.setVolume(20);
	backgroundmusic.setLoop(true);
	backgroundmusic.play();

	while (window.isOpen())
	{
		time = clock.getElapsedTime().asMicroseconds();
		time /= 3000;
		clock.restart();
		sf::Event event;

		//collision
		bool flag = true;
		for (int i = 0; i < collisions.size(); ++i) {

			if (collisions[i].collision(person))
			{
				flag = false;
				break;
			}
		}
		if(flag) {
			position = person.get_position();}
		//-----------------------------------------

		while (window.pollEvent(event))
		{

			if (event.key.code == sf::Keyboard::Escape) { window.close(); }


			switch (event.type)
			{
			case sf::Event::KeyPressed: // кнопка нажата
				if ((event.key.code == sf::Keyboard::S)) {
					moveRec.y = parametr * time;
					traffic = 2;

				}
				if ((event.key.code == sf::Keyboard::W)) {
					moveRec.y = -parametr * time;
					traffic = 1;
				}
				if ((event.key.code == sf::Keyboard::A)) {
					moveRec.x = -parametr * time;
					traffic = 2;

				}
				if ((event.key.code == sf::Keyboard::D)) {
					moveRec.x = parametr * time;
					traffic = 1;
				}
				if( exit.collision(person) && event.key.code == sf::Keyboard::E)
				{
					background.setTexture(&AssetManager::GetTexture("image/black.png"));
					window.clear();
					window.draw(background);
					window.display();
					sf::sleep(sf::seconds(0.5));
					//background.setTexture(&AssetManager::GetTexture("image/background2.png"));
					person.set_position(475 * scaleX, 145 * scaleY);
					person.set_scale(2, 2);
					backgroundmusic.stop();
					return;
				}
				if (near_wheel.collision(person) && event.key.code == sf::Keyboard::E)
				{
					if (person.get_lvl_sleep() < 100 && person.get_hunger() < 100)
					{
						backgroundmusic.pause();
						TrainigWheel(person, window);
						person.update_hunger(10);
						person.update_sleep(10);
						backgroundmusic.play();
					}
				}
				if (near_squat.collision(person) && event.key.code == sf::Keyboard::E)
				{
					if (person.get_lvl_sleep() < 100 && person.get_hunger() < 100)
					{
						backgroundmusic.pause();
						TrainingSquad(person, window);
						
						backgroundmusic.play();
					}
				}
				

				break;

			case sf::Event::KeyReleased: //кнопка отпущена 
				if ((event.key.code == sf::Keyboard::S)) {
					moveRec.y = 0;
					traffic = 0;

				}
				if ((event.key.code == sf::Keyboard::W)) {
					moveRec.y = 0;
					traffic = 0;
				}
				if ((event.key.code == sf::Keyboard::A)) {
					moveRec.x = 0;
					traffic = 0;
				}
				if ((event.key.code == sf::Keyboard::D)) {
					moveRec.x = 0;
					traffic = 0;
				}


				break;

			default:
				break;

			}
		}
		if (clockAnimPlay.getElapsedTime() > sf::milliseconds(100)) {
			clockAnimPlay.restart();

			person.animation(traffic);

		}

		//if (near_door.collision(person))
		//{
		//	door.change_color(sf::Color::Yellow);
		//}
		//else
		//{
		//	door.change_color(sf::Color(0, 0, 0, 0));
		//}

		
		// коллизии 
		if (!flag)
		{
			person.set_position(position.x, position.y);
		}
		person.move(moveRec, width, height);
		for (int i = 0; i < trainers.size(); ++i)
		{
			if (near_trainers[i].collision(person))
			{
				trainers[i].change_color(sf::Color::Yellow);
			}
			else
			{
				trainers[i].change_color(sf::Color(0, 0, 0, 0));
			}
		}

		if (exit.collision(person)) { exit.change_color(sf::Color::Yellow); }
		else { exit.change_color(sf::Color(0, 0, 0, 0)); }

		text.setString("Money: " + std::to_string(person.get_money()));
		day.setString("Day: " + std::to_string(person.get_day()));

		text.setString("Money: " + std::to_string(person.get_money()));
		day.setString("Day: " + std::to_string(person.get_day()));


		window.clear();
		window.draw(background);
		window.draw(exit.get_rect());
		for (int i = 0; i < trainers.size(); ++i)
		{
			window.draw(trainers[i].get_rect());
		}
		person.draw(window);
		window.draw(text);
		window.draw(day);
		person.draw_interface(window, scaleX, scaleY);
		window.display();
	}
}

void TrainigWheel(Person& person, sf::RenderWindow& window)
{
	srand(time(NULL));
	float width = sf::VideoMode::getDesktopMode().width;
	float height = sf::VideoMode::getDesktopMode().height;
	float scaleY = height / 512;
	float scaleX = width / 512;
	window.setMouseCursorVisible(true);

	sf::RectangleShape background(sf::Vector2f(width, height));
	background.setTexture(&AssetManager::GetTexture("image/black.png"));
	window.clear();
	window.draw(background);
	window.display();
	sf::sleep(sf::seconds(0.5));
	background.setTexture(&AssetManager::GetTexture("image/play_wheel.png"));

	sf::Music backgroundmusic;

	if (!backgroundmusic.openFromFile("sound/funk1.wav")) {
		
		return;
	}

	backgroundmusic.setVolume(20);
	backgroundmusic.setLoop(true);
	backgroundmusic.play();

	// Параметры точек
	const int dotSize = 100;
	const int minDots = 5;
	const int maxDots = 7;
	std::vector<sf::CircleShape> dots;
	int poppedDots = 0;

	// Таймер для игры
	sf::Clock gameClock;
	const sf::Time gameDuration = sf::seconds(10);
	bool gameRunning = true;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();

			// Обработка кликов мыши
			if (event.type == sf::Event::MouseButtonPressed && gameRunning) {
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);
				for (auto it = dots.begin(); it != dots.end();) {
					if (isPointClicked(mousePos, *it)) {
						it = dots.erase(it);  // Удаление точки при клике
						poppedDots++;
					}
					else {
						++it;
					}
				}
			}

			// Закрытие окна по нажатию Enter после окончания игры
			if (!gameRunning && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
				backgroundmusic.stop();
				background.setTexture(&AssetManager::GetTexture("image/black.png"));
				window.clear();
				window.draw(background);
				window.display();
				sf::sleep(sf::seconds(0.5));
				window.setMouseCursorVisible(false);
				return;
			}
		}

		// Генерация новых точек, если игра продолжается
		if (gameRunning && gameClock.getElapsedTime() < gameDuration && dots.empty()) {
			int numDots = minDots + rand() % (maxDots - minDots + 1);
			for (int i = 0; i < numDots; ++i) {
				sf::CircleShape dot(dotSize / 2);
				dot.setFillColor(sf::Color::Red);

				// Установка случайной позиции на колесе
				float r = 124 + rand() % 100;
				float q = rand() % 360;
				float x = (r*cos(q) + 256) *scaleX;
				float y = (r*sin(q) + 225) *scaleY;
				
				dot.setPosition(x, y);

				dots.push_back(dot);
			}
		}

		// Проверка окончания времени игры
		if (gameClock.getElapsedTime() >= gameDuration) {
			gameRunning = false;
		}

		// Очистка экрана
		window.clear();

		// Отрисовка колеса и точек
		window.draw(background);
		for (auto& dot : dots) {
			window.draw(dot);
		}

		// Если игра окончена, выводим результат
		if (!gameRunning) {
			sf::Text resultText;
			resultText.setFont(AssetManager::GetFont("font/mainmenu.otf"));
			resultText.setString("Time's up! Popped dots: " + std::to_string(poppedDots) + "\nPress Enter to exit.");
			resultText.setCharacterSize(50);
			resultText.setFillColor(sf::Color::White);
			resultText.setPosition(200*scaleX, 200*scaleY);

			window.draw(resultText);
		}

		// Отображение окна
		window.display();
	}
}


bool isPointClicked(sf::Vector2i mousePos, sf::CircleShape& dot)
{
	return dot.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}

void TrainingSquad(Person& person, sf::RenderWindow& window)
{
	float width = sf::VideoMode::getDesktopMode().width;
	float height = sf::VideoMode::getDesktopMode().height;
	float scaleY = height / 512;
	float scaleX = width / 512;
	

	sf::RectangleShape background(sf::Vector2f(width, height));
	background.setTexture(&AssetManager::GetTexture("image/black.png"));
	window.clear();
	window.draw(background);
	window.display();
	sf::sleep(sf::seconds(0.5));
	background.setTexture(&AssetManager::GetTexture("image/play_squad1.png"));


	sf::Music backgroundmusic;

	if (!backgroundmusic.openFromFile("sound/funk1.wav")) {

		return;
	}

	backgroundmusic.setVolume(20);
	backgroundmusic.setLoop(true);
	backgroundmusic.play();


	
	sf::Text instructionText;
	instructionText.setFont(AssetManager::GetFont("font/mainmenu.otf"));
	instructionText.setCharacterSize(50);
	instructionText.setFillColor(sf::Color::White);
	instructionText.setPosition(175*scaleX, 200*scaleY);
	instructionText.setString("Press E to start the challenge");

	int clickCount = 0;            // Счетчик кликов
	int requiredClicks = 10;      // Количество необходимых кликов
	int Cliks = 10;
	bool challengeActive = false;  // Флаг для отслеживания активности испытания
	sf::Clock clock;               // Часы для отслеживания времени
	float elapsed = 0;             // Переменная для отслеживания времени
	bool startDelay = false;       // Флаг для отсрочки перед началом испытания
	int repeat = 0;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::E && !challengeActive)
			{
				clickCount = 0;
				Cliks += 2;
				requiredClicks =  Cliks; 
				challengeActive = true;
				startDelay = true;   
				clock.restart();
			}
			
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				if (challengeActive && !startDelay) {
					clickCount++;      
					requiredClicks--;
					if (requiredClicks <= 0)
					{
						requiredClicks = 0;
					}
				}
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter && !challengeActive)
			{
				backgroundmusic.stop();
				person.update_hunger(2 * repeat);
				person.update_sleep(4 * repeat);
				return;
			}
		}

		// Обновление таймера и проверка состояний
		if (startDelay) {
			elapsed = clock.getElapsedTime().asSeconds();
			if (elapsed >= 0.5)
			{
				background.setTexture(&AssetManager::GetTexture("image/play_squad2.png"));
			}
			if (elapsed >= 1) {  
				background.setTexture(&AssetManager::GetTexture("image/play_squad3.png"));
				startDelay = false;
				clock.restart();
			}
		}
		else if (challengeActive) {
			elapsed = clock.getElapsedTime().asSeconds();
			
			if (elapsed > 2) {  // Проверка, прошло ли 2 секунды
				background.setTexture(&AssetManager::GetTexture("image/play_squad1.png"));
				if (clickCount >= Cliks) {
					repeat++;
					instructionText.setString("Press E to make another reapet .\n press Enter to finish");
				}
				else {
					
					std::stringstream ss;
					ss << "You made " << repeat << " repeats. I'm looser";
					
					instructionText.setString(ss.str());
					window.clear();
					window.draw(background);
					window.draw(instructionText);
					window.display();
					sf::sleep(sf::seconds(2));

					
					backgroundmusic.stop();
					person.update_hunger(2 * repeat);
					person.update_sleep(4 * repeat);
					return;

				}
				challengeActive = false; 
			}
			else {
				
				std::stringstream ss;
				ss << "Clicks left: " << requiredClicks;
				instructionText.setString(ss.str());
			}
		}

		
		window.clear();
		window.draw(background);
		window.draw(instructionText);

		window.display();
	}
}

void workPlay(Person& person, sf::RenderWindow& window)
{
	float width = sf::VideoMode::getDesktopMode().width;
	float height = sf::VideoMode::getDesktopMode().height;
	float scaleY = height / 512;
	float scaleX = width / 512;
	person.set_position(7 * scaleX, 230 * scaleY);


	sf::RectangleShape background(sf::Vector2f(width, height));
	background.setTexture(&AssetManager::GetTexture("image/black.png"));
	window.clear();
	window.draw(background);
	window.display();
	sf::sleep(sf::seconds(0.5));
	background.setTexture(&AssetManager::GetTexture("image/work_location.png"));

	sf::Text day;
	day.setFont(AssetManager::GetFont("font/mainmenu.otf")); // Устанавливаем шрифт
	day.setCharacterSize(50); // Размер шрифта
	day.setFillColor(sf::Color::White); // Цвет текста

	sf::Text text;
	text.setFont(AssetManager::GetFont("font/mainmenu.otf")); // Устанавливаем шрифт
	text.setCharacterSize(50); // Размер шрифта
	text.setFillColor(sf::Color::White); // Цвет текста

	text.setPosition(10 * scaleX, 10 * scaleY);
	day.setPosition(70 * scaleX, 10 * scaleY);
	person.set_scale(3, 3);


	sf::Vector2f position = person.get_position();

	const float parametr = 2;
	int traffic = 0;
	sf::Vector2f moveRec;


	Collision exit(2 * scaleX, 225 * scaleY, 75 * scaleX, 75 * scaleY);
	Collision computer1(4 * scaleX, 140 * scaleY, 96 * scaleX, 8 * scaleY);
	Collision computer2(188 * scaleX, 140 * scaleY, 96 * scaleX, 8 * scaleY);
	Collision computer3(338 * scaleX, 140 * scaleY, 96 * scaleX, 8 * scaleY);
	Collision computer4(4 * scaleX, 2 * scaleY, 96 * scaleX, 8 * scaleY);
	Collision computer5(188 * scaleX, 2 * scaleY, 96 * scaleX, 8 * scaleY);
	Collision computer6(338 * scaleX, 2 * scaleY, 96 * scaleX, 8 * scaleY);
	Collision computer7(4 * scaleX, 319 * scaleY, 96 * scaleX, 8 * scaleY);
	Collision computer8(188 * scaleX, 319 * scaleY, 96 * scaleX, 8 * scaleY);
	Collision computer9(338 * scaleX, 319 * scaleY, 96 * scaleX, 8 * scaleY);
	Collision computer10(4 * scaleX, 443 * scaleY, 96 * scaleX, 8 * scaleY);
	Collision computer11(188 * scaleX, 443 * scaleY, 96 * scaleX, 8 * scaleY);
	Collision computer12(338 * scaleX, 443 * scaleY, 96 * scaleX, 8 * scaleY);

	Collision near_my_computer(338 * scaleX, 154 * scaleY, 97 * scaleX, 51 * scaleY);


	std::vector<Collision> collisions{computer1,computer2,computer3,computer4,computer5,computer6,computer7,computer8,computer9
		,computer10,computer11,computer12 };


	float time;
	sf::Clock clock, clockAnimPlay;
	sf::Music backgroundmusic;

	while (window.isOpen())
	{
		time = clock.getElapsedTime().asMicroseconds();
		time /= 3000;
		clock.restart();
		sf::Event event;

		//collision
		bool flag = true;
		for (int i = 0; i < collisions.size(); ++i) {

			if (collisions[i].collision(person))
			{
				flag = false;
				break;
			}
		}
		if (flag) {
			position = person.get_position();
		}
		//-----------------------------------------

		while (window.pollEvent(event))
		{

			if (event.key.code == sf::Keyboard::Escape) { window.close(); }


			switch (event.type)
			{
			case sf::Event::KeyPressed: // кнопка нажата
				if ((event.key.code == sf::Keyboard::S)) {
					moveRec.y = parametr * time;
					traffic = 2;

				}
				if ((event.key.code == sf::Keyboard::W)) {
					moveRec.y = -parametr * time;
					traffic = 1;
				}
				if ((event.key.code == sf::Keyboard::A)) {
					moveRec.x = -parametr * time;
					traffic = 2;

				}
				if ((event.key.code == sf::Keyboard::D)) {
					moveRec.x = parametr * time;
					traffic = 1;
				}
				if (exit.collision(person) && event.key.code == sf::Keyboard::E)
				{
					background.setTexture(&AssetManager::GetTexture("image/black.png"));
					window.clear();
					window.draw(background);
					window.display();
					sf::sleep(sf::seconds(0.5));
					//background.setTexture(&AssetManager::GetTexture("image/background2.png"));
					person.set_position(475 * scaleX, 145 * scaleY);
					person.set_scale(2, 2);

					return;
				}
				if (near_my_computer.collision(person) && event.key.code == sf::Keyboard::E)
				{
					workgame(window);
				}
				break;

			case sf::Event::KeyReleased: //кнопка отпущена 
				if ((event.key.code == sf::Keyboard::S)) {
					moveRec.y = 0;
					traffic = 0;

				}
				if ((event.key.code == sf::Keyboard::W)) {
					moveRec.y = 0;
					traffic = 0;
				}
				if ((event.key.code == sf::Keyboard::A)) {
					moveRec.x = 0;
					traffic = 0;
				}
				if ((event.key.code == sf::Keyboard::D)) {
					moveRec.x = 0;
					traffic = 0;
				}


				break;

			default:
				break;

			}
		}
		if (clockAnimPlay.getElapsedTime() > sf::milliseconds(100)) {
			clockAnimPlay.restart();

			person.animation(traffic);

		}
		if (!flag)
		{
			person.set_position(position.x, position.y);
		}
		person.move(moveRec, width, height);
		if (exit.collision(person)) { exit.change_color(sf::Color::Yellow); }
		else { exit.change_color(sf::Color(0, 0, 0, 0)); }

		if (near_my_computer.collision(person)) { near_my_computer.change_color(sf::Color::Yellow); }
		else { near_my_computer.change_color(sf::Color(0, 0, 0, 0)); }

		text.setString("Money: " + std::to_string(person.get_money()));
		day.setString("Day: " + std::to_string(person.get_day()));

		text.setString("Money: " + std::to_string(person.get_money()));
		day.setString("Day: " + std::to_string(person.get_day()));
		

		window.clear();
		window.draw(background);
		window.draw(exit.get_rect());
		window.draw(near_my_computer.get_rect());
		person.draw(window);
		window.draw(text);
		window.draw(day);
		person.draw_interface(window, scaleX, scaleY);
		window.display();
	}


}
