#include "Bear.h"
#include<iostream>
#include<fstream>
Bear::Bear(const std::string& texturePath, const std::string& texturePath1, const std::string& texturePath2,
    const std::string& texturePath3,const std::string& texturePath4,
    const sf::Vector2f& startPosition):texture(texturePath), sprite(texture),
	moveSpeed(0.f),verticalVelocity(0.f),isOnGround(false)//Sprite不存在无参的构造函数
{
    if (!texture.loadFromFile(texturePath) ||
        ! texture1.loadFromFile(texturePath1) ||
        !texture2.loadFromFile(texturePath2) ||
        !texture3.loadFromFile(texturePath3) ||
        !texture4.loadFromFile(texturePath4))
    {
        std::cerr << "Failed to load player textures!" << std::endl;
    }
    textures.push_back(&texture);
    textures.push_back(&texture1);
    textures.push_back(&texture2);
    textures.push_back(&texture3);
    textures.push_back(&texture4);
	sprite.setPosition(startPosition);
    sprite.setTexture(*textures[currentTextureIndex]);
    textureSwithTime = 0.3f;
    pastTime = 0.0f;
}
//控制移动的函数
void Bear::update(float time)
{
    pastTime += time;
    if (pastTime >= textureSwithTime) {
        currentTextureIndex = (currentTextureIndex + 1) % textures.size();
        sprite.setTexture(*textures[currentTextureIndex]);
        pastTime = 0.0f;
    }

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
    if(!isOnGround) {
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

sf::FloatRect Bear::getBounds() const {
    return sprite.getGlobalBounds();
}

float Bear::getSpeed() const
{
    return moveSpeed;
}

void Bear::reset(const sf::Vector2f& position) {
    this->position = position;
    sprite.setPosition(position);
}