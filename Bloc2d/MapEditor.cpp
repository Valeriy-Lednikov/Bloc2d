#pragma once
#include "Header.h"
#include "Scene.cpp"




class MapEditor
{
public:

	void DrawGrid(sf::View& camera, sf::RenderWindow& window) {
		sf::RectangleShape lineW(sf::Vector2f(With, 1));
		sf::RectangleShape lineH(sf::Vector2f(1, Height));
		sf::Vector2f  WinLeftUp = sf::Vector2f(camera.getCenter().x - With / 2, camera.getCenter().y - Height / 2);
		sf::Vector2f  WinRightDown = sf::Vector2f(camera.getCenter().x + With / 2, camera.getCenter().y + Height / 2);

		for (float i = round(WinLeftUp.x / 32) * 32; i < WinRightDown.x; i = i + 32) {
			lineH.setPosition(i, WinLeftUp.y);
			window.draw(lineH);
		}
		for (float i = round(WinLeftUp.y / 32) * 32; i < WinRightDown.y; i = i + 32) {
			lineW.setPosition(WinLeftUp.x, i);
			window.draw(lineW);
		}
	}


	void mapEdit(sf::View& camera, sf::RenderWindow& window, Scene& map) {
		if (MapEdit) {
			DrawGrid(camera, window);
			if (ChoseSprite >= 0) {

				GameSprite* sprite = map.findGameSpriteCash(ChoseSprite);
				sprite->sprite.setPosition(camera.getCenter().x + sf::Mouse::getPosition().x - With / 2, camera.getCenter().y + sf::Mouse::getPosition().y - Height / 2);
				sprite->sprite.setTexture(sprite->texture);
				window.draw(sprite->sprite);

				Event event;                  
				window.pollEvent(event);  

				if (event.type == Event::KeyPressed) {
					if (event.key.code == Keyboard::Space) {
						int x = round(sprite->sprite.getPosition().x / 32) * 32;
						int y = round(sprite->sprite.getPosition().y / 32) * 32;
						std::cout << "x = " << x << " y = " << y << " Sprite = " << ChoseSprite << "\n";
						map.createGamebject(x, y, ChoseSprite);
					}
				}
			}
		}
	}



private:
	int ChoseSprite = 1;
};















//Выбор блока и отмена 
//Установка
//Сохранение карты