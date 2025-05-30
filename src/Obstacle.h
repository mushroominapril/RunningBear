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

// �ϰ�����
class Obstacle {
public:
	// ���캯��
    Obstacle(sf::Texture& texture, float posX, float posY, ObstacleType type);

	// �����ϰ����λ��
	void update(float deltaTime, float speed);

	// ����ϰ����Ƿ��Ѿ��Ƴ���Ļ
	bool isOffScreen() const;

	// ��ȡ�ϰ������ײ�߽�
	sf::FloatRect getBounds() const;

	// �����ϰ���
	void draw(sf::RenderWindow& window);
    ObstacleType getType() const { return type; }

    // ���¶���Ч��
    void updateAnimation(float deltaTime);
private:
	sf::Sprite sprite;
    ObstacleType type;
    float animationTime;
    float animationSpeed;
    bool animationDirection;
};

// �ϰ����������
class ObstacleManager {
public:
    // ���캯��
    ObstacleManager();

    // �����ϰ�������
    bool loadTextures();

    // ���������ϰ���
    void update(float deltaTime, float speed);

    // �������ϰ���
    void spawnObstacle(float groundY);

    // �������ҵ���ײ
    bool checkCollision(const sf::FloatRect& playerBounds);

    // ���������ϰ���
    void draw(sf::RenderWindow& window);

    // �����ϰ���ϵͳ
    void reset();

    // �Ѷȵ���
    void increaseDifficulty(float gameTime);

private:
    std::vector<std::unique_ptr<Obstacle>> obstacles; // �洢��ǰ��Ծ���ϰ������
    sf::Texture blockTexture;
    sf::Texture balloonTexture;
    sf::Texture longBlockTexture;

    float spawnTimer; // ���ɼ�ʱ��
    float nextSpawnTime; // �´�����ʱ��
    float minSpawnTime; // ��С����ʱ����
    float maxSpawnTime; // �������ʱ����
    float lastObstacleX; // ��һ���ϰ����X����
    float minObstacleDistance; // �ϰ���֮�����С����

    // �����������ʱ��
    float getRandomSpawnTime() const;
    ObstacleType getRandomObstacleType() const;
};