#pragma once
#include <SFML/Graphics.hpp>
#include <random>

namespace Tool {
    extern std::mt19937 gen;
  /*  bool checkCollision(const sf::FloatRect& a, const sf::FloatRect& b);*/

    bool checkPixelCollision( const sf::Sprite& sprite1, const  sf::Sprite& sprite2);

    int getRandomInt(int min, int max);
    float getRandomFloat(float min, float max);
}