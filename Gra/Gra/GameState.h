#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

struct CEGLYData
{
    float x, y;
    int hp;
};

class Platforma;
class Pilka1;
class Cegla;

class GameState
{
    public:
        sf::Vector2f platformaPosition;
        sf::Vector2f pilkaPosition;
        sf::Vector2f pilkaVelocity;
        std::vector<CEGLYData> CEGLY;

        GameState() = default;
        void capture(const Platforma& platforma,
        const Pilka1& ball,
        const std::vector<Cegla>& cegly);
        bool saveToFile(const std::string& filename) const;
        bool loadFromFile(const std::string& filename);
        void apply(Platforma& platforma, Pilka1& pilka, std::vector<Cegla>& cegly);
};
