#pragma once
#include <SFML/Graphics.hpp>
#include <random>

namespace Tool {
    extern std::mt19937 gen;
    bool checkCollision(const sf::FloatRect& a, const sf::FloatRect& b);
    int getRandomInt(int min, int max);
    float getRandomFloat(float min, float max);
}