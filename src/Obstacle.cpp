#include "Obstacle.h"
#include <random>
#include <iostream>

// Obstacle 类实现

Obstacle::Obstacle(sf::Texture& texture, float posX, float posY, ObstacleType type)
	: sprite(texture), type(type), animationTime(0), animationDirection(true) {
	auto size = sprite.getTexture().getSize();
	sprite.setPosition({ posX, posY - static_cast<float>(size.y) });
	switch (type) {
	case ObstacleType::Balloon:
		animationSpeed = 2.0f;
		break;
	case ObstacleType::LongBlock:
		animationSpeed = 0.5f;
		break;
	default:
		animationSpeed = 0.0f;
	}
	switch (type) {
	case ObstacleType::SmallBlock:
		sprite.setScale({ 0.7f, 0.7f });
		break;
	case ObstacleType::MediumBlock:
		sprite.setScale({ 1.0f, 1.0f });
		break;
	case ObstacleType::LargeBlock:
		sprite.setScale({ 1.3f, 1.3f });
		break;
	case ObstacleType::LongBlock:
		sprite.setScale({ 2.0f, 1.0f });
		break;
	default:
		break;
	}
}

void Obstacle::update(float deltaTime, float speed) {
	sprite.move({ -speed * deltaTime, 0 });
	updateAnimation(deltaTime);
}

void Obstacle::updateAnimation(float deltaTime) {
	if (animationSpeed <= 0.0f) return;
	animationTime += deltaTime;

	switch (type) {
	case ObstacleType::Balloon: {
		float offset = std::sin(animationTime * animationSpeed * 5.0f) * 10.0f;
		auto pos = sprite.getPosition();
		sprite.setPosition({ pos.x, pos.y + offset * deltaTime * 60.0f });
		break;
	}
	case ObstacleType::LongBlock: {
		float angle = std::sin(animationTime * animationSpeed) * 2.0f;
		sprite.setRotation(sf::degrees(angle));
		break;
	}
	default:
		if (type == ObstacleType::SmallBlock ||
			type == ObstacleType::MediumBlock ||
			type == ObstacleType::LargeBlock) {
			float scaleOffset = std::sin(animationTime * animationSpeed) * 0.05f;
			sf::Vector2f baseScale = sprite.getScale();
			sprite.setScale({ baseScale.x * (1.0f + scaleOffset), baseScale.y * (1.0f + scaleOffset) });
		}
		break;
	}
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


// ObstacleManager 类实现

ObstacleManager::ObstacleManager()
	:spawnTimer(0), nextSpawnTime(0), minSpawnTime(1.0f), maxSpawnTime(3.0f),
	lastObstacleX(0), minObstacleDistance(300.0f) {
	nextSpawnTime = getRandomSpawnTime();
}

bool ObstacleManager::loadTextures() {
	if (!blockTexture.loadFromFile("assets/small_cactus.png")) {
		std::cerr << "无法加载路障纹理！" << std::endl;
		return false;
	}
	if (!blockTexture.loadFromFile("assets/medium_cactus.png")) {
		std::cerr << "无法加载路障纹理！" << std::endl;
		return false;
	}
	if (!blockTexture.loadFromFile("assets/large_cactus.png")) {
		std::cerr << "无法加载路障纹理！" << std::endl;
		return false;
	}
	if (!balloonTexture.loadFromFile("assets/bird.png")) {
		std::cerr << "无法加载广告气球纹理！" << std::endl;
		return false;
	}
	if (!longBlockTexture.loadFromFile("assets/long_obstacle.png")) {
		std::cerr << "无法加载长路障纹理！" << std::endl;
		return false;
	}
	return true;
}

//
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
	std::random_device rd;
	std::mt19937 gen(rd());
	ObstacleType type = getRandomObstacleType();

	sf::Texture* texture = nullptr;
	switch (type) {
	case ObstacleType::SmallBlock:
		texture = &blockTexture;
		break;
	case ObstacleType::MediumBlock:
		texture = &blockTexture;
		break;
	case ObstacleType::LargeBlock:
		texture = &blockTexture;
		break;
	case ObstacleType::Balloon:
		texture = &balloonTexture;
		break;
	case ObstacleType::LongBlock:
		texture = &longBlockTexture;
		break;
	}
	if (!texture) return;

	float posY = groundY;
	if (type == ObstacleType::Balloon) {
		std::uniform_real_distribution<float> height(groundY - 200.0f, groundY - 100.0f);
		posY = height(gen);
	}

	obstacles.push_back(std::make_unique<Obstacle>(*texture, 800.0f, posY, type));
	lastObstacleX = 800.0f;
}

ObstacleType ObstacleManager::getRandomObstacleType() const {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> typeDis(0, 4);

	switch (typeDis(gen)) {
	case 0: return ObstacleType::SmallBlock;
	case 1: return ObstacleType::MediumBlock;
	case 2: return ObstacleType::LargeBlock;
	case 3: return ObstacleType::Balloon;
	case 4: return ObstacleType::LongBlock;
	default: return ObstacleType::MediumBlock;
	}
}

bool ObstacleManager::checkCollision(const sf::FloatRect& playerBounds) {
	for (const auto& obstacle : obstacles) {
		sf::FloatRect obstacleBounds = obstacle->getBounds();

		bool collision = !(playerBounds.position.x + playerBounds.size.x < obstacleBounds.position.x ||
			obstacleBounds.position.x + obstacleBounds.size.x < playerBounds.position.x ||
			playerBounds.position.y + playerBounds.size.y < obstacleBounds.position.y ||
			obstacleBounds.position.y + obstacleBounds.size.y < playerBounds.position.y);

		if (collision) {
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
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(1.5f, 3.0f); // 
	return dis(gen);
}

void ObstacleManager::increaseDifficulty(float gameTime) {
	minSpawnTime = std::max(0.5f, 1.0f - gameTime / 60.0f);
	maxSpawnTime = std::max(1.5f, 3.0f - gameTime / 30.0f);
	minObstacleDistance = std::max(150.0f, 300.0f - gameTime / 2.0f);
}