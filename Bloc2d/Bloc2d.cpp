#include "Header.h"
#include "Map.cpp"
#include "Camera.cpp"

const int With = GetSystemMetrics(SM_CXSCREEN);
const int Height = GetSystemMetrics(SM_CYSCREEN);

using namespace sf;



int main()
{

    //loading
    Texture grassT;
    grassT.loadFromFile("F:/__Project/__2022/Bloc2d/Bloc2d/texture/grass.png");
    Sprite grass;
    grass.setTexture(grassT);
    grass.setPosition(With/2, Height/2);

    Camera smoothCamera;
    View camera(sf::FloatRect(0, 0, With, Height));
    

    RenderWindow window(VideoMode(With, Height), "space", sf::Style::None);
    window.setFramerateLimit(60);
    window.setView(camera);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { window.close(); }



        
        window.clear();


        smoothCamera.moveCamera(camera);
        window.setView(camera);
       

        window.draw(grass);
        window.display();
    }

    return 0;
}