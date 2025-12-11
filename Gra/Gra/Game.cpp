#include "Game.h"
#include <string>

Game::Game()
    : m_platforma(100.f, 20.f, sf::Color::White, { 350.f, 550.f }, 8.f),
    m_pilka(10.f, sf::Color::White, { 390.f, 300.f }, { 4.f, -4.f }),
    m_gameOver(false),
    m_win(false),
    m_platformVisible(true)
{
    generujCegly();
}

void Game::generujCegly()
{
    m_cegly.clear();

    const int wiersze = 5;
    const int kolumny = 8;
    float windowWidth = 800.f;
    float offsetX = 5.f;
    float offsetY = 50.f;
    float spacing = 4.f;
    float ceglaW = (windowWidth - offsetX * 2 - spacing * (kolumny - 1)) / kolumny;
    float ceglaH = 25.f;

    for (int r = 0; r < wiersze; r++)
    {
        int hp = 1;
        if (r == 0) hp = 3;
        else if (r == 1 || r == 2) hp = 2;
        else hp = 1;

        for (int c = 0; c < kolumny; c++)
        {
            sf::Vector2f pos(
                offsetX + c * (ceglaW + spacing),
                offsetY + r * (ceglaH + spacing)
            );

            m_cegly.emplace_back(ceglaW, ceglaH, hp, pos);
        }
    }
}

void Game::clearGameOverFlag()
{
    m_gameOver = false;
    m_win = false;
    m_platformVisible = true;
    m_platforma.setVisible(true); //przyrwaca paletke
}

void Game::update(sf::Time dt, const sf::RenderWindow& window)
{
    if (m_gameOver)
    {
        return;
    }

    //aktualizacja
    m_platforma.update(window);
    m_pilka.update(window);
    m_pilka.kolizjaZPlatforma(m_platforma);
    m_pilka.kolizjaZCegly(m_cegly);

    //sprawdzenie czy wszystkie cegly zostaly zniszczone jak tak to wygrana
    if (m_cegly.empty() && !m_gameOver)
    {
        m_win = true;
        m_gameOver = true;
        m_endClock.restart();
        m_pilka.reset(m_pilka.getPosition(), { 0.f, 0.f }); //pilka stop
        return;
    }

    //sprawdzenie czy pilka spadla ponizej paletki jesli tak to nastepuje wybuch paletki
    float pilkaY = m_pilka.getPosition().y;
    float platformaY = m_platforma.getPosition().y;
    float platformaH = m_platforma.getBounds().height;

    if (pilkaY > platformaY + platformaH && !m_gameOver)
    {
        //paletka wybucha i znika
        m_platformVisible = false;
        m_platforma.setVisible(false);
        m_win = false;
        m_gameOver = true;
        m_endClock.restart();

        //pilka stop
        m_pilka.reset(m_pilka.getPosition(), { 0.f, 0.f });
        return;
    }

    //zabezpieczenie jesli pilka wyjdzie ponizej paletki
    if (m_pilka.getPosition().y > window.getSize().y + 200 && !m_gameOver)
    {
        m_platformVisible = false;
        m_platforma.setVisible(false);
        m_win = false;
        m_gameOver = true;
        m_endClock.restart();
    }
}

void Game::render(sf::RenderTarget& target)
{
    //jesli paletka jest widoczna to ja rysujemy
    if (m_platformVisible)
        m_platforma.draw((sf::RenderWindow&)target);

    //rysujemy pilke
    m_pilka.draw((sf::RenderWindow&)target);

    //rysujemy cegly
    for (auto& c : m_cegly)
        c.draw((sf::RenderWindow&)target);

    //wyswietlane jest przegrales albo wygrales
    if (m_gameOver)
    {
        sf::Font font;
        if (!font.loadFromFile("arial.ttf"))
        {
            return;
        }

        sf::Text txt;
        txt.setFont(font);
        txt.setCharacterSize(48);
        txt.setFillColor(sf::Color::White);
        txt.setString(getEndMessage());

        //ustawienie na srodku
        sf::FloatRect r = txt.getLocalBounds();
        txt.setOrigin(r.left + r.width / 2.f, r.top + r.height / 2.f);
        txt.setPosition(((sf::RenderWindow&)target).getSize().x / 2.f, ((sf::RenderWindow&)target).getSize().y / 2.f);
        ((sf::RenderWindow&)target).draw(txt);

        //efekt wybuchu paletki i pokazanie sie okregow tworzacych chmure dymu, ustawione w roznych losowych miejscach aby spowodowac nieregularny ksztalt
        if (!m_platformVisible)
        {
            float elapsed = m_endClock.getElapsedTime().asSeconds();
            if (elapsed < 2.0f)
            {
                sf::Vector2f center(
                    m_platforma.getPosition().x + m_platforma.getBounds().width / 2.f,
                    m_platforma.getPosition().y + m_platforma.getBounds().height / 2.f
                );

                const int warstwy = 8;

                for (int i = 0; i < warstwy; i++)
                {
                    float offsetX = static_cast<float>(rand() % 40 - 20);
                    float offsetY = static_cast<float>(rand() % 40 - 20);
                    float baseRadius = 50.f + elapsed * 60.f;
                    float radiusVariation = static_cast<float>(rand() % 30 - 15);
                    float radius = baseRadius + radiusVariation;

                    sf::CircleShape cloud(radius);
                    cloud.setOrigin(radius, radius);
                    cloud.setFillColor(sf::Color::White);
                    cloud.setPosition(center.x + offsetX, center.y + offsetY);
                    ((sf::RenderWindow&)target).draw(cloud);
                }
            }
        }
    }
}

void Game::reset()
{
    m_pilka.reset({ 390.f, 300.f }, { 4.f, -4.f });
    generujCegly();
    m_gameOver = false;
    m_win = false;
    m_platformVisible = true;
    m_platforma.setVisible(true);
}

void Game::startNewGame()
{
    reset();
}

bool Game::shouldReturnToMenu() const
{
    if (!m_gameOver) return false;
    return m_endClock.getElapsedTime().asSeconds() >= m_endDelay;
}

std::string Game::getEndMessage() const
{
    return m_win ? "Wygrales!" : "Przegrales!";
}
