#pragma once
#include<SFML/Graphics.hpp>
#include<array>
class Map 
{
private:
	sf::Texture m_texture1,m_texture2;
	sf::Sprite sprite1, sprite2;
	sf::Vector2f windowsize;//Vector2f是一个二维向量类
	float scrollspread = 0.5f;
	float offset = 0.5f;

public:
    Map(const std::string texturePath, const std::string texturePath1,const sf::Vector2f& startPosition);
	void draw(sf::RenderWindow& window) const;
	void update(float time, const sf::Vector2f& cameraMovement);
	void setScrollSpread(float scrollspead);
	void setReapeting(bool repeat);

};