#pragma once

#include <SFML/Graphics.hpp>

struct FrameAnime
{
	int Frame = 0, Frame1 = 0;
	int Step = 100, Step1 = 100;


};

void PlayerMove(sf::Sprite& ship, sf::Vector2f& moveRec);

void playerAnim(sf::Sprite& ship, FrameAnime& FramePlanim, int traffic);
