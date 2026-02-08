#pragma once
#include <SFML/Graphics.hpp>

class Player {
private:
    int x;
    int y;
    int health;
    int score;

    sf::CircleShape shape;
    float tileSize;
public:
    Player(int startX, int startY, float size);
    void move(int dx, int dy);
    void takeDamage(int damage);
    int getHealth() const;
    int getX() const;
    int getY() const;
    int getScore() const;
    void setScore(int newScore);
    void addScore(int points);
    void draw(sf::RenderWindow& window) const;
};