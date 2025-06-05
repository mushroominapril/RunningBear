#include "UI.h"
#include <iostream>

// UI.cpp
UILabel::UILabel(const sf::Font& font, const std::string& text, unsigned int size, sf::Vector2f position)
	: m_text(font) {
	m_text.setString(text);
	m_text.setCharacterSize(size);
	m_text.setFillColor(sf::Color::Black);
	m_text.setPosition({ position.x,position.y - 100.f });
}

void UILabel::setText(const std::string& text) {
	m_text.setString(text);
}

void UILabel::setPosition(sf::Vector2f position) {
	m_text.setPosition(position);
}

void UILabel::draw(sf::RenderWindow& window) {
	window.draw(m_text);
}


UIButton::UIButton(const sf::Font& font, const std::string& text, unsigned int size,
	sf::Vector2f position, sf::Vector2f sizeRect)
	: m_text(font) {
	m_background.setSize(sizeRect);
	m_background.setFillColor(sf::Color::Blue);
	m_background.setPosition(position);

	m_text.setString(text);
	m_text.setCharacterSize(size);
	m_text.setFillColor(sf::Color::White);

	sf::FloatRect textRect = m_text.getLocalBounds();
	m_text.setOrigin({
		textRect.position.x + textRect.size.x / 2.f,
		textRect.position.y + textRect.size.y / 2.f
	});
	m_text.setPosition(position + sizeRect / 2.f);
}

void UIButton::setCallback(std::function<void()> callback) {
	m_callback = callback;
}

void UIButton::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
	if (const auto* mousePress = event.getIf<sf::Event::MouseButtonPressed>()) {
		if (mousePress->button == sf::Mouse::Button::Left) {
			sf::Vector2f mousePos = window.mapPixelToCoords(
				{ mousePress->position.x, mousePress->position.y });
			if (m_background.getGlobalBounds().contains(mousePos) && m_callback) {
				m_callback();
			}
		}
	}
}

void UIButton::draw(sf::RenderWindow& window) {
	window.draw(m_background);
	window.draw(m_text);
}

void UIButton::setPosition(sf::Vector2f position) {
	m_background.setPosition(position);
	sf::FloatRect textRect = m_text.getLocalBounds();
	m_text.setOrigin({
		textRect.position.x + textRect.size.x / 2.f,
		textRect.position.y + textRect.size.y / 2.f
	});
	m_text.setPosition(position + m_background.getSize() / 2.f);
}


UIManager::UIManager(const sf::Font& font, const std::vector<sf::Texture>& frames)
	: m_scoreLabel(font, "Score: 0", 24, { 10.f, 10.f }),
	m_statusLabel(font, "", 48, { 200.f, 200.f }),
	m_restartButton(font, "Restart", 24, { 300.f, 300.f }, { 200.f, 50.f }),
	m_startButton(font, "Start", 30, { 300.f, 200.f }, { 200.f, 50.f }),
	m_exitButton(font, "Exit", 30, { 300.f, 400.f }, { 200.f, 50.f }),
	m_titleLabel(font, "RunningBear", 72, { 250.f, 100.f }),
	m_menuFrames(frames),
	m_menuSprite(frames[0]),
	m_isGameOver(false),
	m_isInMainMenu(true)
{
	// ���ö����Ƿ���سɹ�
	m_animationLoaded = !frames.empty();

	// ���ö���Sprite��λ�ã�����ȫ���ڣ�
	m_menuSprite.setPosition({ 0.f, 0.f });

	// ���� UI Ԫ��λ��ʹ�����
	const float centerX = 400.f; // ���ڿ�ȵ�һ�룬����Ĵ��ڳߴ����

	m_titleLabel.setPosition({ centerX - 200.f, 80.f });
	m_startButton.setPosition({ centerX - 100.f, 300.f });
	m_exitButton.setPosition({ centerX - 100.f, 380.f });

	// ���ð�ť�ص�
	m_restartButton.setCallback([this]() {
		if (m_isGameOver && m_callback) {
			m_callback();
		}
		});

	m_startButton.setCallback([this]() {
		if (m_isInMainMenu && m_startCallback) {
			m_startCallback();
		}
		});

	m_exitButton.setCallback([this]() {
		if (m_isInMainMenu && m_exitCallback) {
			m_exitCallback();
		}
		});
}

void UIManager::updateScore(int score) {
	m_scoreLabel.setText("Score: " + std::to_string(score));
}

void UIManager::setGameOver(bool isGameOver) {
	m_isGameOver = isGameOver;
	if (isGameOver) {
		m_statusLabel.setText("Game Over");
	}
	else {
		m_statusLabel.setText("");
	}
}

void UIManager::setRestartCallback(std::function<void()> callback) {
	m_callback = callback;
}

void UIManager::setStartCallback(std::function<void()> callback) {
	m_startCallback = callback;
}

void UIManager::setExitCallback(std::function<void()> callback) {
	m_exitCallback = callback;
}

void UIManager::draw(sf::RenderWindow& window) {
	if (m_isInMainMenu) {
		if (m_animationLoaded) {
			// ��ȡ���ں�����ߴ�
			sf::Vector2u windowSize = window.getSize();
			sf::Vector2u textureSize = m_menuFrames[m_currentFrame].getSize();

			float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
			float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

			m_menuSprite.setScale({ scaleX, scaleY }); // ���ű���ͼ
			m_menuSprite.setPosition({ 0.f, 0.f });    // ȷ�����ϽǶ��봰��

			window.draw(m_menuSprite);
		}
		// SFML ���Զ�������Ƶ֡������
		// ֻ�����UIԪ��
		m_titleLabel.draw(window);
		m_startButton.draw(window);
		m_exitButton.draw(window);
	}
	else {
		m_scoreLabel.draw(window);
		if (m_isGameOver) {
			m_statusLabel.draw(window);
			m_restartButton.draw(window);
		}
	}
}

void UIManager::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
	if (m_isInMainMenu) {
		m_startButton.handleEvent(event, window);
		m_exitButton.handleEvent(event, window);
	}
	else if (m_isGameOver) {
		m_restartButton.handleEvent(event, window);
	}
}

void UIManager::updateAnimation(float deltaTime) {
	if (!m_isInMainMenu || !m_animationLoaded)
		return;

	m_currentTime += deltaTime;
	if (m_currentTime >= m_frameTime) {
		m_currentTime = 0.f;
		m_currentFrame = (m_currentFrame + 1) % m_menuFrames.size();
		m_menuSprite.setTexture(m_menuFrames[m_currentFrame]);
	}
}

void UIManager::showMainMenu() {
	m_isInMainMenu = true;
	m_isGameOver = false;
}

void UIManager::showGameUI() {
	m_isInMainMenu = false;
	m_isGameOver = false;
}