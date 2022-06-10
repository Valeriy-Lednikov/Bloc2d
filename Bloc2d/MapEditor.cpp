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
				window.setMouseCursorVisible(false);

				GameSprite* sprite = map.findGameSpriteCash(ChoseSprite);
				sprite->sprite.setPosition(camera.getCenter().x + sf::Mouse::getPosition().x - With / 2 - 16, camera.getCenter().y + sf::Mouse::getPosition().y - Height / 2 - 16);
				sprite->sprite.setTexture(sprite->texture);
				window.draw(sprite->sprite);


				int x = round(sprite->sprite.getPosition().x / 32) * 32;
				int y = round(sprite->sprite.getPosition().y / 32) * 32;

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::V)) {
					if (map.cellIsFull(x, y)) {
						std::cout << "Delete - " << "x = " << x << " y = " << y << "\n";
						map.deleteGamebject(x, y);
					}

				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
					if (!map.cellIsFull(x, y)) {
						std::cout << "Create - " << "x = " << x << " y = " << y << " Sprite = " << ChoseSprite << "\n";
						map.createGamebject(x, y, ChoseSprite);
					}

				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
					map.saveScene();
					std::cout << "Map Save - Save/map.mp" << "\n";
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0)) {
					ChoseSprite = 0;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1)) {
					ChoseSprite = 1;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2)) {
					ChoseSprite = 2;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3)) {
					ChoseSprite = 3;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4)) {
					ChoseSprite = 4;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5)) {
					ChoseSprite = 5;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6)) {
					ChoseSprite = 6;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad7)) {
					ChoseSprite = 7;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8)) {
					ChoseSprite = 8;
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