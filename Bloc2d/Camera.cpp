#include "Header.h"


class CameraS
{
private:
	struct Velocity
	{
		double x = 0.001;
		double y = 0.001;
	};
	Velocity _camera;
public:

	void moveCamera(sf::View& myCamera) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { _camera.x = _camera.x - 1; }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { _camera.x = _camera.x + 1; }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { _camera.y = _camera.y + 1; }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { _camera.y = _camera.y - 1; }

		_camera.x = _camera.x / 1.2;
		_camera.y = _camera.y / 1.2;

		myCamera.move(_camera.x, _camera.y);

	}
	Velocity getPosition() {
		return _camera;
	}


};

