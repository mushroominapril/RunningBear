#pragma once
#include"Glod.h"
#include "Tool.h"
#include <random>
#include <iostream>
class GoldManager {
public:
    GoldManager();

    bool loadTexture();
    void update(float deltaTime, float speed, float groundY, float targetWidth);
    int checkCollection(const sf::FloatRect& playerBounds);
    void draw(sf::RenderWindow& window);
    void reset();
    void increaseDifficulty(float gameTime);

private:
    void spawnGoldGroup(float groundY, float targetWidth);  // 修改为生成一组金币
    float getRandomSpawnTime() const;

    sf::Texture goldTexture;
    std::vector<std::unique_ptr<Glod>> golds;
    float spawnTimer;
    float nextSpawnTime;
    float minSpawnTime;
    float maxSpawnTime;
    float lastGoldX;
    float minGoldDistance;
};
