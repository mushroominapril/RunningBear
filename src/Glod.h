#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#define GLOD_H
class Glod {
public:
    Glod(sf::Texture& texture, float posX, float posY, float targetWidth);

    void update(float deltaTime, float speed);
    void draw(sf::RenderWindow& window);
    bool isOffScreen() const;
    sf::FloatRect getBounds() const;
    void collect();
    bool isCollected() const;

private:
    void updateAnimation(float deltaTime);

    sf::Sprite sprite;
    float animationTime;
    bool collected;
    float floatOffset;  // 每个金币独特的浮动偏移量
};


