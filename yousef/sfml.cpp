#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
using namespace std;

string getCurrentTime()
{
    time_t now = time(0);
    tm local;
    localtime_s(&local, &now);
    stringstream ss;
    ss << local.tm_hour << ":" << local.tm_min << ":" << local.tm_sec;
    return ss.str();
}
void displayTime(sf::RenderWindow& window, sf::Font& font)
{
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(26);
    text.setFillColor(sf::Color::White);
    text.setPosition(10, 10);
    string currentTime = getCurrentTime();
    text.setString(currentTime);
    window.draw(text);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "wonder world");
    sf::Texture backgroundTexture;

    if (!backgroundTexture.loadFromFile("background.jpg"))
    {
        cout << "Error loading background image" <<endl;
    }


    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);
    sf::Vector2u imageSize = backgroundTexture.getSize();
    sf::Vector2u windowSize = window.getSize();

    float scaleX = static_cast<float>(windowSize.x) / imageSize.x;
    float scaleY = static_cast<float>(windowSize.y) / imageSize.y;

    backgroundSprite.setScale(scaleX, scaleY);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            {
                window.close();
            }
        }


        sf::Font font;
        if (!font.loadFromFile("arial1.ttf"))
        {
            std::cout << "Error loading font file" << std::endl;
        }


        window.clear(sf::Color::Black);
        window.draw(backgroundSprite);
        displayTime(window, font);
        window.display();
    }

    return 0;
}