#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

// 障碍物类
class Obstacle {
public:
	Obstacle(sf::Texture& texture, float posX, float posY, float targetWidth);
	virtual ~Obstacle() = default;

	virtual void update(float deltaTime, float speed); // 更新障碍物的位置
	virtual bool isOffScreen() const; // 检查障碍物是否已经移出屏幕
	virtual sf::FloatRect getBounds() const; // 获取障碍物的碰撞边界
	virtual void draw(sf::RenderWindow& window); // 绘制障碍物

protected:
	virtual void updateAnimation(float deltaTime) = 0; // 更新动画效果

	sf::Sprite sprite;
	float animationTime;
	float animationSpeed;
};

// 小障碍物
class SmallBlock : public Obstacle {
public:
	SmallBlock(sf::Texture& texture, float posX, float posY, float targetWidth);
protected:
	void updateAnimation(float deltaTime) override;
};

// 大障碍物
class BigBlock : public Obstacle {
public:
	BigBlock(sf::Texture& texture, float posX, float posY, float targetWidth);
protected:
	void updateAnimation(float deltaTime) override;
};

// 长障碍物
class LongBlock : public Obstacle {
public:
	LongBlock(sf::Texture& texture, float posX, float posY, float targetWidth);
protected:
	void updateAnimation(float deltaTime) override;
};

// 气球障碍物
class Balloon : public Obstacle {
public:
	Balloon(sf::Texture& texture, float posX, float posY, float targetWidth);
protected:
	void updateAnimation(float deltaTime) override;
};

// 障碍物管理器类
class ObstacleManager {
public:
	ObstacleManager();

	bool loadTextures(); // 加载障碍物纹理
	void update(float deltaTime, float speed, float targetWidth); // 更新所有障碍物
	bool checkCollision(const sf::FloatRect& playerBounds); // 检测与玩家的碰撞
	void draw(sf::RenderWindow& window); // 绘制所有障碍物
	void reset(); // 重置障碍物系统
	void increaseDifficulty(float gameTime); // 难度调整

private:
	void spawnObstacle(float groundY, float targetWidth); // 生成新障碍物
	float getRandomSpawnTime() const; // 生成随机生成时间
	int getRandomObstacleType() const; // 生成随机障碍物类型

	std::vector<std::unique_ptr<Obstacle>> obstacles; // 存储当前活跃的障碍物对象
	sf::Texture smallBlockTexture;
	sf::Texture bigBlockTexture;
	sf::Texture longBlockTexture;
	sf::Texture balloonTexture;

	float spawnTimer; // 生成计时器
	float nextSpawnTime; // 下次生成时间
	float minSpawnTime; // 最小生成时间间隔
	float maxSpawnTime; // 最大生成时间间隔
	float lastObstacleX; // 上一个障碍物的X坐标
	float minObstacleDistance; // 障碍物之间的最小距离
};