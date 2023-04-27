#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include "button.cpp"

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
void displayText(sf::RenderWindow& window, sf::Font& font,const string& str
    , const int char_size,const int ch_Y, const int ch_X)
{
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(char_size);
    text.setFillColor(sf::Color::White);
    text.setPosition(ch_X, ch_Y);
    string currentTime = getCurrentTime();
    text.setString(str);
    window.draw(text);
}
void displayLoading(sf::RenderWindow& window, const std::string& fileName)
{

    sf::Texture loadingTexture;
    if (!loadingTexture.loadFromFile(fileName))
    {
        std::cout << "Error loading loading image" << std::endl;
    }
    sf::Sprite loadingSprite;
    loadingSprite.setTexture(loadingTexture);

    sf::Vector2u imageSize = loadingTexture.getSize();
    sf::Vector2u windowSize = window.getSize();

    float scaleX = static_cast<float>(windowSize.x) / imageSize.x;
    float scaleY = static_cast<float>(windowSize.y) / imageSize.y;

    loadingSprite.setScale(scaleX, scaleY);

    window.draw(loadingSprite);


}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "wonder world");
    sf::Texture backgroundTexture;

    sf::Font font;

    font.loadFromFile("arial.ttf");
    bool enterPressed = false;
    backgroundTexture.loadFromFile("background.jpg");


    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);
    sf::Vector2u imageSize = backgroundTexture.getSize();
    sf::Vector2u windowSize = window.getSize();

    float scaleX = static_cast<float>(windowSize.x) / imageSize.x;
    float scaleY = static_cast<float>(windowSize.y) / imageSize.y;

    Button playButton("Play", font, 40, sf::Color::Green, sf::Vector2f(100,100));
    Button aboutButton("about", font, 40, sf::Color::Green, sf::Vector2f(100, 200));
    Button creditsButton("credits", font, 40, sf::Color::Green, sf::Vector2f(100, 300));
    Button exitButton("exit", font, 40, sf::Color::Green, sf::Vector2f(100, 400));
    backgroundSprite.setScale(scaleX, scaleY);


    while (window.isOpen())
    {
        sf::Event event;
        //
        if (playButton.isMouseOver(window)) { 
            playButton.setTextFillcolor(sf::Color::White);
        }
        else {     playButton.setShapeFillColor(sf::Color::Blue);
        }
        if (aboutButton.isMouseOver(window)) {
            aboutButton.setTextFillcolor(sf::Color::White);
        }
        else {
            aboutButton.setShapeFillColor(sf::Color::Blue);
        }
        if (creditsButton.isMouseOver(window)) {
            creditsButton.setTextFillcolor(sf::Color::White);
        }
        else {
            creditsButton.setShapeFillColor(sf::Color::Blue);
        }
        if (exitButton.isMouseOver(window)) {
            exitButton.setTextFillcolor(sf::Color::White);
        }
        else {
            exitButton.setShapeFillColor(sf::Color::Blue);
        }
        //
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Enter)
                {
                    enterPressed = true;
                }
            }
            
        }

        string currentTime = getCurrentTime();
        sf::Font font;

        font.loadFromFile("arial.ttf");

        window.clear(sf::Color::Black);
        if (enterPressed)
        {
            window.draw(backgroundSprite);
            playButton.draw(window);
            displayText(window, font,currentTime,35,10, 650);
            aboutButton.draw(window);
            creditsButton.draw(window);
            exitButton.draw(window);

        }
        else
        {
            displayLoading(window, "loading.png");
            displayText(window, font, "wonder world", 50, 200, 200);
        }
  
        window.display();
    }


    return 0;
}