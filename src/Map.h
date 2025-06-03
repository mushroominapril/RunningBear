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

	//void update(float time);

	void setFollowFactor(float factor);
	float getFollowFactor() const;
};

//class Map {
//public:
//    Map(const std::string& texturePath1, const std::string& texturePath2, float scrollSpeed);
//    void draw(sf::RenderWindow& window) const;
//    void update(float time);
//    void setScrollSpeed(float speed);
//    float getScrollSpeed() const;
//
//private:
//    std::vector<sf::Sprite> sprites;  // 存储两个背景精灵
//    sf::Texture texture1, texture2;
//    float scrollSpeed;  // 滚动速度（像素/秒）
//};