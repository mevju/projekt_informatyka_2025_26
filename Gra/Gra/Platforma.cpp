#include "Platforma.h"

Platforma::Platforma(float width, float height, sf::Color color, sf::Vector2f startPos, float spd)
{
    shape.setSize({ width, height });
    shape.setFillColor(color);
    shape.setPosition(startPos);
    speed = spd;
    visible = true;
}

void Platforma::update(const sf::RenderWindow& window)
{
    if (!visible) return; //gdy paletka wybuchnie to jest nie widoczna i nie mozna nia ruszac

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        shape.move(-speed, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        shape.move(speed, 0.f);

    float W = static_cast<float>(window.getSize().x);
    sf::Vector2f pos = shape.getPosition();

    if (pos.x < 0.f) shape.setPosition(0.f, pos.y);
    if (pos.x + shape.getSize().x > W)
        shape.setPosition(W - shape.getSize().x, pos.y);
}

void Platforma::draw(sf::RenderWindow& window)
{
    if (!visible) return; //nie rysujemy gdy nie widoczna paletka 
    window.draw(shape);
}








