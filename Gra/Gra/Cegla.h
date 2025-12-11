#pragma once
#include <SFML/Graphics.hpp>
#include <array>

static const std::array<sf::Color, 4> CeglyColors = {
    sf::Color::Transparent, //0
    sf::Color::Red, //1
    sf::Color::Yellow, //2
    sf::Color::Blue //3
};

class Cegla
{
private:
    sf::RectangleShape shape;
    int hp;

public:
    Cegla(float width, float height, int hpStart, sf::Vector2f pos)
        : hp(hpStart)
    {
        shape.setSize({ width, height });
        shape.setFillColor(CeglyColors[hpStart]);
        shape.setPosition(pos);
    }

    void draw(sf::RenderWindow& window) { window.draw(shape); }

    sf::FloatRect getBounds() const { return shape.getGlobalBounds(); }

    bool czyZniszczona() const { return hp <= 0; }

    void traf()
    {
        hp--;
        if (hp >= 0 && hp < 4)
            shape.setFillColor(CeglyColors[hp]);
    }

    int getHP() const { return hp; }
    sf::Vector2f getPosition() const { return shape.getPosition(); }
};
