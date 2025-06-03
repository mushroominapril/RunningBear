#include "Map.h"
#include<SFML/Graphics.hpp>
#include "Bear.h"
Map::Map(const std::string texturePath, float flowFactor):m_texture(texturePath),sprite(m_texture),followFactor(flowFactor){
	if (!m_texture.loadFromFile(texturePath)) {
		throw std::runtime_error("Failed to load background texture: " + texturePath);
	}
   sprite.setTexture(m_texture);
}

void Map::draw(sf::RenderWindow& window) const
{
	window.draw(sprite);
}

void Map::update(const sf::Vector2f& targetPosition,float time)
{
	sf::Vector2f targetOffset(
		-targetPosition.x *followFactor,
		-targetPosition.y *followFactor
	);

	// 平滑过渡（可选）
	sf::Vector2f currentPos = sprite.getPosition();
	sf::Vector2f newPos = currentPos + (targetOffset - currentPos) * 10.f * time;
    sprite.setPosition(newPos);
}
//void Map::update(float time)
//{
//    // 定义向左移动的速度（像素/秒）
//    const float moveSpeed = 200.0f; // 可以根据需要调整这个值
//
//    // 计算这一帧应该移动的距离
//    float offset = -moveSpeed * time; // 负值表示向左移动
//
//    // 更新精灵位置
//    sf::Vector2f currentPos = sprite.getPosition();
//    sf::Vector2f newPos(currentPos.x + offset, currentPos.y);
//    sprite.setPosition(newPos);
//}

void Map::setFollowFactor(float factor)
{
	followFactor = std::clamp(factor, 0.f, 1.f);//clamp函数将数值限定在指定范围内，防止穿帮
}

float Map::getFollowFactor() const
{
	return followFactor;
}


//Map::Map(const std::string& texturePath1, const std::string& texturePath2, float scrollSpeed)
//    : scrollSpeed(scrollSpeed) {
//    // 加载两张纹理
//    if (!texture1.loadFromFile(texturePath1) || !texture2.loadFromFile(texturePath2)) {
//        throw std::runtime_error("Failed to load background textures");
//    }
//
//    // 创建两个精灵
//    sf::Sprite sprite1(texture1);
//    sf::Sprite sprite2(texture2);
//
//    // 将第二个精灵放在第一个的右侧
//    sprite1.setPosition({ 0, 0 });
//    sprite2.setPosition({sprite1.getGlobalBounds().position.x, 0});
//
//    sprites.push_back(sprite1);
//    sprites.push_back(sprite2);
//}
//
//void Map::draw(sf::RenderWindow& window) const {
//    for (const auto& sprite : sprites) {
//        window.draw(sprite);
//    }
//}
//
//void Map::update(float time) {
//    float offset = -scrollSpeed * time; // 向左移动
//
//    for (auto& sprite : sprites) {
//        // 移动每个精灵
//        sprite.move({ offset, 0 });
//
//        // 检查精灵是否完全移出屏幕左侧
//        sf::FloatRect bounds = sprite.getGlobalBounds();
//        if (bounds.position.x + bounds.position.y < 0) {
//            // 将这个精灵移动到另一个精灵的右侧
//            float newX = sprites[0].getGlobalBounds().position.x + sprites[0].getGlobalBounds().position.y;
//            sprite.setPosition({newX, 0});
//        }
//
//        // 确保sprites[0]始终是左边的那个
//        if (sprites[0].getPosition().x > sprites[1].getPosition().x) {
//            std::swap(sprites[0], sprites[1]);
//        }
//    }
//}
//
//void Map::setScrollSpeed(float speed) {
//    scrollSpeed = speed;
//}
//
//float Map::getScrollSpeed() const {
//    return scrollSpeed;
//}
//


