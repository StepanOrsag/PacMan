#include "Map.hpp"
#include "Player.hpp"
#include <string>
#include <SFML/Graphics.hpp>

int main() {
	const float tileSize = 32.0f;
	unsigned int w = static_cast<unsigned int>(20 * tileSize);
	unsigned int h = static_cast<unsigned int>(11 * tileSize);
	sf::RenderWindow window(sf::VideoMode({ w, h }), "PAC-MAN");
	window.setFramerateLimit(60);
	Player player(9, 9, tileSize);
	Map map(tileSize);

	sf::Font font("AniMe Vision - MB_EN Regular.ttf");
	sf::Text scoreText(font, "Score: " + std::to_string(0));
	scoreText.setFillColor(sf::Color::White);
	scoreText.setCharacterSize(24);

	sf::Text pressToPlay(font, ">> Press ENTER to start <<");
	sf::FloatRect textRect = pressToPlay.getLocalBounds();
	pressToPlay.setOrigin(textRect.getCenter());
	pressToPlay.setPosition(sf::Vector2f(w / 2, h / 2));
	
	sf::Clock clock;
	sf::Clock blinkClock;

	while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
		}

		sf::Time elapsedTime = blinkClock.getElapsedTime();
		bool showText = blinkClock.getElapsedTime().asSeconds() < 1;

		if (elapsedTime.asSeconds() > 1.5f) {
			blinkClock.restart();
		}

		window.clear();
		map.draw(window);
		player.draw(window);
		if (showText) {
			window.draw(pressToPlay);
		}
		window.display();

	}
	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
		}
		if (map.getDotCount() == 0) {
			int tempScore = player.getScore();
			player = Player(9, 9, tileSize);
			player.setScore(tempScore);
			map = Map(tileSize);
		}
		int dx = 0;
		int dy = 0;
		sf::Time elapsed = clock.getElapsedTime();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && elapsed.asSeconds() > 0.15) {
			dx = -1;
			clock.restart();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && elapsed.asSeconds() > 0.15) {
			dx = 1;
			clock.restart();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && elapsed.asSeconds() > 0.15) {
			dy = -1;
			clock.restart();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && elapsed.asSeconds() > 0.15) {
			dy = 1;
			clock.restart();
		}
		int futureX = 0;
		int futureY = 0;

		futureX = player.getX() + dx;
		futureY = player.getY() + dy;
		if (dx != 0 || dy != 0) {
			if (!map.isWall(futureX, futureY)) {
				player.move(dx, dy);
				player.addScore(map.tryEatDot(futureX, futureY));
			}
		}

		scoreText.setString("Score: " + std::to_string(player.getScore()));
		window.clear();
		map.draw(window);
		player.draw(window);
		window.draw(scoreText);
		window.display();
	}
	return 0;
}