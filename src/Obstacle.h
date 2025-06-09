#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class Obstacle {
public:
	Obstacle::Obstacle(sf::Texture& texture, float posX, float posY);
	virtual ~Obstacle() = default;
	const sf::Sprite& getSprite() const;

	void update(float deltaTime, float speed); // 更新障碍物的位置
	bool isOffScreen() const; // 检查障碍物是否已经移出屏幕
	sf::FloatRect getBounds() const; // 获取障碍物的碰撞边界
	void draw(sf::RenderWindow& window); // 绘制障碍物
	//void setCollisionBoundsPadding(float paddingX, float paddingY);
	//void drawDebug(sf::RenderWindow& window);
protected:

	virtual void updateAnimation(float deltaTime) = 0; // 更新动画效果
	
	void initializePositionAndBounds(float posX, float posY);
	void calculatePreciseCollisionBounds();


	sf::Sprite sprite;
	float animationTime;
	float animationSpeed;
	sf::Vector2f initialPosition;

	sf::Vector2f originalScale; // 保存原始缩放比例
	sf::FloatRect collisionBounds; // 自定义碰撞边界
};

// 
class SmallBlock : public Obstacle {
public:
	SmallBlock::SmallBlock(sf::Texture& texture, float posX, float posY);
protected:
	void updateAnimation(float deltaTime) override;
};

// 
class BigBlock : public Obstacle {
public:
	BigBlock(sf::Texture& texture, float posX, float posY);
protected:
	void updateAnimation(float deltaTime) override;
};

// 
class LongBlock : public Obstacle {
public:
	LongBlock(sf::Texture& texture, float posX, float posY);
protected:
	void updateAnimation(float deltaTime) override;
};

// 
class Balloon : public Obstacle {
public:
	Balloon(sf::Texture& texture, float posX, float posY);
protected:
	void updateAnimation(float deltaTime) override;
};

//
class ObstacleManager {
public:
	ObstacleManager();

	bool loadTextures(); // 加载障碍物纹理
	void update(float deltaTime, float speed); // 更新所有障碍物
	bool checkCollision(const sf::Sprite& playerSprite); // 检测与玩家的碰撞
	void draw(sf::RenderWindow& window); // 绘制所有障碍物
	void reset(); // 重置障碍物系统
	void increaseDifficulty(float gameTime); // 难度调整

	//void drawDebug(sf::RenderWindow& window);
private:

	void spawnObstacle(float groundY);
	float getRandomSpawnTime() const; 
	int getRandomObstacleType() const;

	std::vector<std::unique_ptr<Obstacle>> obstacles;
	sf::Texture smallBlockTexture;
	sf::Texture bigBlockTexture;
	sf::Texture longBlockTexture;
	sf::Texture balloonTexture;

	float spawnTimer; 
	float nextSpawnTime;
	float minSpawnTime; 
	float maxSpawnTime; 
	float lastObstacleX;
	float minObstacleDistance; 
};