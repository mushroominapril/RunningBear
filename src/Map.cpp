#include "Map.h"
#include<SFML/Graphics.hpp>
#include "Bear.h"
Map::Map(const std::string texturePath, float speed):m_texture(texturePath),sprite(m_texture),moveSpeed(speed){
	if (!m_texture.loadFromFile(texturePath)) {
		throw std::runtime_error("Failed to load background texture: " + texturePath);
	}
   sprite.setTexture(m_texture);
   resetPosition();
}

void Map::draw(sf::RenderWindow& window) const
{
    // 主背景
    window.draw(sprite);
    float posX = sprite.getPosition().x;
    float textureWidth = sprite.getGlobalBounds().size.x;

    // 如果背景图的左侧已经完全移出屏幕，绘制第二个背景图
    if (posX < 0) // 如果背景图的左边移出了屏幕
    {
        // 创建第二个背景图并放置在第一个背景图的右边
        sf::Sprite secondSprite = sprite;
        secondSprite.setPosition({ posX + textureWidth, sprite.getPosition().y });
        window.draw(secondSprite);
    }
}

void Map::setmoveSpeed(float speed)
{
    moveSpeed = speed;
}

float Map::getmoveSpeed() const
{
    return moveSpeed;
}

void Map::resetPosition()
{
	sprite.setPosition({1,-200});
}

void Map::update(float time){
    float offset = moveSpeed * time;

    // 获取当前背景图的位置
    sf::Vector2f currentPos = sprite.getPosition();
    sf::Vector2f newPos(currentPos.x - offset, currentPos.y);

    // 获取背景图尺寸
    sf::FloatRect bounds = sprite.getGlobalBounds();
    float textureWidth = bounds.size.x;

    const float screenWidth = 600.0f; // 假设屏幕宽度是600

     if (newPos.x <= -textureWidth) {
        newPos.x += textureWidth;  // 将位置重置到另一边
    }

    // 更新背景图位置
    sprite.setPosition(newPos);
}


