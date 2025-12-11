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
    CEGLY.clear();
    CEGLY.reserve(cegly.size());

    for (const auto& c : cegly)
    {
        CEGLYData b;
        b.x = c.getPosition().x;
        b.y = c.getPosition().y;
        b.hp = c.getHP();
        CEGLY.push_back(b);
    }
}

bool GameState::saveToFile(const std::string& filename) const //zapisuje stan gry
{
    std::ofstream file(filename);
    if (!file.is_open())
        return false;

    file <<"Paletka "<< platformaPosition.x <<" "<< platformaPosition.y << "\n";
    file <<"Pilka "<< pilkaPosition.x <<" "<< pilkaPosition.y << " "
        << pilkaVelocity.x <<" "<< pilkaVelocity.y << "\n";
    file <<"Liczba_Cegiel "<< CEGLY.size() << "\n";

    for (const auto& b : CEGLY)
        file << b.x << " " << b.y << " " << b.hp << "\n";

    file.close();
    return true;
}

bool GameState::loadFromFile(const std::string& filename) //wczytuje stan gry
{
    std::ifstream file(filename);
    if (!file.is_open())
        return false;

    std::string label;
    file >> label >> platformaPosition.x >> platformaPosition.y;
    file >> label >> pilkaPosition.x >> pilkaPosition.y >> pilkaVelocity.x >> pilkaVelocity.y;
    int count;
    file >> label >> count;
    CEGLY.clear();
    CEGLY.reserve(count);

    for (int i = 0; i < count; i++)
    {
        CEGLYData b;
        file >> b.x >> b.y >> b.hp;
        CEGLY.push_back(b);
    }

    file.close();
    return true;
}

void GameState::apply(Platforma& paddle, Pilka1& ball, std::vector<Cegla>& cegly) //odtwarza na ekranie
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

    for (const auto& b : CEGLY)
    {
        cegly.emplace_back(ceglaW, ceglaH, b.hp, sf::Vector2f(b.x, b.y));
    }
}

