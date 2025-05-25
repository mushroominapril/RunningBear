#include<SFML/Graphics.hpp>
class Bear {
private:
	
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f position;

	bool isOnGround;//判断是否在地面
	float moveSpeed;//水平速度
	float verticalVelocity;//竖直速度
	

	static constexpr float maxSpeed = 300.f;
	static constexpr float acceleration = 800.f;//加速
	static constexpr float deceleration = 1000.f;//停止
	static constexpr float jumpSpeed = -600.f;//跳跃速度
	static constexpr float gravity = 700.f;//重力
	static constexpr float airControl = 1.0f;//空气阻力
	static constexpr float groundLevel = 450.f;//地面高度
public:
	Bear(const std::string& text, const sf::Vector2f& startPosition);
	void update(float time);//移动
	void draw(sf::RenderWindow& window);
	void setPosition(const sf::Vector2f& Position);
	sf::Vector2f getPosition() const;
	
};