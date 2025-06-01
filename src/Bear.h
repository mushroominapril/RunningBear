#include<SFML/Graphics.hpp>
#include<vector>
class Bear {
private:
	
	//sf::Texture texture;
	sf::Texture texture, texture1, texture2, texture3, texture4;
	std::vector<sf::Texture*>textures;
	int currentTextureIndex = 0;//当前纹理的索引
	float textureSwithTime;
	float pastTime;
	sf::Sprite sprite;
	sf::Vector2f position;

	bool isOnGround;//判断是否在地面
	float moveSpeed;//水平速度
	float verticalVelocity;//竖直速度
	
    static constexpr float maxSpeed = 300.f;
	static constexpr float acceleration = 500.f;//加速,
	static constexpr float deceleration = 1000.f;//停止
	static constexpr float jumpSpeed = -600.f;//跳跃速度
	static constexpr float gravity = 700.f;//重力
	static constexpr float airControl = 1.0f;//空气阻力
	static constexpr float groundLevel = 450.f;//地面高度
public:
	/*Bear(const std::string& text, const sf::Vector2f& startPosition);*/
	Bear(const std::string& texturePath, const std::string& texturePath1, const std::string& texturePath2, const std::string& texturePath3, const std::string& texturePath4, const sf::Vector2f& startPosition);
	void update(float time);//移动
	void draw(sf::RenderWindow& window);
	void setPosition(const sf::Vector2f& Position);
	sf::Vector2f getPosition() const;
	sf::FloatRect getBounds() const;
};