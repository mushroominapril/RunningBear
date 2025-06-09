#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class Obstacle {
public:
	Obstacle::Obstacle(sf::Texture& texture, float posX, float posY);
	virtual ~Obstacle() = default;
	const sf::Sprite& getSprite() const;

	void update(float deltaTime, float speed); // �����ϰ����λ��
	bool isOffScreen() const; // ����ϰ����Ƿ��Ѿ��Ƴ���Ļ
	sf::FloatRect getBounds() const; // ��ȡ�ϰ������ײ�߽�
	void draw(sf::RenderWindow& window); // �����ϰ���
	//void setCollisionBoundsPadding(float paddingX, float paddingY);
	//void drawDebug(sf::RenderWindow& window);
protected:

	virtual void updateAnimation(float deltaTime) = 0; // ���¶���Ч��
	
	void initializePositionAndBounds(float posX, float posY);
	void calculatePreciseCollisionBounds();


	sf::Sprite sprite;
	float animationTime;
	float animationSpeed;
	sf::Vector2f initialPosition;

	sf::Vector2f originalScale; // ����ԭʼ���ű���
	sf::FloatRect collisionBounds; // �Զ�����ײ�߽�
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

	bool loadTextures(); // �����ϰ�������
	void update(float deltaTime, float speed); // ���������ϰ���
	bool checkCollision(const sf::Sprite& playerSprite); // �������ҵ���ײ
	void draw(sf::RenderWindow& window); // ���������ϰ���
	void reset(); // �����ϰ���ϵͳ
	void increaseDifficulty(float gameTime); // �Ѷȵ���

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