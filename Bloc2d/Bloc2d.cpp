#include "Header.h"
#include "Scene.cpp"
#include "Camera.cpp"



const int With = GetSystemMetrics(SM_CXSCREEN);
const int Height = GetSystemMetrics(SM_CYSCREEN);


using namespace sf;


float fps = 0;
Clock timerFPS;
sf::Time previousTime = timerFPS.getElapsedTime();
sf::Time currentTime;


sf::Clock gameTimerControl;
Time dt = seconds(1.f / 60.f); // Modify this to change physics rate.
Time accumulator = seconds(0.f);
bool drawn = false;



int main()
{
    //loading
    sf::Font font;
    if (!font.loadFromFile("Fonts/arial.ttf"))
    {
        std::cout << "Error!";
    }

    Camera smoothCamera;
    View camera(sf::FloatRect(0, 0, With, Height));
    

    Scene map1; 

    RenderWindow window(VideoMode(With, Height), "space", sf::Style::None);
    //window.setFramerateLimit(100);
    window.setView(camera);
    //window.setVerticalSyncEnabled(true);


    ////////Load
    map1.LoadMap("/Maps/map1.mp");
    Text textFPS;
    textFPS.setFont(font);
    textFPS.setCharacterSize(24);
    textFPS.setFillColor(sf::Color::Red);


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





        currentTime = timerFPS.getElapsedTime();
        fps = 1.0f / (currentTime.asSeconds() - previousTime.asSeconds()); // the asSeconds returns a float
        std::string s_textFPS = "fps = " + std::to_string(floor(fps));
        textFPS.setString(s_textFPS);
        textFPS.setPosition(camera.getCenter().x-With/2, camera.getCenter().y-Height/2);
        window.draw(textFPS);
        //std::cout << "fps =" << floor(fps) << std::endl; // flooring it will make the frame rate a rounded number
        previousTime = currentTime;

        window.display();

    }

    return 0;
}