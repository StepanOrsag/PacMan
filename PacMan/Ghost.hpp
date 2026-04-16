#pragma once
#include <SFML/Graphics.hpp>
#include "Map.hpp"

class Ghost {
private:
    int x, y;
    float tileSize;
    sf::RectangleShape shape;
    sf::Clock moveClock;
    float moveInterval;

public:
    Ghost(int startX, int startY, float size, sf::Color color);
    void update(Map& map);
    void draw(sf::RenderWindow& window) const;
    
    int getX() const { return x; }
    int getY() const { return y; }
};
