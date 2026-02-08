#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class Map {
private:
    std::vector<std::vector<int>> grid;
    float tileSize;

    sf::RectangleShape wallShape;
    sf::CircleShape dotShape;
public:
    Map(float size);

    void draw(sf::RenderWindow& window);

    bool isWall(int x, int y);
    int tryEatDot(int x, int y);
    int getDotCount();
};