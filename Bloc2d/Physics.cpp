#include "Header.h"

bool IsCollision(sf::Sprite a, sf::Sprite b) {
	return (a.getPosition().y < b.getPosition().y + b.getScale().y 
		|| a.getPosition().y + a.getScale().y > b.getPosition().y 
		|| a.getPosition().x + a.getScale().x < b.getPosition().x 
		|| a.getPosition().x > b.getPosition().x + b.getScale().x);
	//return ( a.y < b.y1 || a.y1 > b.y || a.x1 < b.x || a.x > b.x1 );
}