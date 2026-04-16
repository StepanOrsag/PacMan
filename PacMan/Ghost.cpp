#include "Ghost.hpp"
#include <vector>
#include <cstdlib>
#include <ctime>

Ghost::Ghost(int startX, int startY, float size, sf::Color color) 
    : x(startX), y(startY), tileSize(size), moveInterval(0.2f) 
{
    shape.setSize(sf::Vector2f(tileSize - 4, tileSize - 4));
    shape.setFillColor(color);
    shape.setOrigin(sf::Vector2f(0, 0)); 
    shape.setPosition(sf::Vector2f(x * tileSize + 2, y * tileSize + 2));
    
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

void Ghost::update(Map& map) {
    if (moveClock.getElapsedTime().asSeconds() < moveInterval) {
        return;
    }

    std::vector<sf::Vector2i> directions = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}
    };

    for (size_t i = 0; i < directions.size(); ++i) {
        size_t j = std::rand() % directions.size();
        std::swap(directions[i], directions[j]);
    }

    for (const auto& dir : directions) {
        int nextX = x + dir.x;
        int nextY = y + dir.y;

        if (!map.isWall(nextX, nextY)) {
            x = nextX;
            y = nextY;
            shape.setPosition(sf::Vector2f(x * tileSize + 2, y * tileSize + 2));
            break;
        }
    }

    moveClock.restart();
}

void Ghost::draw(sf::RenderWindow& window) const {
    window.draw(shape);
}
