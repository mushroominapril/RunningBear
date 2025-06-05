#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <string>
#include <vector>

class UILabel {
private:
    sf::Text m_text;
public:
    UILabel(const sf::Font& font, const std::string& text, unsigned int size, sf::Vector2f position);
    void setText(const std::string& text);
    void setPosition(sf::Vector2f position);
    void draw(sf::RenderWindow& window);
};

class UIButton {
private:
    sf::RectangleShape m_background;
    sf::Text m_text;
    std::function<void()> m_callback;
public:
    UIButton(const sf::Font& font, const std::string& text, unsigned int size, sf::Vector2f position, sf::Vector2f sizeRect);
    void setCallback(std::function<void()> callback);
    void draw(sf::RenderWindow& window);
    void handleEvent(const sf::Event& event, const sf::RenderWindow& window);
    void setPosition(sf::Vector2f position);
};

class UIManager {
public:
    UIManager::UIManager(const sf::Font& font, const std::vector<sf::Texture>& frames);
    void updateScore(int score);
    void handleEvent(const sf::Event& event, const sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    void setGameOver(bool isGameOver);
    void setRestartCallback(std::function<void()> callback);

    void showMainMenu();
    void showGameUI();
    void setStartCallback(std::function<void()> callback);
    void setExitCallback(std::function<void()> callback);
    void updateAnimation(float deltaTime);
private:
    UILabel m_scoreLabel;    // ������ǩ
    UILabel m_statusLabel;   // ״̬��ǩ����Ϸ������ʾ��
    UIButton m_restartButton; // �����ť
    UIButton m_startButton;  // ��ʼ��Ϸ��ť
    UIButton m_exitButton;   // �˳���Ϸ��ť
    UILabel m_titleLabel;    // ��Ϸ����

    std::vector<sf::Texture> m_menuFrames; // ����֡����
    sf::Sprite m_menuSprite;                // ��ǰ֡����
    float m_frameTime = 0.1f;               // ÿ֡����ʱ�䣨�룩
    float m_currentTime = 0.f;              // ��ǰ֡�ۼ�ʱ��
    size_t m_currentFrame = 0;              // ��ǰ֡����
    bool m_animationLoaded = false;         // �����Ƿ���سɹ�

    bool m_isGameOver;       // ��Ϸ�Ƿ����
    bool m_isInMainMenu;     // �Ƿ������˵�
    std::function<void()> m_callback;  // ����ص�
    std::function<void()> m_startCallback; // ��ʼ��Ϸ�ص�
    std::function<void()> m_exitCallback;  // �˳���Ϸ�ص�
};