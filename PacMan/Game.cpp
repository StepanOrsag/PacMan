#include "Game.hpp"
#include <string>

Game::Game() : 
    window(sf::VideoMode({ static_cast<unsigned int>(20 * 32), static_cast<unsigned int>(11 * 32) }), "PAC-MAN"),
    state(GameState::Menu),
    scoreText(font),
    infoText(font)
{
    window.setFramerateLimit(60);
    init();
}

void Game::init() {
    if (!font.openFromFile("AniMe Vision - MB_EN Regular.ttf")) {
    }

    scoreText.setFont(font);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setCharacterSize(24);
    scoreText.setPosition(sf::Vector2f(10, 10));

    infoText.setFont(font);
    infoText.setFillColor(sf::Color::Yellow);
    infoText.setCharacterSize(24);

    reset();
}

void Game::reset() {
    player = std::make_unique<Player>(9, 9, tileSize);
    map = std::make_unique<Map>(tileSize);
    ghosts.clear();
    ghosts.push_back(std::make_unique<Ghost>(9, 5, tileSize, sf::Color::Red));
    ghosts.push_back(std::make_unique<Ghost>(10, 5, tileSize, sf::Color::Cyan)); 
}

void Game::handleInput() {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
    }

    if (state == GameState::Menu || state == GameState::GameOver) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
            if (state == GameState::GameOver) reset();
            state = GameState::Playing;
        }
    }
}

void Game::update() {
    if (state != GameState::Playing) return;

    for (auto& ghost : ghosts) {
        ghost->update(*map);
        if (player->getX() == ghost->getX() && player->getY() == ghost->getY()) {
            state = GameState::GameOver;
        }
    }

    if (map->getDotCount() == 0) {
        int currentScore = player->getScore();
        reset();
        player->setScore(currentScore);
    }

    int dx = 0, dy = 0;
    if (moveClock.getElapsedTime().asSeconds() > 0.15f) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) dx = -1;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) dx = 1;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) dy = -1;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) dy = 1;

        if (dx != 0 || dy != 0) {
            if (!map->isWall(player->getX() + dx, player->getY() + dy)) {
                player->move(dx, dy);
                player->addScore(map->tryEatDot(player->getX(), player->getY()));
            }
            moveClock.restart();
        }
    }

    for (auto& ghost : ghosts) {
        if (player->getX() == ghost->getX() && player->getY() == ghost->getY()) {
            state = GameState::GameOver;
        }
    }

    scoreText.setString("Score: " + std::to_string(player->getScore()));
}

void Game::render() {
    window.clear();
    map->draw(window);
    player->draw(window);
    for (auto& ghost : ghosts) ghost->draw(window);

    if (state == GameState::Menu) {
        infoText.setString(">> Press ENTER to start <<");
        sf::FloatRect textRect = infoText.getLocalBounds();
        infoText.setOrigin(textRect.getCenter());
        infoText.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f));
        
        if (blinkClock.getElapsedTime().asSeconds() < 1.0f) {
            window.draw(infoText);
        } else if (blinkClock.getElapsedTime().asSeconds() > 1.5f) {
            blinkClock.restart();
        }
    } 
    else if (state == GameState::GameOver) {
        infoText.setString("GAME OVER! Press ENTER to restart");
        infoText.setFillColor(sf::Color::Red);
        sf::FloatRect textRect = infoText.getLocalBounds();
        infoText.setOrigin(textRect.getCenter());
        infoText.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f));
        window.draw(infoText);
    } 
    else {
        window.draw(scoreText);
    }

    window.display();
}

void Game::run() {
    while (window.isOpen()) {
        handleInput();
        update();
        render();
    }
}
