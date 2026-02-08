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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
			dx = -1;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
			dx = 1;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
			dy = -1;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
			dy = 1;
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