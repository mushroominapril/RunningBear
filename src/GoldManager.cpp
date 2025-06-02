#pragma once
#include"GoldManager.h"
#include "tool.h"
GoldManager::GoldManager()
    : spawnTimer(0), nextSpawnTime(0), minSpawnTime(0.5f), maxSpawnTime(2.0f),
    lastGoldX(0), minGoldDistance(200.0f) {
    nextSpawnTime = getRandomSpawnTime();
}

bool GoldManager::loadTexture() {
    if (!goldTexture.loadFromFile("glod.png")) {
        std::cerr << "无法加载金币纹理" << std::endl;
        return false;
    }
    return true;
}

void GoldManager::update(float deltaTime, float speed, float groundY, float targetWidth) {
    spawnTimer += deltaTime;

    if (spawnTimer >= nextSpawnTime &&
        (golds.empty() || 800.0f - lastGoldX >= minGoldDistance)) {
        spawnGoldGroup(groundY, targetWidth);
        spawnTimer = 0;
        nextSpawnTime = getRandomSpawnTime();
    }

    for (auto& gold : golds) {
        gold->update(deltaTime, speed);
    }

    golds.erase(
        std::remove_if(golds.begin(), golds.end(),
            [](const std::unique_ptr<Glod>& g) { return g->isOffScreen() || g->isCollected(); }),
        golds.end()
    );
}

//void GoldManager::spawnGold(float groundY, float targetWidth) {
//    float posY = groundY - Tool::getRandomFloat(50.0f, 150.0f); // 金币在离地面一定高度生成
//    auto gold = std::make_unique<Glod>(goldTexture, 800.0f, posY, targetWidth / 3.0f); // 金币宽度是障碍物的1/3
//
//    golds.push_back(std::move(gold));
//    lastGoldX = 800.0f;
//}
void GoldManager::spawnGoldGroup(float groundY, float targetWidth) {
    const int goldCount = 10; // 一次生成5个金币
    const float spacing = 80.0f; // 金币之间的间距

    float baseY = groundY - Tool::getRandomFloat(100.0f, 200.0f);
    float startX = 800.0f;

    //更新逻辑可以尝试修改
    for (int i = 0; i < goldCount; ++i) {
        // 计算每个金币的位置，形成弧形排列
        float posX = startX + i * spacing;
        float posY = baseY + std::sin(i * 0.6f) * 40.0f; // 正弦波排列

        auto gold = std::make_unique<Glod>(goldTexture, posX, posY, targetWidth*2.0F / 3.0f);
        golds.push_back(std::move(gold));
    }

    lastGoldX = startX + (goldCount - 1) * spacing;
}

int GoldManager::checkCollection(const sf::FloatRect& playerBounds) {
    int collectedCount = 0;
    for (auto& gold : golds) {
        if (!gold->isCollected() && Tool::checkCollision(playerBounds, gold->getBounds())) {
            gold->collect();
            collectedCount++;
        }
    }
    return collectedCount;
}

void GoldManager::draw(sf::RenderWindow& window) {
    for (const auto& gold : golds) {
        gold->draw(window);
    }
}

void GoldManager::reset() {
    golds.clear();
    spawnTimer = 0;
    nextSpawnTime = getRandomSpawnTime();
    lastGoldX = 0;
}

float GoldManager::getRandomSpawnTime() const {
    return Tool::getRandomFloat(minSpawnTime, maxSpawnTime);
}

void GoldManager::increaseDifficulty(float gameTime) {
    minSpawnTime = std::max(0.3f, 0.5f - gameTime / 120.0f);
    maxSpawnTime = std::max(0.8f, 2.0f - gameTime / 60.0f);
    minGoldDistance = std::max(100.0f, 200.0f - gameTime / 3.0f);
}