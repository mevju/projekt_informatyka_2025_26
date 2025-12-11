#pragma once
#include <SFML/Graphics.hpp>

#define MAX_ITEMS 3

class Menu
{
public:
    Menu(float width, float height);

    void draw(sf::RenderWindow& window);
    void moveUp();
    void moveDown();
    int getSelectedItem() const { return selectedItemIndex; }

private:
    int selectedItemIndex;
    sf::Font font;
    sf::Text menu[MAX_ITEMS];
};
