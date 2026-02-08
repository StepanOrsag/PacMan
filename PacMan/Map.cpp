#include "Map.hpp"
#include <SFML/Graphics.hpp>

Map::Map(float size) : tileSize(size) {
	wallShape.setSize(sf::Vector2f(tileSize, tileSize));
	wallShape.setFillColor(sf::Color::Black);
	wallShape.setOutlineColor(sf::Color::Blue);
	wallShape.setOutlineThickness(2.0f);

	dotShape.setRadius(tileSize / 8);
	dotShape.setFillColor(sf::Color::Magenta);
	dotShape.setOrigin(sf::Vector2(tileSize / 8, tileSize / 8));

	grid = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 1},
		{1, 2, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 2, 1},
		{1, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 1},
		{1, 2, 1, 2, 1, 1, 2, 1, 1, 0, 0, 1, 1, 2, 1, 1, 2, 1, 2, 1},
		{1, 2, 2, 2, 2, 2, 2, 1, 0, 0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 1},
		{1, 2, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 2, 1},
		{1, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 1},
		{1, 2, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 2, 1},
		{1, 2, 2, 2, 2, 1, 2, 2, 2, 0, 2, 2, 2, 2, 1, 2, 2, 2, 2, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};
}

void Map::draw(sf::RenderWindow& window) {
	for (int y = 0; y < grid.size(); y++) {
		for (int x = 0; x < grid[y].size(); x++) {
			if (grid[y][x] == 1) {
				wallShape.setPosition(sf::Vector2f(x * tileSize, y * tileSize));
				window.draw(wallShape);
			}
			else if (grid[y][x] == 2) {
				float offset = tileSize / 2;
				dotShape.setPosition(sf::Vector2f(x * tileSize + offset, y * tileSize + offset));
				window.draw(dotShape);
			}
		}
	}
}

bool Map::isWall(int x, int y) {
	if (y < 0 || y >= grid.size() || x < 0 || x >= grid[0].size()) {
		return true;
	}
	return grid[y][x] == 1;
}

int Map::tryEatDot(int x, int y) {
	if (y < 0 || y >= grid.size() || x < 0 || x >= grid[0].size()) {
		return 0;
	}
	if (grid[y][x] == 2) {
		grid[y][x] = 0;
		return 10;
	}
	return 0;
}

int Map::getDotCount() {
	int count = 0;
	for (int y = 0; y < grid.size(); y++) {
		for (int x = 0; x < grid[y].size(); x++) {
			if (grid[y][x] == 2) {
				count++;
			}
		}
	}
	return count;
}