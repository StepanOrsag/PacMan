#include "Player.hpp"

Player::Player(int startX, int startY, float size) :
    x(startX), y(startY), health(3), score(0), tileSize(size)
{

    shape.setRadius(tileSize / 2);
    shape.setFillColor(sf::Color::Yellow);
    //shape.setOrigin(sf::Vector2(tileSize / 2, tileSize / 2));

    shape.setPosition(sf::Vector2(x * tileSize, y * tileSize));
}

void Player::move(int dx, int dy) {
    x += dx;
    y += dy;
    shape.setPosition(sf::Vector2(x * tileSize, y * tileSize));
}

void Player::takeDamage(int damage) {
    if (health > 0) {
        health -= damage;
    }
    else {
        health = 0;
    }
}

int Player::getHealth() const {
    return health;
}
int Player::getX() const {
    return x;
}
int Player::getY() const {
    return y;
}
int Player::getScore() const {
    return score;
}
void Player::setScore(int newScore) {
    score = newScore;
}
void Player::addScore(int points) {
    score += points;
}
void Player::draw(sf::RenderWindow& window) const {
    window.draw(shape);
}