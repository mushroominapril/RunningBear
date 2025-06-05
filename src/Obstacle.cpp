#include "Obstacle.h"
#include "Tool.h"
#include <random>
#include <iostream>

// Obstacle 

Obstacle::Obstacle(sf::Texture& texture, float posX, float posY)
	: sprite(texture), animationTime(0.0f), animationSpeed(0.0f) {
	originalScale = { 1.0f, 1.0f };
}

void Obstacle::setCollisionBoundsPadding(float paddingX, float paddingY) {
	sf::FloatRect bounds = sprite.getGlobalBounds();
	collisionBounds = sf::FloatRect(
		{ bounds.position.x + paddingX / 2.f,bounds.position.y + paddingY / 2.f },
		{ bounds.size.x - paddingX,bounds.size.y - paddingY }
	);
}

void Obstacle::update(float deltaTime, float speed) {
	sprite.move({ -speed * deltaTime, 0 });
	updateAnimation(deltaTime);
}

bool Obstacle::isOffScreen() const {
	auto size = sprite.getTexture().getSize();
	return sprite.getPosition().x < -static_cast<float>(size.x);
}

sf::FloatRect Obstacle::getBounds() const {
	// 计算当前位置与初始位置的偏移
	sf::Vector2f currentPos = sprite.getPosition();
	sf::Vector2f offset = currentPos - initialPosition;

	// 应用偏移到碰撞边界
	sf::FloatRect bounds = collisionBounds;
	bounds.position.x += offset.x;
	bounds.position.y += offset.y;

	return bounds;
}

void Obstacle::draw(sf::RenderWindow& window) {
	window.draw(sprite);
}

void Obstacle::initializePositionAndBounds(float posX, float posY) {
	sprite.setScale(originalScale);

	// 计算缩放后的高度
	auto size = sprite.getTexture().getSize();
	float scaledHeight = size.y * originalScale.y;

	// 设置位置，确保障碍物底部精确对齐地面
	sprite.setPosition({ posX, posY});

	// 分析纹理像素数据，找出非透明区域的边界
	calculatePreciseCollisionBounds();
}

// 新增方法：分析纹理像素数据，计算精确碰撞边界
void Obstacle::calculatePreciseCollisionBounds() {
	// 简化碰撞边界计算，使用更保守的边界
	sf::FloatRect bounds = sprite.getGlobalBounds();
	float padding = 0.2f; // 20%的内边距，可以根据需要调整

	float paddingX = bounds.size.x * padding;
	float paddingY = bounds.size.y * padding;

	collisionBounds = sf::FloatRect(
		{ bounds.position.x + paddingX, bounds.position.y + paddingY },
		{ bounds.size.x - 2 * paddingX, bounds.size.y - 2 * paddingY }
	);

	// 保存初始位置用于后续偏移计算
	initialPosition = sprite.getPosition();
}

void Obstacle::drawDebug(sf::RenderWindow& window) {
	// 绘制精灵边界
	sf::RectangleShape spriteBound;
	sf::FloatRect bounds = sprite.getGlobalBounds();
	spriteBound.setPosition({ bounds.position.x, bounds.position.y });
	spriteBound.setSize({ bounds.size.x, bounds.size.y });
	spriteBound.setFillColor(sf::Color(0, 255, 0, 50)); // 半透明绿色
	spriteBound.setOutlineColor(sf::Color::Green);
	spriteBound.setOutlineThickness(1.0f);
	window.draw(spriteBound);

	// 绘制碰撞边界
	sf::RectangleShape collisionBound;
	sf::FloatRect cBounds = getBounds();
	collisionBound.setPosition({ cBounds.position.x, cBounds.position.y });
	collisionBound.setSize({ cBounds.size.x, cBounds.size.y });
	collisionBound.setFillColor(sf::Color(255, 0, 0, 50)); // 半透明红色
	collisionBound.setOutlineColor(sf::Color::Red);
	collisionBound.setOutlineThickness(1.0f);
	window.draw(collisionBound);
}

void ObstacleManager::drawDebug(sf::RenderWindow& window) {
	for (const auto& obstacle : obstacles) {
		obstacle->drawDebug(window);
	}
}


// ============ SmallBlock ============
SmallBlock::SmallBlock(sf::Texture& texture, float posX, float posY)
	: Obstacle(texture, posX, posY) {
	originalScale = { 0.3f, 0.3f };
	animationSpeed = 0.0f;
	initializePositionAndBounds(posX, posY);
}

void SmallBlock::updateAnimation(float deltaTime) {
	//if (animationSpeed <= 0.0f) return;
	//animationTime += deltaTime;
	//float scaleOffset = std::sin(animationTime * animationSpeed) * 0.05f;
	//sprite.setScale({
	//	originalScale.x * (1.0f + scaleOffset),
	//	originalScale.y * (1.0f + scaleOffset)
	//	});
}

// ============ BigBlock ============
BigBlock::BigBlock(sf::Texture& texture, float posX, float posY)
	: Obstacle(texture, posX, posY) {
	originalScale = { 0.3f, 0.3f };
	animationSpeed = 0.0f;
	initializePositionAndBounds(posX, posY);
}

void BigBlock::updateAnimation(float deltaTime) {
	//if (animationSpeed <= 0.0f) return;
	//animationTime += deltaTime;
	//float scaleOffset = std::cos(animationTime * animationSpeed) * 0.08f;
	//sprite.setScale({
	//	originalScale.x * (1.0f + scaleOffset),
	//	originalScale.y * (1.0f + scaleOffset)
	//	});
	//float angle = std::sin(animationTime * 0.3f) * 1.0f;
	//sprite.setRotation(sf::degrees(angle));
}

// ============ LongBlock ============
LongBlock::LongBlock(sf::Texture& texture, float posX, float posY)
	: Obstacle(texture, posX, posY) {
	originalScale = { 0.3f, 0.3f };
	animationSpeed = 0.0f;
	initializePositionAndBounds(posX, posY);
}

void LongBlock::updateAnimation(float deltaTime) {
	//if (animationSpeed <= 0.0f) return;
	//animationTime += deltaTime;
	//float angle = std::sin(animationTime * animationSpeed) * 2.0f;
	//sprite.setRotation(sf::degrees(angle));
}

// ============ Balloon============
Balloon::Balloon(sf::Texture& texture, float posX, float posY)
	: Obstacle(texture, posX, posY) {
	originalScale = { 0.2f, 0.2f };
	animationSpeed = 2.0f;

	sprite.setScale(originalScale);
	auto size = sprite.getTexture().getSize();
	float scaledHeight = size.y * originalScale.y;

	float maxHeight = posY - 50.0f - scaledHeight;
	float minHeight = 100.0f; // 距离顶部至少100像素
	float balloonY = Tool::getRandomFloat(minHeight, maxHeight);

	sprite.setPosition({ posX, balloonY });

	calculatePreciseCollisionBounds();
}

void Balloon::updateAnimation(float deltaTime) {
	if (animationSpeed <= 0.0f) return;
	animationTime += deltaTime;
	float offset = std::sin(animationTime * animationSpeed * 5.0f) * 10.0f;
	auto pos = sprite.getPosition();
	sprite.setPosition({ pos.x, pos.y + offset * deltaTime * 60.0f });
}

// ObstacleManager 

ObstacleManager::ObstacleManager()
	:spawnTimer(0), nextSpawnTime(0), minSpawnTime(1.0f), maxSpawnTime(3.0f),
	lastObstacleX(0), minObstacleDistance(300.0f) {
	nextSpawnTime = getRandomSpawnTime();
}

bool ObstacleManager::loadTextures() {
	if (!smallBlockTexture.loadFromFile("smallBlock.png")) {
		std::cerr << "" << std::endl;
		return false;
	}
	if (!bigBlockTexture.loadFromFile("bigBlock.png")) {
		std::cerr << "" << std::endl;
		return false;
	}
	if (!longBlockTexture.loadFromFile("longBlock.png")) {
		std::cerr << " " << std::endl;
		return false;
	}
	if (!balloonTexture.loadFromFile("balloon.png")) {
		std::cerr << "" << std::endl;
		return false;
	}
	return true;
}

void ObstacleManager::update(float deltaTime, float speed) {
	spawnTimer += deltaTime;

	if (spawnTimer >= nextSpawnTime &&
		(obstacles.empty() || 800.0f - lastObstacleX >= minObstacleDistance)) {
		spawnObstacle(450.0f);
		spawnTimer = 0;
		nextSpawnTime = getRandomSpawnTime();
	}

	for (auto& obstacle : obstacles) {
		obstacle->update(deltaTime, speed);
	}

	obstacles.erase(
		std::remove_if(obstacles.begin(), obstacles.end(),
			[](const std::unique_ptr<Obstacle>& o) { return o->isOffScreen(); }),
		obstacles.end()
	);
}


void ObstacleManager::spawnObstacle(float groundY) {
	int type = getRandomObstacleType();
	float posY = groundY;
	std::unique_ptr<Obstacle> obstacle;

	switch (type) {
	case 0: // SmallBlock
		obstacle = std::make_unique<SmallBlock>(smallBlockTexture, 800.0f, groundY);
		break;
	case 1: // BigBlock
		obstacle = std::make_unique<BigBlock>(bigBlockTexture, 800.0f, groundY);
		break;
	case 2: // LongBlock
		obstacle = std::make_unique<LongBlock>(longBlockTexture, 800.0f, groundY);
		break;
	case 3: // Balloon
		posY = Tool::getRandomFloat(groundY - 200.0f, groundY - 100.0f);
		obstacle = std::make_unique<Balloon>(balloonTexture, 800.0f, posY);
		break;
	}

	obstacles.push_back(std::move(obstacle));
	lastObstacleX = 800.0f;
}

int ObstacleManager::getRandomObstacleType() const {
	return Tool::getRandomInt(0, 3);
}

//bool ObstacleManager::checkCollision(const sf::FloatRect& playerBounds) {
//	for (const auto& obstacle : obstacles) {
//		if (Tool::checkCollision(obstacle, obstaz) {
//			return true;
//		}
//	}
//	return false;
//}
bool ObstacleManager::checkCollision(const sf::Sprite& playerSprite)
{
	for (const auto& obstacle : obstacles) {
		if (Tool::checkPixelCollision(playerSprite, obstacle->getSprite())) {
			return true;
		}
	}
	return false;
}


void ObstacleManager::draw(sf::RenderWindow& window) {
	for (const auto& obstacle : obstacles) {
		obstacle->draw(window);
	}
}

void ObstacleManager::reset() {
	obstacles.clear();
	spawnTimer = 0;
	nextSpawnTime = getRandomSpawnTime();
	minSpawnTime = 1.0f;
	maxSpawnTime = 3.0f;
	lastObstacleX = 0;
}

float ObstacleManager::getRandomSpawnTime() const {
	return Tool::getRandomFloat(minSpawnTime, maxSpawnTime);
}

void ObstacleManager::increaseDifficulty(float gameTime) {
	minSpawnTime = std::max(0.5f, 1.0f - gameTime / 60.0f);
	maxSpawnTime = std::max(1.5f, 3.0f - gameTime / 30.0f);
	minObstacleDistance = std::max(150.0f, 300.0f - gameTime / 2.0f);
}
const sf::Sprite& Obstacle::getSprite() const {
	return sprite;  // �����ϰ���� Sprite
}