#include "button.h"
#include <SFML/Graphics.hpp>

class Button {
public:
    Button(const std::string& text, const sf::Font& font, unsigned int size, const sf::Color& color, const sf::Vector2f& position) {
        m_text.setString(text);
        m_text.setFont(font);
        m_text.setCharacterSize(size);
        m_text.setFillColor(color);
        m_text.setPosition(position);

        m_shape.setSize(sf::Vector2f(m_text.getGlobalBounds().width + 10.f, m_text.getGlobalBounds().height + 15.f));
        m_shape.setFillColor(sf::Color::Transparent);
        m_shape.setOutlineColor(color);
        m_shape.setOutlineThickness(2.f);
        m_shape.setPosition(position.x - 5.f, position.y - 5.f);

        m_pressed = false;
    }
    std::string getText() const {
        return m_text.getString();
    }
    void setText(const std::string& text) {
        m_text.setString(text);
    }
    sf::RectangleShape getShape() const {
        return m_shape;
    }
    void setTextFillcolor(const sf::Color& color) { m_text.setFillColor(color); }
    void setShapeFillColor(const sf::Color& color) { m_shape.setFillColor(color); }
    void setShape(const sf::RectangleShape& shape) {
        m_shape = shape;
    }

    void draw(sf::RenderTarget& target) {
        target.draw(m_shape);
        target.draw(m_text);
    }

    bool isMouseOver(const sf::RenderWindow& window) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        return m_shape.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    }

    bool isPressed() {
        return m_pressed;
    }

    void setPressed(bool pressed) {
        m_pressed = pressed;
    }

private:

    sf::Text m_text;
    sf::RectangleShape m_shape;
    bool m_pressed;
};