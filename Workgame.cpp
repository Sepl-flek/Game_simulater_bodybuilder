#include "Workgame.h"

void workgame(sf::RenderWindow& window)
{

        srand(time(NULL));
        

        // �������������� ������
        sf::Texture textureInfoPanel;
        textureInfoPanel.loadFromFile("pictures/Panel.png");
        sf::RectangleShape gameInfoPanel(sf::Vector2f(1280, 113));
        gameInfoPanel.setTexture(&textureInfoPanel);
        gameInfoPanel.setPosition(sf::Vector2f(0, 0));

        // ���������
        sf::Texture textureSpace;
        textureSpace.loadFromFile("pictures/newkos1.jpg");

        sf::RectangleShape gameSpace(sf::Vector2f(1280, 720));
        gameSpace.setTexture(&textureSpace);

        sf::RectangleShape gameSpace2(sf::Vector2f(1280, 720));
        gameSpace2.setTexture(&textureSpace);
        gameSpace2.setPosition(sf::Vector2f(1280, 0));

        bool game_over = false;
        sf::Vector2f pos;
        sf::Clock clock, clockAnimPlay, clockMeteor;
        float time, timeShip, timeBackground, timeMete;
        //.........................................

        // ����������� �������
        sf::Vector2f moveRec; // ������������ ������
        int traffic = 0;
        sf::Texture textureShip;

        FrameAnime FramePlanim;
        FramePlanim.Frame = 700;
        textureShip.loadFromFile("pictures/playeranim1.png");

        sf::Sprite ship;
        ship.setTexture(textureShip);
        ship.setTextureRect(sf::IntRect(0, FramePlanim.Frame, 90, 90));
        ship.scale(0.7, 0.7);
        ship.setPosition(sf::Vector2f(80, 380));
        //.........................................


        // ����� ������������ �������

        FrameAnime distruction_anim;
        distruction_anim.Frame = 5;
        distruction_anim.Frame1 = 15;
        sf::Texture text_deest;
        text_deest.loadFromFile("pictures/bum.png");
        sf::Sprite destruction;
        destruction.setTexture(text_deest);
        destruction.setTextureRect(sf::IntRect(5, 15, 95, 80));
        destruction.scale(0.7, 0.7);


        //���������
        Meteor meteors[15];
        int nmeteor = 15;



        while (window.isOpen())
        {
            sf::Event event;
            // time
            time = clock.getElapsedTime().asMicroseconds();
            time /= 6000;
            timeShip = time * 3;
            timeBackground = time;
            timeMete = time * 2;
            //.........................................

            clock.restart();
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
                // ���������� ��������
                switch (event.type)
                {
                case sf::Event::KeyPressed:
                    if ((event.key.code == sf::Keyboard::S)) {
                        moveRec.y = 0.3 * timeShip;
                        traffic = 2;
                    }
                    if ((event.key.code == sf::Keyboard::W)) {
                        moveRec.y = -0.3 * timeShip;
                        traffic = 1;
                    }
                    if ((event.key.code == sf::Keyboard::A)) {
                        moveRec.x = -0.3 * timeShip;

                    }
                    if ((event.key.code == sf::Keyboard::D)) {
                        moveRec.x = 0.3 * timeShip;
                    }
                    break;

                case sf::Event::KeyReleased:
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
                    }
                    if ((event.key.code == sf::Keyboard::D)) {
                        moveRec.x = 0;
                    }
                    break;

                default:
                    break;
                }

            }
            if (game_over) {
                if (clockMeteor.getElapsedTime() > sf::milliseconds(80)) {

                    clockMeteor.restart();
                    distruction_anim.Frame += distruction_anim.Step;
                    if (distruction_anim.Frame > 405) {
                        distruction_anim.Frame1 += distruction_anim.Step1;
                        distruction_anim.Frame = 5;
                    }
                    if (distruction_anim.Frame1 > 415) {
                        game_over = false;
                        ship.setPosition(sf::Vector2f(80, 380));
                        for (int i = 0; i < nmeteor; ++i) {
                            meteors[i].restart();

                        }
                        distruction_anim.Frame = 5;
                        distruction_anim.Frame1 = 15;
                    }
                    else {
                        destruction.setTextureRect(sf::IntRect(distruction_anim.Frame, distruction_anim.Frame1, 95, 80));
                    }
                }
            }
            else {



                if (clockAnimPlay.getElapsedTime() > sf::milliseconds(100)) {
                    clockAnimPlay.restart();

                    playerAnim(ship, FramePlanim, traffic);

                }

                if (clockMeteor.getElapsedTime() > sf::milliseconds(80)) {
                    clockMeteor.restart();
                    for (int i = 0; i < nmeteor; ++i) {
                        meteors[i].animation();

                    }

                }



                // ���������� �������
                gameSpace.move(-0.2 * timeBackground, 0);
                pos = gameSpace.getPosition();
                if (pos.x < -1280) {
                    gameSpace.setPosition(1280, pos.y);
                }

                gameSpace2.move(-0.2 * timeBackground, 0);
                pos = gameSpace2.getPosition();
                if (pos.x < -1280) {
                    gameSpace2.setPosition(1280, pos.y);
                }
                //...........................................

                //�������� �������
                PlayerMove(ship, moveRec);

                for (int i = 0; i < nmeteor; ++i) {
                    meteors[i].move(timeMete);

                    if (meteors[i].collision(ship.getGlobalBounds())) {
                        game_over = true;
                        destruction.setPosition(ship.getPosition().x, ship.getPosition().y);
                        break;
                    }

                }
            }

            window.clear();
            window.draw(gameSpace);
            window.draw(gameSpace2);
            window.draw(gameInfoPanel);

            if (game_over) {
                window.draw(destruction);
            }
            else {
                window.draw(ship);
            }
            for (int i = 0; i < nmeteor; ++i) {
                meteors[i].draw(window);
            }
            window.display();


        }

       
}
