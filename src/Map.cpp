#include "Map.h"
#include<SFML/Graphics.hpp>
Map::Map(const std::string texturePath, const std::string texturePath1, const sf::Vector2f& startPosition) :
	m_texture1(texturePath), windowsize(startPosition), m_texture2(texturePath1), sprite1(m_texture1),
	sprite2(m_texture2) {

}

void Map::draw(sf::RenderWindow& window) const
{
	window.draw(sprite1);
	window.draw(sprite2);
}

void Map::update(float time, const sf::Vector2f& cameraMovement)
{
	offset = scrollspread * time;
	if (offset >= windowsize.x) {
		offset = 0;
	}
	sprite1.setPosition({ -offset, 0 });
	sprite2.setPosition({ windowsize.x - offset,0 });
}

void Map::setScrollSpread(float scrollspead)
{
	this->scrollspread = scrollspead;
}

void Map::setReapeting(bool repeat)
{
	m_texture1.setRepeated(repeat);
}

