#include "Header.h"
#include "Scene.h"
using namespace sf;
#define BlocSize = 32





class Scene
{
public:

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
			createGamebject(std::stof(data[0]), std::stof(data[1]), data[2]);
		}
		file.close();




	}

	void RenderMap(sf::RenderWindow &window) {

		Node* _temp = _first;
		for (int i = 0; i < _countGamebject; i++) {
			GameSprite* sprite = findGameSpriteCash(_temp->obj.spriteID);
			
			sprite->sprite.setPosition(_temp->obj.x, _temp->obj.y);
			sprite->sprite.setTexture(sprite->texture);
			window.draw(sprite->sprite);
			_temp = _temp->nextNode;
		}
	}

	void createGamebject(int x, int y, int spriteID) {
		if (_countGamebject == 0) {
			_first = (Node*)malloc(sizeof(Node));
			_last = _first;
		}
		else {
			_last->nextNode = (Node*)malloc(sizeof(Node));
			_last = _last->nextNode;
		}
		_countGamebject++;
		_last->obj.spriteID = spriteID;
		_last->obj.x = x;
		_last->obj.y = y;
	}
	void createGamebject(int x, int y, std::string spriteName)
	{
		if (_countGamebject == 0) {
			_first = (Node*)malloc(sizeof(Node));
			_last = _first;
		}
		else {
			_last->nextNode = (Node*)malloc(sizeof(Node));
			_last = _last->nextNode;
		}
		_countGamebject++;
		_last->obj.spriteID = findGameSpriteCash(spriteName)->spriteID;
		_last->obj.x = x;
		_last->obj.y = y;
	}

	int getCountGamebjects() {
		return _countGamebject;
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
	struct Node {
		Gameobject obj;
		Node* nextNode;
	};
	Node* _first, * _last;
	std::vector<GameSprite>* _spriteCash = new std::vector<GameSprite>(1);
	int countSpriteCash = 0;
};



