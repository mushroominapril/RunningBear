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
    UILabel m_scoreLabel;    // 分数标签
    UILabel m_statusLabel;   // 状态标签（游戏结束提示）
    UIButton m_restartButton; // 重启按钮
    UIButton m_startButton;  // 开始游戏按钮
    UIButton m_exitButton;   // 退出游戏按钮
    UILabel m_titleLabel;    // 游戏标题

    std::vector<sf::Texture> m_menuFrames; // 动画帧纹理
    sf::Sprite m_menuSprite;                // 当前帧精灵
    float m_frameTime = 0.1f;               // 每帧持续时间（秒）
    float m_currentTime = 0.f;              // 当前帧累计时间
    size_t m_currentFrame = 0;              // 当前帧索引
    bool m_animationLoaded = false;         // 动画是否加载成功

    bool m_isGameOver;       // 游戏是否结束
    bool m_isInMainMenu;     // 是否在主菜单
    std::function<void()> m_callback;  // 重启回调
    std::function<void()> m_startCallback; // 开始游戏回调
    std::function<void()> m_exitCallback;  // 退出游戏回调
};