#pragma once
#include <string>
#include<SFML/Graphics.hpp>
#include <iostream>
class Glod {
public:
	Glod(const std::string &texturePath,const sf::Vector2f &position);
	void draw(sf::RenderWindow& window);
	sf::Vector2f getPosition() const;

	void disapper();
	 void generate(std::vector<Glod>& glods);
private:
	sf::Sprite sprite;
	sf::Texture texture;
};