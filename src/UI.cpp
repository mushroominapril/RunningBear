#include "UI.h"
#include <variant> 

// UI.cpp
UILabel::UILabel(const sf::Font& font, const std::string& text, unsigned int size, sf::Vector2f position)
    : m_text(font)
{
    m_text.setString(text);
    m_text.setCharacterSize(size);
    m_text.setFillColor(sf::Color::White);
    m_text.setPosition(position);
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
    : m_text(font)
{
    m_background.setSize(sizeRect);
    m_background.setFillColor(sf::Color::Blue);
    m_background.setPosition(position);

    m_text.setString(text);
    m_text.setCharacterSize(size);
    m_text.setFillColor(sf::Color::White);

    sf::FloatRect textRect = m_text.getLocalBounds();
    m_text.setOrigin(
        { textRect.position.x + textRect.size.x / 2.f,
        textRect.position.y + textRect.size.y / 2.f });
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

UIManager::UIManager(const sf::Font& font)
    : m_scoreLabel(font, "Score: 0", 24, { 10.f, 10.f }),
    m_statusLabel(font, "", 48, { 200.f, 200.f }),
    m_restartButton(font, "Restart", 24, { 300.f, 300.f }, { 200.f, 50.f }),
    m_startButton(font, "开始游戏", 30, { 300.f, 200.f }, { 200.f, 50.f }),
    m_exitButton(font, "退出游戏", 30, { 300.f, 400.f }, { 200.f, 50.f }),
    m_titleLabel(font, "奔跑的熊", 72, { 250.f, 100.f }),
    m_isGameOver(false),
    m_isInMainMenu(true)
{
    m_restartButton.setCallback([this]() {
        if (m_isGameOver && m_callback) {
            m_callback();
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

void UIManager::draw(sf::RenderWindow& window) {
    if (m_isInMainMenu) {
        // 绘制主菜单
        m_titleLabel.draw(window);
        m_startButton.draw(window);
        m_exitButton.draw(window);
    }
    else {
        // 绘制游戏界面
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

void UIManager::showMainMenu() {
    m_isInMainMenu = true;
    m_isGameOver = false;
}

void UIManager::showGameUI() {
    m_isInMainMenu = false;
    m_isGameOver = false;
}