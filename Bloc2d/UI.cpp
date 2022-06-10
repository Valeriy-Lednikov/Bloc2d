#pragma once
#include "Header.h"
#include "Camera.h"


class UI
{
public:
	void update(sf::View &camera, sf::RenderWindow &window) {

		

		currentTime = timerFPS.getElapsedTime();
		fps = 1.0f / (currentTime.asSeconds() - previousTime.asSeconds()); // the asSeconds returns a float
		std::string s_textFPS = "fps = " + std::to_string((int)floor(fps));
		textFPS.setString(s_textFPS);
		textFPS.setPosition(camera.getCenter().x - With / 2, camera.getCenter().y - Height / 2);
		window.draw(textFPS);
		previousTime = currentTime;




	}
	void initialization() {
		if (!font_Arial.loadFromFile("Fonts/arial.ttf"))
		{
			std::cout << "Error!";
		}

		textFPS.setFont(font_Arial);
		textFPS.setCharacterSize(24);
		textFPS.setFillColor(sf::Color::Red);

	}
private:
	struct UIobject
	{
		int x = 0, y = 0;
	};

	std::vector<UIobject> UIobjects;

	sf::Font font_Arial;
	sf::Text textFPS;


	float fps = 0;
	sf::Clock timerFPS;
	sf::Time previousTime = timerFPS.getElapsedTime();
	sf::Time currentTime;


};

