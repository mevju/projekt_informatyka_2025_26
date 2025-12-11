#include "GameState.h"
#include "Platforma.h"
#include "Pilka1.h"
#include "Cegla.h"
#include <fstream>
#include <iostream>

void GameState::capture(const Platforma& platforma,
    const Pilka1& pilka,
    const std::vector<Cegla>& cegly)
{
    platformaPosition = platforma.getPosition();
    pilkaPosition = pilka.getPosition();
    pilkaVelocity = pilka.getVelocity();
    blocks.clear();
    blocks.reserve(cegly.size());

    for (const auto& c : cegly)
    {
        BlockData b;
        b.x = c.getPosition().x;
        b.y = c.getPosition().y;
        b.hp = c.getHP();
        blocks.push_back(b);
    }
}

bool GameState::saveToFile(const std::string& filename) const
{
    std::ofstream file(filename);
    if (!file.is_open())
        return false;

    file <<"Paletka "<< platformaPosition.x <<" "<< platformaPosition.y << "\n";
    file <<"Pilka "<< pilkaPosition.x <<" "<< pilkaPosition.y << " "
        << pilkaVelocity.x <<" "<< pilkaVelocity.y << "\n";
    file <<"BLOCKS_COUNT "<< blocks.size() << "\n";

    for (const auto& b : blocks)
        file << b.x << " " << b.y << " " << b.hp << "\n";

    file.close();
    return true;
}

bool GameState::loadFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
        return false;

    std::string label;
    file >> label >> platformaPosition.x >> platformaPosition.y;
    file >> label >> pilkaPosition.x >> pilkaPosition.y >> pilkaVelocity.x >> pilkaVelocity.y;
    int count;
    file >> label >> count;
    blocks.clear();
    blocks.reserve(count);

    for (int i = 0; i < count; i++)
    {
        BlockData b;
        file >> b.x >> b.y >> b.hp;
        blocks.push_back(b);
    }

    file.close();
    return true;
}

void GameState::apply(Platforma& paddle, Pilka1& ball, std::vector<Cegla>& cegly)
{
    paddle.setPosition(platformaPosition);
    ball.reset(pilkaPosition, pilkaVelocity);
    cegly.clear();

    const int cols = 8;
    float windowWidth = 800.f;
    float offsetX = 5.f;
    float spacing = 4.f;
    float ceglaW = (windowWidth - offsetX * 2 - spacing * (cols - 1)) / cols;
    float ceglaH = 25.f;

    for (const auto& b : blocks)
    {
        cegly.emplace_back(ceglaW, ceglaH, b.hp, sf::Vector2f(b.x, b.y));
    }
}

