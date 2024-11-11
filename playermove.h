#pragma once

#include <SFML/Graphics.hpp>
#include "Meteor.h";
#include "Full.h";
#include <sstream>
#include <string>
#include <SFML/Audio.hpp>

struct FrameAnime
{
	int Frame = 0, Frame1 = 0;
	int Step = 100, Step1 = 100;


};

void PlayerMove(sf::Sprite& ship, sf::Vector2f& moveRec, float max_x, float max_y);

void playerAnim(sf::Sprite& ship, FrameAnime& FramePlanim, int traffic);

void Correct(Full& canister, int i, Meteor* meteor, int nmeteor);

void CorrectFull(Full& canister, Meteor* meteor, int nmeteor);

std::string IntToStr(int number);