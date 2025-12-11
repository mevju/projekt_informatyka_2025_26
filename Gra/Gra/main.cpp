#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Menu.h"
#include "GameState.h"
#include <iostream>

//wyswietlanie dynamiczne odliczania
void showCountdown(sf::RenderWindow& window, const sf::Font& font)
{
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(96);
    text.setFillColor(sf::Color::Green);

    const std::vector<std::string> steps = { "3", "2", "1", "START" };
    for (size_t i = 0; i < steps.size(); ++i)
    {
        text.setString(steps[i]);
        //ustawia na srodku
        sf::FloatRect r = text.getLocalBounds();
        text.setOrigin(r.left + r.width / 2.f, r.top + r.height / 2.f);
        text.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);

        sf::Clock clk;
        while (clk.getElapsedTime().asSeconds() < 0.8f)
        {
            sf::Event e;
            while (window.pollEvent(e))
            {
                if (e.type == sf::Event::Closed) window.close();
            }
            window.clear();
            window.draw(text);
            window.display();
        }
    }
}

enum class GameStateEnum { Menu, Playing, Exiting };

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Arkanoid");
    window.setFramerateLimit(60);

    //ladowanie czcionki
    sf::Font arial;
    if (!arial.loadFromFile("arial.ttf"))
    {
        std::cerr << "Nie masz czcionki arial.tft\n";
    }

    Menu menu(window.getSize().x, window.getSize().y);
    Game game;

    GameStateEnum currentState = GameStateEnum::Menu;
    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            //zapisywanie klawiszem F5
            if (event.type == sf::Event::KeyPressed && currentState == GameStateEnum::Playing)
            {
                if (event.key.code == sf::Keyboard::F5)
                {
                    GameState gs;
                    gs.capture(game.getPlatforma(), game.getPilka(), game.getCegly());
                    if (gs.saveToFile("zapis-gry.txt"))
                        std::cout << "Gra zapisana\n";
                    else
                        std::cout << "Nie udalo sie zapisac\n";
                }
            }

            //obsluga klawiszy w menu
            if (currentState == GameStateEnum::Menu && event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Up) menu.moveUp();
                if (event.key.code == sf::Keyboard::Down) menu.moveDown();

                if (event.key.code == sf::Keyboard::Enter)
                {
                    int selected = menu.getSelectedItem();

                    //nowa gra
                    if (selected == 0)
                    {
                        game.startNewGame();
                        showCountdown(window, arial); //pokazuje odliczanie przed rozpoczeciem gry

                        currentState = GameStateEnum::Playing;
                    }

                    //wczytaj gre
                    else if (selected == 1)
                    {
                        GameState gs;
                        if (gs.loadFromFile("zapis-gry.txt"))
                        {
                            gs.apply(game.getPlatforma(), game.getPilka(), game.getCegly());
                            game.clearGameOverFlag();
                            showCountdown(window, arial); //pokazuje odliczanie przed wczytaniem gry

                            currentState = GameStateEnum::Playing;
                            std::cout << "Wczytano gre!\n";
                        }
                        else
                        {
                            std::cout << "Brak pliku zapis-gry.txt!\n";
                        }
                    }

                    //wyjscie
                    else if (selected == 2)
                    {
                        window.close();
                    }
                }
            }
        }

        sf::Time dt = clock.restart();

        //aktualizuje gre gdy dziala
        if (currentState == GameStateEnum::Playing)
        {
            game.update(dt, window);

            //opoznienie powrotu do menu
            if (game.shouldReturnToMenu())
            {
                currentState = GameStateEnum::Menu;
            }
        }

        //rysowanie
        window.clear();

        if (currentState == GameStateEnum::Menu)
            menu.draw(window);
        else if (currentState == GameStateEnum::Playing)
            game.render(window);

        window.display();
    }

    return 0;
}
