#include"Glod.h"

Glod::Glod(const std::string& texturePath, const sf::Vector2f& position) :texture(texturePath), sprite(texture) {
	/*srand(static_cast<unsigned int>(time(0)));*/
	if (!texture.loadFromFile(texturePath)) {
		throw std::runtime_error("Failed to load coin texture: " + texturePath);
	}
	/*float x = rand() % static_cast<int>(width);
	float y = rand() % static_cast<int>(height);*/
	sprite.setPosition(position);
	sprite.setScale({0.5f, 0.5f});
	
	/*sprite.setTexture(texture);*/
}

void Glod::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
	sprite.setColor(sf::Color::White);  // 强制设为可见
}

sf::Vector2f Glod::getPosition() const
{
	return sprite.getPosition();
}

void Glod::disapper()
{
	sprite.setScale({ 0.f, 0.f });
}

void Glod::generate(std::vector<Glod>& glods)
{
	sf::Vector2f position = sprite.getPosition();
	position.x += 1.f;
	if (position.x > 800.F) position.x = 0.f;
	sprite.setPosition(position);
}

