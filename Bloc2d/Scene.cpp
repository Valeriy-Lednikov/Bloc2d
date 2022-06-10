#pragma once
#include "Header.h"
#include "Scene.h"
using namespace sf;


class Scene
{
public:

	std::vector<Gameobject>* _gameObjects = new std::vector<Gameobject>(1);


	std::vector<std::string> split(std::string s, std::string delimiter) {
		size_t pos_start = 0, pos_end, delim_len = delimiter.length();
		std::string token;
		std::vector<std::string> res;

		while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
			token = s.substr(pos_start, pos_end - pos_start);
			pos_start = pos_end + delim_len;
			res.push_back(token);
		}

		res.push_back(s.substr(pos_start));
		return res;
	}


	void LoadSprite(std::string include) {
		std::string line;
		std::ifstream file(include);
		while (getline(file, line)) {
			std::vector<std::string> data = split(line, ",");
			Texture texture;
			if (!texture.loadFromFile(data.at(0))) {
				std::cout << "Could not load texture - " << data.at(0) << std::endl;
			}
			Sprite sprite;
			sprite.setTexture(texture);
			_spriteCash->resize(_spriteCash->size() + 1);
			_spriteCash->at(countSpriteCash).name = data.at(1);
			_spriteCash->at(countSpriteCash).spriteID = stoi(data.at(2));
			_spriteCash->at(countSpriteCash).sprite = sprite;
			_spriteCash->at(countSpriteCash).texture = texture;
			countSpriteCash++;
		}
		file.close();
	}


	void LoadMap(std::string path, std::string include) {
		LoadSprite(include);

		std::string line;
		std::ifstream file(path);

		while (getline(file, line)) {
			std::string temp = "";
			std::vector<std::string> data = split(line, ",");
			createGamebject(std::stof(data[0]), std::stof(data[1]), stoi(data[2]));
		}
		file.close();

	}

	void RenderMap(sf::RenderWindow& window) {

		for (int i = 0; i < _countGamebject; i++) {
			GameSprite* sprite = findGameSpriteCash(_gameObjects->at(i).spriteID);
			sprite->sprite.setPosition(_gameObjects->at(i).x, _gameObjects->at(i).y);
			sprite->sprite.setTexture(sprite->texture);
			sprite->sprite.setRotation((_gameObjects->at(i).rotation));
			window.draw(sprite->sprite);
		}
	}

	void createGamebject(int x, int y, int spriteID) {
		_gameObjects->resize(_gameObjects->size() + 1);
		_gameObjects->at(_countGamebject).x = x;
		_gameObjects->at(_countGamebject).y = y;
		_gameObjects->at(_countGamebject).spriteID = spriteID;
		_countGamebject++;
	}
	void createGamebject(int x, int y, std::string spriteName)
	{
		_gameObjects->resize(_gameObjects->size() + 1);
		_gameObjects->at(_countGamebject).x = x;
		_gameObjects->at(_countGamebject).y = y;
		_gameObjects->at(_countGamebject).spriteID = findGameSpriteCash(spriteName)->spriteID;
		_countGamebject++;

	}

	bool cellIsFull(int x, int y) {
		for (int i = 0; i < _countGamebject; i++) {
			if (_gameObjects->at(i).x == x && _gameObjects->at(i).y == y) {
				return true;
			}
		}
		return false;
	}
	void deleteGamebject(int x, int y) {
		if(cellIsFull(x, y)) {
			for (int i = 0; i < _countGamebject; i++) {
				if (_gameObjects->at(i).x == x && _gameObjects->at(i).y == y) {
					_gameObjects->erase(_gameObjects->begin() + i);
					_countGamebject--;
				}
			}
		}
	}



	int getCountGamebjects() {
		return _countGamebject;
	}



	void saveScene() {
		std::ofstream file("Maps/map1.mp");
		for (int i = 0; i < _gameObjects->size() -1; i++) {
			file << _gameObjects->at(i).x << "," << _gameObjects->at(i).y << "," << _gameObjects->at(i).spriteID << "\n";
		}

	}


	GameSprite* findGameSpriteCash(int spriteID) {
		for (int i = 0; i < countSpriteCash; i++) {
			if (spriteID == _spriteCash->at(i).spriteID) {
				return &_spriteCash->at(i);
			}
		}
		return &_spriteCash->at(0);
	}
	GameSprite* findGameSpriteCash(std::string name) {
		for (int i = 0; i < countSpriteCash; i++) {
			if (name == _spriteCash->at(i).name) {
				return &_spriteCash->at(i);
			}
		}
		return &_spriteCash->at(0);
	}


private:

	int _countGamebject = 0;

	std::vector<GameSprite>* _spriteCash = new std::vector<GameSprite>(1);
	int countSpriteCash = 0;
};



