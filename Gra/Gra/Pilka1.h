#pragma once
#include <SFML/Graphics.hpp>
#include "Platforma.h"
#include "Cegla.h"
#include <vector>

class Pilka1
{
private:
    sf::CircleShape shape;
    sf::Vector2f velocity;

public:
    Pilka1(float radius, sf::Color color, sf::Vector2f startPos, sf::Vector2f startVel);

    void update(const sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);

    sf::Vector2f getVelocity() const { return velocity; }
    void odbijY();
    void odbijX();

    sf::FloatRect getBounds() const { return shape.getGlobalBounds(); }
    void kolizjaZPlatforma(Platforma& platforma);
    void kolizjaZCegly(std::vector<Cegla>& cegly);

    sf::Vector2f getPosition() const { return shape.getPosition(); }
    void reset(const sf::Vector2f& pos, const sf::Vector2f& vel);
};