#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp> 
#include <vector>
#include <memory>

enum class ObstacleType {
    SmallBlock,
    MediumBlock,
    LargeBlock,
    Balloon,
    LongBlock
};

// 障碍物类
class Obstacle {
public:
	// 构造函数
    Obstacle(sf::Texture& texture, float posX, float posY, ObstacleType type);

	// 更新障碍物的位置
	void update(float deltaTime, float speed);

	// 检查障碍物是否已经移出屏幕
	bool isOffScreen() const;

	// 获取障碍物的碰撞边界
	sf::FloatRect getBounds() const;

	// 绘制障碍物
	void draw(sf::RenderWindow& window);
    ObstacleType getType() const { return type; }

    // 更新动画效果
    void updateAnimation(float deltaTime);
private:
	sf::Sprite sprite;
    ObstacleType type;
    float animationTime;
    float animationSpeed;
    bool animationDirection;
};

// 障碍物管理器类
class ObstacleManager {
public:
    // 构造函数
    ObstacleManager();

    // 加载障碍物纹理
    bool loadTextures();

    // 更新所有障碍物
    void update(float deltaTime, float speed);

    // 生成新障碍物
    void spawnObstacle(float groundY);

    // 检测与玩家的碰撞
    bool checkCollision(const sf::FloatRect& playerBounds);

    // 绘制所有障碍物
    void draw(sf::RenderWindow& window);

    // 重置障碍物系统
    void reset();

    // 难度调整
    void increaseDifficulty(float gameTime);

private:
    std::vector<std::unique_ptr<Obstacle>> obstacles; // 存储当前活跃的障碍物对象
    sf::Texture blockTexture;
    sf::Texture balloonTexture;
    sf::Texture longBlockTexture;

    float spawnTimer; // 生成计时器
    float nextSpawnTime; // 下次生成时间
    float minSpawnTime; // 最小生成时间间隔
    float maxSpawnTime; // 最大生成时间间隔
    float lastObstacleX; // 上一个障碍物的X坐标
    float minObstacleDistance; // 障碍物之间的最小距离

    // 生成随机生成时间
    float getRandomSpawnTime() const;
    ObstacleType getRandomObstacleType() const;
};