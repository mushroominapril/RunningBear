#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

// �ϰ�����
class Obstacle {
public:
	Obstacle(sf::Texture& texture, float posX, float posY, float targetWidth);
	virtual ~Obstacle() = default;

	virtual void update(float deltaTime, float speed); // �����ϰ����λ��
	virtual bool isOffScreen() const; // ����ϰ����Ƿ��Ѿ��Ƴ���Ļ
	virtual sf::FloatRect getBounds() const; // ��ȡ�ϰ������ײ�߽�
	virtual void draw(sf::RenderWindow& window); // �����ϰ���

	const sf::Sprite& getSprite() const;

protected:
	virtual void updateAnimation(float deltaTime) = 0; // ���¶���Ч��

	sf::Sprite sprite;
	float animationTime;
	float animationSpeed;
};

// С�ϰ���
class SmallBlock : public Obstacle {
public:
	SmallBlock(sf::Texture& texture, float posX, float posY, float targetWidth);
protected:
	void updateAnimation(float deltaTime) override;
};

// ���ϰ���
class BigBlock : public Obstacle {
public:
	BigBlock(sf::Texture& texture, float posX, float posY, float targetWidth);
protected:
	void updateAnimation(float deltaTime) override;
};

// ���ϰ���
class LongBlock : public Obstacle {
public:
	LongBlock(sf::Texture& texture, float posX, float posY, float targetWidth);
protected:
	void updateAnimation(float deltaTime) override;
};

// �����ϰ���
class Balloon : public Obstacle {
public:
	Balloon(sf::Texture& texture, float posX, float posY, float targetWidth);
protected:
	void updateAnimation(float deltaTime) override;
};

// �ϰ����������
class ObstacleManager {
public:
	ObstacleManager();

	bool loadTextures(); // �����ϰ�������
	void update(float deltaTime, float speed, float targetWidth); // ���������ϰ���
	/*bool checkCollision(const sf::FloatRect& playerBounds);*/
	bool checkCollision(const sf::Sprite& playerSprite);
	// �������ҵ���ײ
	void draw(sf::RenderWindow& window); // ���������ϰ���
	void reset(); // �����ϰ���ϵͳ
	void increaseDifficulty(float gameTime); // �Ѷȵ���

private:
	void spawnObstacle(float groundY, float targetWidth); // �������ϰ���
	float getRandomSpawnTime() const; // �����������ʱ��
	int getRandomObstacleType() const; // ��������ϰ�������

	std::vector<std::unique_ptr<Obstacle>> obstacles; // �洢��ǰ��Ծ���ϰ������
	sf::Texture smallBlockTexture;
	sf::Texture bigBlockTexture;
	sf::Texture longBlockTexture;
	sf::Texture balloonTexture;

	float spawnTimer; // ���ɼ�ʱ��
	float nextSpawnTime; // �´�����ʱ��
	float minSpawnTime; // ��С����ʱ����
	float maxSpawnTime; // �������ʱ����
	float lastObstacleX; // ��һ���ϰ����X����
	float minObstacleDistance; // �ϰ���֮�����С����
};