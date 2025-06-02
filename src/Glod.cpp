#pragma once
#include "Glod.h"
#include "Tool.h"
#include <random>
#include <iostream>

// Glod 类实现
Glod::Glod(sf::Texture& texture, float posX, float posY, float targetWidth)
    : sprite(texture), animationTime(0.0f), collected(false) {
    auto size = sprite.getTexture().getSize();
    float scale = targetWidth*2.0f/ size.x;
    sprite.setScale({ scale,scale });
    sprite.setPosition({ posX, posY });
    sprite.setOrigin({ size.x / 2.0f, size.y / 2.0f }); // 设置原点为中心，便于旋转

     // 为每个金币设置独特的浮动偏移量
    floatOffset = Tool::getRandomFloat(0.0f, 3.14f); // 0到π之间的随机值
}


bool Glod::isOffScreen() const {
    auto size = sprite.getTexture().getSize();
    return sprite.getPosition().x < -static_cast<float>(size.x);
}

sf::FloatRect Glod::getBounds() const {
    return sprite.getGlobalBounds();
}

void Glod::draw(sf::RenderWindow& window) {
    if (!collected) {
        window.draw(sprite);
    }
}
void Glod::update(float deltaTime, float speed) {
    if (!collected) {
        sprite.move({ -speed * deltaTime, 0 });
        updateAnimation(deltaTime);
    }
}

void Glod::collect() {
    collected = true;
}

bool Glod::isCollected() const {
    return collected;
}

void Glod::updateAnimation(float deltaTime) {
    animationTime += deltaTime;

    // 上下浮动效果 - 每个金币有独特的浮动相位
    float offsetY = std::sin(animationTime * 5.0f + floatOffset) * 10.0f;
    auto pos = sprite.getPosition();
    sprite.setPosition({ pos.x, pos.y + offsetY * deltaTime * 60.0f });

    // 缩放效果
    //float scale = 1.0f + std::sin(animationTime * 3.0f + floatOffset) * 0.2f;
    //sprite.setScale({ scale, scale });
    

    // 缩放效果 - 带上下限控制
    float minScale = 1.0f;  // 最小缩放比例
    float maxScale = 1.5f;  // 最大缩放比例
    float scale = std::clamp(1.0f + std::sin(animationTime * 3.0f + floatOffset) * 0.2f, minScale, maxScale);
    sprite.setScale({ scale, scale });
}


