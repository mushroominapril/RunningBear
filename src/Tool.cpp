#include "Tool.h"
#include <chrono>

std::mt19937 Tool::gen(std::chrono::steady_clock::now().time_since_epoch().count());

bool Tool::checkCollision(const sf::FloatRect& a, const sf::FloatRect& b) {
    return !(a.position.x + a.size.x < b.position.x ||
        b.position.x + b.size.x < a.position.x ||
        a.position.y + a.size.y < b.position.y ||
        b.position.y + b.size.y < a.position.y);
}

int Tool::getRandomInt(int min, int max) {
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

float Tool::getRandomFloat(float min, float max) {
    std::uniform_real_distribution<float> dis(min, max);
    return dis(gen);
}