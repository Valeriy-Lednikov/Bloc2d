#include "Header.h"
#include "Scene.h"
using namespace sf;
#define BlocSize = 32
#define CountCashSprite 10




class Scene
{
public:


	void LoadMap(std::string path) {//std::string path) {
		_spriteCash = new GameSprite[CountCashSprite];
		///////////////////////////////////////////////////////////
		Texture grassT;
		if (!grassT.loadFromFile("texture/grass.png")) {
			std::cout << "Could not load texture" << std::endl;
		}
		Sprite grass;
		grass.setTexture(grassT);
		_spriteCash[0].name = "grass";
		_spriteCash[0].spriteID = 0;
		_spriteCash[0].sprite = grass;
		_spriteCash[0].texture = grassT;
		///////////////////////////////////////////////////////////
		Texture grassTL;
		if (!grassTL.loadFromFile("texture/grass-L.png")) {
			std::cout << "Could not load texture" << std::endl;
		}
		Sprite grassL;
		grassL.setTexture(grassTL);
		_spriteCash[1].name = "grass-l";
		_spriteCash[1].spriteID = 1;
		_spriteCash[1].sprite = grassL;
		_spriteCash[1].texture = grassTL;
		///////////////////////////////////////////////////////////
		Texture grassTR;
		if (!grassTR.loadFromFile("texture/grass-R.png")) {
			std::cout << "Could not load texture" << std::endl;
		}
		Sprite grassR;
		grassR.setTexture(grassTR);
		_spriteCash[2].name = "grass-r";
		_spriteCash[2].spriteID = 2;
		_spriteCash[2].sprite = grassR;
		_spriteCash[2].texture = grassTR;
		///////////////////////////////////////////////////////////
		Texture dirtT;
		if (!dirtT.loadFromFile("texture/dirt.png")) {
			std::cout << "Could not load texture" << std::endl;
		}
		Sprite dirtS;
		dirtS.setTexture(dirtT);
		_spriteCash[3].name = "dirt";
		_spriteCash[3].spriteID = 3;
		_spriteCash[3].sprite = dirtS;
		_spriteCash[3].texture = dirtT;
		///////////////////////////////////////////////////////////

		std::string map[]{ 
			"",
			"",
			"",
			"",
			"",
			"        ",
			"d                d",
			"d rggl     rgggl d",
			"dgddddgggggdddddgd",
			"",
			"" 
		};


		for (int i = 0; i < _countof(map); i++) {
			for (int ii = 0; ii < map[i].size(); ii++) {
				if (map[i][ii] == 'g') {
					createGamebject(ii * 32, i* 32, "grass");
				}
				if (map[i][ii] == 'l') {
					createGamebject(ii * 32, i * 32, "grass-l");
				}
				if (map[i][ii] == 'r') {
					createGamebject(ii * 32, i * 32, "grass-r");
				}
				if (map[i][ii] == 'd') {
					createGamebject(ii * 32, i * 32, "dirt");
				}
			}
		}




	}

	void RenderMap(sf::RenderWindow &window) {

		Node* _temp = _first;
		for (int i = 0; i < _countGamebject; i++) {
			GameSprite sprite = findGameSpriteCash(_temp->obj.spriteID);
			sprite.sprite.setPosition(_temp->obj.x, _temp->obj.y);
			sprite.sprite.setTexture(sprite.texture);
			window.draw(sprite.sprite);
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
		_last->obj.spriteID = findGameSpriteCash(spriteName).spriteID;
		_last->obj.x = x;
		_last->obj.y = y;
	}

	int getCountGamebjects() {
		return _countGamebject;
	}




	GameSprite findGameSpriteCash(int spriteID) {
		for (int i = 0; i < CountCashSprite; i++) {
			if (spriteID == _spriteCash[i].spriteID) {
				return _spriteCash[i];
			}
		}
		GameSprite temp;
		temp.name = "NULL";
			return temp;
	}
	GameSprite findGameSpriteCash(std::string name) {
		for (int i = 0; i < CountCashSprite; i++) {
			if (name == _spriteCash[i].name ) {
				return _spriteCash[i];
			}
		}
		GameSprite temp;
		temp.name = "NULL";
		return temp;
	}
	



private:

	int _countGamebject = 0;
	struct Node {
		Gameobject obj;
		Node* nextNode;
	};
	Node* _first, * _last;
	GameSprite* _spriteCash;
};



