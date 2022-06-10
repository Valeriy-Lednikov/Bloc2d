#pragma once
#include "Header.h"


struct GameSprite {
	int spriteID = -1;
	std::string name = "";
	sf::Sprite sprite;
	sf::Texture texture;
};
struct Gameobject {
	int spriteID = -1;
	float x = 0;
	float y = 0;
	float rotation = 0;
	float sizeX = BlocSize;
	float sizeY = BlocSize;



};



