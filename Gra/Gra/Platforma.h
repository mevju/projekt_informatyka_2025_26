#pragma once
#include <SFML/Graphics.hpp>

class Platforma
{
private:
    sf::RectangleShape shape;
    float speed;
    bool visible;

public:
    Platforma(float width, float height, sf::Color color, sf::Vector2f startPos, float speed);

    void update(const sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);

    sf::Vector2f getPosition() const { return shape.getPosition(); }
    void setPosition(const sf::Vector2f& pos) { shape.setPosition(pos); }
    void setVisible(bool v) { visible = v; }
    bool isVisible() const { return visible; }

    sf::FloatRect getBounds() const { return shape.getGlobalBounds(); }
};
