#include "Tool.h"
#include <chrono>
#include <iostream>

std::mt19937 Tool::gen(std::chrono::steady_clock::now().time_since_epoch().count());

//bool Tool::checkCollision(const sf::FloatRect& a, const sf::FloatRect& b) {
//    return !(a.position.x + a.size.x < b.position.x ||
//        b.position.x + b.size.x < a.position.x ||
//        a.position.y + a.size.y < b.position.y ||
//        b.position.y + b.size.y < a.position.y);
//}


bool Tool::checkPixelCollision(const sf::Sprite& sprite1, const sf::Sprite& sprite2)
{
	const sf::Texture texture1 = sprite1.getTexture();
	const sf::Texture texture2 = sprite2.getTexture();
	sf::Image img1 = texture1.copyToImage();
	sf::Image img2 = texture2.copyToImage();

	sf::FloatRect bound1 = sprite1.getGlobalBounds();
	sf::FloatRect bound2 = sprite2.getGlobalBounds();
	if (!bound1.findIntersection(bound2)) {
		return false;
	}

	sf::IntRect overlap;
	overlap.position.x = static_cast<int>(std::max(bound1.position.x, bound2.position.x));
	overlap.position.y = static_cast<int>(std::max(bound1.position.y, bound2.position.y));
	overlap.size.x = static_cast<int>(std::min(bound1.position.x + bound1.size.x, bound2.position.x + bound2.size.x)) - overlap.position.x;
	overlap.size.y = static_cast<int>(std::min(bound1.position.y + bound1.size.y, bound2.position.y + bound2.size.y)) - overlap.size.y;
	/*   std::cout << "Overlap: (" << overlap.position.x<< ", " << overlap.size.y << ") - ("
		   << overlap.position.x + overlap.position.y << ", " << overlap.size.y + overlap.size.y << ")\n"; */
		   // 检查重叠区域的像素
	for (int x = 0; x < overlap.size.x; ++x) {
		for (int y = 0; y < overlap.size.y; ++y) {
			// 全局坐标转局部纹理坐标（修正后的版本）
			sf::Vector2f globalPos(overlap.position.x + x, overlap.position.y + y);
			sf::Vector2f localPos1 = sprite1.getInverseTransform().transformPoint(globalPos);
			sf::Vector2f localPos2 = sprite2.getInverseTransform().transformPoint(globalPos);
			sf::Vector2f pos1(overlap.position.x + x - bound1.position.x, overlap.position.y + y - bound1.position.y);
			sf::Vector2f pos2(overlap.position.x + x - bound2.position.x, overlap.position.y + y - bound2.position.y);
			//// 检查坐标是否在纹理范围内
			//if (pos1.x >= img1.getSize().x || pos1.y >= img1.getSize().y ||
			//    pos2.x >= img2.getSize().x || pos2.y >= img2.getSize().y) {
			//    continue; // 跳过越界坐标
			//}
			//if (img1.getPixel({ static_cast<unsigned int>(pos1.x), static_cast<unsigned int>(pos1.y) }).a > 0 &&
			//    img2.getPixel({static_cast<unsigned int>(pos2.x), static_cast<unsigned int>(pos2.y)}).a > 0) {
			//    return true; // 两个像素都不透明，发生碰撞
			//}
					 // 检查坐标是否在纹理范围内
			if (localPos1.x < 0 || localPos1.y < 0 || localPos1.x >= img1.getSize().x || localPos1.y >= img1.getSize().y ||
				localPos2.x < 0 || localPos2.y < 0 || localPos2.x >= img2.getSize().x || localPos2.y >= img2.getSize().y) {
				continue; // 跳过越界坐标
			}

			// 检查像素是否不透明（Alpha > 0）
			if (img1.getPixel({ static_cast<unsigned int>(localPos1.x), static_cast<unsigned int>(localPos1.y) }).a > 0 &&
				img2.getPixel({ static_cast<unsigned int>(localPos2.x), static_cast<unsigned int>(localPos2.y) }).a > 0) {
				return true; // 发生碰撞
			}
		}
	}
	return false;
}

int Tool::getRandomInt(int min, int max) {
	if (min > max) {
		std::swap(min, max);
	}
	std::uniform_int_distribution<> dis(min, max);
	return dis(gen);
}

float Tool::getRandomFloat(float min, float max) {
	if (min > max) {
		std::swap(min, max);
	}
	if (min < 0 && max > min + std::numeric_limits<float>::max()) {
		max = min + std::numeric_limits<float>::max();
	}

	std::uniform_real_distribution<float> dis(min, max);
	return dis(gen);
}