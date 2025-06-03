#pragma once
#include<SFML/Graphics.hpp>
#include<array>

class Map 
{
private:
	sf::Texture m_texture;
	sf::Sprite sprite;
	float moveSpeed;//像素移动
	float screenWidth;
public:
    Map(const std::string texturePath,float flowFactor);
	void draw(sf::RenderWindow& window) const;
	void update(float time);
	void setmoveSpeed(float speed);
	float getmoveSpeed() const;
	void resetPosition();//获取初始速度
};