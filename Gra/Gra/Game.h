#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Platforma.h"
#include "Pilka1.h"
#include "Cegla.h"

class Game
{
private:
    sf::Clock m_deltaClock;
    Platforma m_platforma;
    Pilka1 m_pilka;
    std::vector<Cegla> m_cegly;
    bool m_gameOver;
    bool m_win; //czy wygrales
    sf::Clock m_endClock; //liczenie czasu wyswietlania komunikatu
    float m_endDelay = 2.0f; //czas po jakim wraca do menu
    bool m_platformVisible; //czy paletka jest widoczna po jej wybuchu

    void generujCegly();

public:
    Game();
    void update(sf::Time dt, const sf::RenderWindow& window);
    void render(sf::RenderTarget& target);
    void reset();
    bool isGameOver() const { return m_gameOver; }
    void startNewGame();
    void clearGameOverFlag();

    bool shouldReturnToMenu() const; //powrot do menu po komunikacie
    std::string getEndMessage() const; //komunikat wygrales lub przegrales

    Platforma& getPlatforma() { return m_platforma; }
    Pilka1& getPilka() { return m_pilka; }
    std::vector<Cegla>& getCegly() { return m_cegly; }
};
