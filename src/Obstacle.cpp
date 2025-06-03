#include "Obstacle.h"
#include "Tool.h"
#include <random>
#include <iostream>

// Obstacle ����ʵ��

Obstacle::Obstacle(sf::Texture& texture, float posX, float posY, float targetWidth)
	: sprite(texture), animationTime(0.0f), animationSpeed(0.0f) {
	auto size = sprite.getTexture().getSize();
	float scaleX = targetWidth / size.x;
	float scaleY = scaleX;
	sprite.setScale({ scaleX, scaleY });
	float scaledHeight = size.y * scaleY;
	sprite.setPosition({ posX, posY - scaledHeight });
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
	return sprite.getGlobalBounds();
}

void Obstacle::draw(sf::RenderWindow& window) {
	window.draw(sprite);
}


// ============ SmallBlockʵ�� ============
SmallBlock::SmallBlock(sf::Texture& texture, float posX, float posY, float targetWidth)
	: Obstacle(texture, posX, posY, targetWidth) {
	animationSpeed = 1.2f;
}

void SmallBlock::updateAnimation(float deltaTime) {
	if (animationSpeed <= 0.0f) return;
	animationTime += deltaTime;
	float scaleOffset = std::sin(animationTime * animationSpeed) * 0.05f;
	sprite.setScale({ 1.0f + scaleOffset, 1.0f + scaleOffset });
}

// ============ BigBlockʵ�� ============
BigBlock::BigBlock(sf::Texture& texture, float posX, float posY, float targetWidth)
	: Obstacle(texture, posX, posY, targetWidth) {
	animationSpeed = 0.8f;
}

void BigBlock::updateAnimation(float deltaTime) {
	if (animationSpeed <= 0.0f) return;
	animationTime += deltaTime;
	float scaleOffset = std::cos(animationTime * animationSpeed) * 0.08f;
	sprite.setScale({ 1.0f + scaleOffset, 1.0f + scaleOffset });
	float angle = std::sin(animationTime * 0.3f) * 1.0f;
	sprite.setRotation(sf::degrees(angle));
}

// ============ LongBlockʵ�� ============
LongBlock::LongBlock(sf::Texture& texture, float posX, float posY, float targetWidth)
	: Obstacle(texture, posX, posY, targetWidth) {
	animationSpeed = 0.5f;
}

void LongBlock::updateAnimation(float deltaTime) {
	if (animationSpeed <= 0.0f) return;
	animationTime += deltaTime;
	float angle = std::sin(animationTime * animationSpeed) * 2.0f;
	sprite.setRotation(sf::degrees(angle));
}

// ============ Balloonʵ�� ============
Balloon::Balloon(sf::Texture& texture, float posX, float posY, float targetWidth)
	: Obstacle(texture, posX, posY, targetWidth) {
	animationSpeed = 2.0f;
}

void Balloon::updateAnimation(float deltaTime) {
	if (animationSpeed <= 0.0f) return;
	animationTime += deltaTime;
	float offset = std::sin(animationTime * animationSpeed * 5.0f) * 10.0f;
	auto pos = sprite.getPosition();
	sprite.setPosition({ pos.x, pos.y + offset * deltaTime * 60.0f });
}

// ObstacleManager ��ʵ��

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
		std::cerr << "�޷����س�·�������? "<< std::endl;
		return false;
	}
	if (!balloonTexture.loadFromFile("balloon.png")) {
		std::cerr << "�޷����ع�����������" << std::endl;
		return false;
	}
	return true;
}

void ObstacleManager::update(float deltaTime, float speed, float targetWidth) {
	spawnTimer += deltaTime;

	if (spawnTimer >= nextSpawnTime &&
		(obstacles.empty() || 800.0f - lastObstacleX >= minObstacleDistance)) {
		spawnObstacle(450.0f, targetWidth);
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


void ObstacleManager::spawnObstacle(float groundY, float targetWidth) {
	int typeIndex = getRandomObstacleType();
	float posY = groundY;
	std::unique_ptr<Obstacle> obstacle;

	switch (typeIndex) {
	case 0: // SmallBlock
		obstacle = std::make_unique<SmallBlock>(smallBlockTexture, 800.0f, posY, targetWidth);
		break;
	case 1: // BigBlock
		obstacle = std::make_unique<BigBlock>(bigBlockTexture, 800.0f, posY, targetWidth);
		break;
	case 2: // LongBlock
		obstacle = std::make_unique<LongBlock>(longBlockTexture, 800.0f, posY, targetWidth);
		break;
	case 3: // Balloon
		posY = Tool::getRandomFloat(groundY - 200.0f, groundY - 100.0f);
		obstacle = std::make_unique<Balloon>(balloonTexture, 800.0f, posY, targetWidth);
		break;
	}

	obstacles.push_back(std::move(obstacle));
	lastObstacleX = 800.0f;
}

int ObstacleManager::getRandomObstacleType() const {
	return Tool::getRandomInt(0, 3);
}

bool ObstacleManager::checkCollision(const sf::FloatRect& playerBounds) {
	for (const auto& obstacle : obstacles) {
		if (Tool::checkCollision(playerBounds, obstacle->getBounds())) {
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