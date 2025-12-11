#include "Menu.h"

Menu::Menu(float width, float height)
{
    font.loadFromFile("arial.ttf");

    //nowa gra
    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::Red);
    menu[0].setString("Nowa gra");
    menu[0].setPosition(width / 2 - 100, height / 2 - 80);

    //wczytaj gre
    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("Wczytaj gre");
    menu[1].setPosition(width / 2 - 100, height / 2 - 20);

    //wyjscie
    menu[2].setFont(font);
    menu[2].setFillColor(sf::Color::White);
    menu[2].setString("Wyjscie");
    menu[2].setPosition(width / 2 - 100, height / 2 + 100);

    selectedItemIndex = 0;
}

void Menu::draw(sf::RenderWindow& window)
{
    for (int i = 0; i < MAX_ITEMS; i++)
    {
        window.draw(menu[i]);
    }
}

void Menu::moveUp()
{
    if (selectedItemIndex - 1 >= 0)
    {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void Menu::moveDown()
{
    if (selectedItemIndex + 1 < MAX_ITEMS)
    {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}
