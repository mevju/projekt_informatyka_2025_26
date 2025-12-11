#include "Pilka1.h"
#include <cmath>

Pilka1::Pilka1(float radius, sf::Color color, sf::Vector2f startPos, sf::Vector2f startVel)
{
    shape.setRadius(radius);
    shape.setFillColor(color);
    shape.setPosition(startPos);
    velocity = startVel;
}

void Pilka1::update(const sf::RenderWindow& window)
{
    shape.move(velocity);

    float r = shape.getRadius();
    sf::Vector2f pos = shape.getPosition();
    float W = static_cast<float>(window.getSize().x);
    float H = static_cast<float>(window.getSize().y);

    if (pos.x <= 0.f)
    {
        shape.setPosition(0.f, pos.y);
        odbijX();
    }

    if (pos.x + 2 * r >= W)
    {
        shape.setPosition(W - 2 * r, pos.y);
        odbijX();
    }

    if (pos.y <= 0.f)
    {
        shape.setPosition(pos.x, 0.f);
        odbijY();
    }
}


void Pilka1::draw(sf::RenderWindow& window)
{
    window.draw(shape);
}

void Pilka1::odbijY() { velocity.y = -velocity.y; }
void Pilka1::odbijX() { velocity.x = -velocity.x; }

void Pilka1::kolizjaZPlatforma(Platforma& p)
{
    if (shape.getGlobalBounds().intersects(p.getBounds()))
    {
        odbijY();
        float center = p.getBounds().left + p.getBounds().width / 2.f;
        float hit = (shape.getPosition().x + shape.getRadius()) - center;
        velocity.x = hit * 0.1f;
    }
}

void Pilka1::kolizjaZCegly(std::vector<Cegla>& cegly)
{
    for (auto it = cegly.begin(); it != cegly.end();)
    {
        if (shape.getGlobalBounds().intersects(it->getBounds()))
        {
            it->traf();
            odbijY();

            if (it->czyZniszczona())
                it = cegly.erase(it);
            else
                ++it;
        }
        else
            ++it;
    }
}

void Pilka1::reset(const sf::Vector2f& pos, const sf::Vector2f& vel)
{
    shape.setPosition(pos);
    velocity = vel;
}
