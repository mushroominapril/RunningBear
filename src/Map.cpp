#include "Map.h"
#include<SFML/Graphics.hpp>
#include "Bear.h"
Map::Map(const std::string texturePath, float flowFactor):m_texture(texturePath),sprite(m_texture),followFactor(flowFactor){
	if (!m_texture.loadFromFile(texturePath)) {
		throw std::runtime_error("Failed to load background texture: " + texturePath);
	}
   sprite.setTexture(m_texture);
}

void Map::draw(sf::RenderWindow& window) const
{
	window.draw(sprite);
}

void Map::update(const sf::Vector2f& targetPosition,float time)
{
	sf::Vector2f targetOffset(
		-targetPosition.x *followFactor,
		-targetPosition.y *followFactor
	);

	// 平滑过渡（可选）
	sf::Vector2f currentPos = sprite.getPosition();
	sf::Vector2f newPos = currentPos + (targetOffset - currentPos) * 10.f * time;
    sprite.setPosition(newPos);
}

void Map::setFollowFactor(float factor)
{
	followFactor = std::clamp(factor, 0.f, 1.f);//clamp函数将数值限定在指定范围内，防止穿帮
}

float Map::getFollowFactor() const
{
	return followFactor;
}





