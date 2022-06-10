#pragma once
#include "Header.h"
#include "Scene.cpp"
#include "Camera.h"
#include "UI.cpp"
#include "MapEditor.cpp"



using namespace sf;




sf::Clock gameTimerControl;
Time dt = seconds(1.f / 60.f); // Modify this to change physics rate.
Time accumulator = seconds(0.f);
bool drawn = false;



int main()
{
    //loading

    View camera(sf::FloatRect(0, 0, With, Height));
    CameraS smoothCamera;
    Scene map1;
    UI UserInterface;

    
        MapEditor mapEditor;
    


    RenderWindow window(VideoMode(With, Height), "space", sf::Style::None);
    window.setView(camera);
    window.setFramerateLimit(200);
    //window.setVerticalSyncEnabled(true);
   // window.setMouseCursorVisible(false);

    ////////Load
    map1.LoadMap("Maps/map1.mp", "Maps/include.mp");
    UserInterface.initialization();


    while (window.isOpen())
    {
        accumulator += gameTimerControl.getElapsedTime();
        gameTimerControl.restart();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { window.close(); }



        window.clear();
        map1.RenderMap(window);



        while (accumulator >= dt)
        {
            // Physics and gameplay updates.
            smoothCamera.moveCamera(camera);
            window.setView(camera);
            

            accumulator -= dt;
            drawn = false;
        }



        mapEditor.mapEdit(camera, window, map1);
        UserInterface.update(camera, window);
        window.display();

    }

    return 0;
}