#pragma once
#include "Header.h"


class Physics
{
public:


private:

};




class BoxCollider
{
public:

	BoxCollider(sf::Vector2f size, sf::Vector2f position);

	bool IsCollision(sf::Sprite b) {

		return (_position.y < b.getPosition().y + b.getScale().y
			|| _position.y + _size.y > b.getPosition().y
			|| _position.x + _size.x < b.getPosition().x
			|| _position.x > b.getPosition().x + b.getScale().x);
	}

private:
	sf::Vector2f _size;
	sf::Vector2f _position;
	
};


BoxCollider::BoxCollider(sf::Vector2f size, sf::Vector2f position) {
	_size = size;
	_position = position;
}

