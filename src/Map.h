#pragma once
#include<SFML/Graphics.hpp>
#include<array>
class Map 
{
private:
	sf::Texture m_texture;
	sf::Sprite sprite;
	float followFactor;//跟随系数
public:
    Map(const std::string texturePath,float flowFactor);
	void draw(sf::RenderWindow& window) const;
	void update(const sf::Vector2f& targetPosition,float time);
	void setFollowFactor(float factor);
	float getFollowFactor() const;
};