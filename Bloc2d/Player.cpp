#pragma once
#include "Header.h"
#include "Scene.cpp"
using namespace sf;

class Player
{
public:
	void start() {

		if (!texture.loadFromFile("texture/player.png")) {
			std::cout << "Could not load texture - " << std::endl;
		}
		player.setTexture(texture);
		player.setPosition(400, 0);
	}
	void physicsUpdate(Scene map) {
		velocity = velocity + Vector2f(0.0, G);
		
		

		bool collission = false;
		for (int i = 0; i < map.getCountGamebjects(); i++) {
			GameSprite* sprite = map.findGameSpriteCash(map._gameObjects->at(i).spriteID);
			sprite->sprite.setPosition(map._gameObjects->at(i).x, map._gameObjects->at(i).y);
			sprite->sprite.setTexture(sprite->texture);
			if (player.getGlobalBounds().intersects(sprite->sprite.getGlobalBounds())) {

				//std::cout << "Collision X = " << sprite->sprite.getPosition().x << " Y = " << sprite->sprite.getPosition().y << "\n";
				collission = true;
			}
		}
		if (!collission) {
			player.setPosition(player.getPosition().x + velocity.x / 60, player.getPosition().y + velocity.y / 60);
		}


	}
	void draw(sf::RenderWindow& window) {
		window.draw(player);
	}

	bool IsCollision(sf::Sprite b) {

		return (player.getPosition().y < b.getPosition().y + b.getScale().y
			|| player.getPosition().y + player.getScale().y > b.getPosition().y
			|| player.getPosition().x + player.getScale().x < b.getPosition().x
			|| player.getPosition().x > b.getPosition().x + b.getScale().x);
	}



private:
	Sprite player;
	Texture texture;

	Vector2f velocity = Vector2f(0.0,0.0);
};

