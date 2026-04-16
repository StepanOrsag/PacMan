#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "Player.hpp"
#include "Map.hpp"
#include "Ghost.hpp"

enum class GameState {
    Menu,
    Playing,
    GameOver
};

class Game {
private:
    sf::RenderWindow window;
    const float tileSize = 32.0f;
    
    std::unique_ptr<Player> player;
    std::unique_ptr<Map> map;
    std::vector<std::unique_ptr<Ghost>> ghosts;
    
    GameState state;
    sf::Font font;
    sf::Text scoreText;
    sf::Text infoText;
    
    sf::Clock moveClock;
    sf::Clock blinkClock;

    void init();
    void reset();
    void handleInput();
    void update();
    void render();

public:
    Game();
    void run();
};
