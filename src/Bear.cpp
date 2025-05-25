#include "Bear.h"
#include<iostream>
#include<fstream>
Bear::Bear(const std::string& texturePath, const sf::Vector2f& startPosition):texture(texturePath),sprite(texture),
	moveSpeed(0.f),verticalVelocity(0.f),isOnGround(false)//Sprite不存在无参的构造函数
{
	if (!texture.loadFromFile(texturePath)) {
		std::cerr << "Failed to load texture: " << texturePath << std::endl;
		throw std::runtime_error("Failed to load texture");
	} 
	sprite.setPosition(startPosition);
}
//控制移动的函数
void Bear::update(float time)
{
    // 水平输入
    float direction = 0.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) direction -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) direction += 1.f;

    // 地面移动
    if (isOnGround) {
        moveSpeed += direction * acceleration * time;
        moveSpeed = std::max(-maxSpeed, std::min(moveSpeed, maxSpeed));
    }
    // 空中控制
    else {
        moveSpeed += direction * acceleration * airControl * time;
    }

    // 自然减速
    if (direction == 0 && isOnGround) {
        if (moveSpeed > 0) moveSpeed = std::max(0.f, moveSpeed - deceleration * time);
        if (moveSpeed < 0) moveSpeed = std::min(0.f, moveSpeed + deceleration * time);
    }

    // 跳跃
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && isOnGround) {
        verticalVelocity = jumpSpeed;
        isOnGround = false;
    }

    // 重力
    verticalVelocity += gravity * time;
    sprite.move({ moveSpeed * time, verticalVelocity * time });

    // 地面检测
    if (sprite.getPosition().y >= 450.f) {
        sprite.setPosition({ sprite.getPosition().x, 450.f });
        verticalVelocity = 0;
        isOnGround = true;
    }
    // 边界检测
    sf::FloatRect bounds =sprite.getGlobalBounds();//获取边界框
    if (bounds.position.x < 0) {
        sprite.setPosition({ 800.f,sprite.getPosition().y });
    }
    if (bounds.position.x > 800.f) {
        sprite.setPosition({ 0.f,sprite.getPosition().y });
    }
}

void Bear::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

void Bear::setPosition(const sf::Vector2f& position)
{
    sprite.setPosition(position);
}

sf::Vector2f Bear::getPosition() const
{
    return sprite.getPosition();
}

