#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <string>
#include <memory>

class UILabel {
private:
    sf::Text m_text;
public:
    UILabel(const sf::Font& font, const std::string& text, unsigned int size, sf::Vector2f position);
    void setText(const std::string& text);
    void setPosition(sf::Vector2f position);
    void draw(sf::RenderWindow& window);
};


// UIButton.h
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
};

class UIManager {
public:
    enum class GameState {
        MainMenu,
        Playing,
        GameOver
    };
    UIManager(const sf::Font& font);
    void updateScore(int score);
    void handleEvent(const sf::Event& event, const sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    void setGameOver(bool isGameOver);
    void setRestartCallback(std::function<void()> callback);

    void showMainMenu();
    void showGameUI();
    void setStartGameCallback(std::function<void()> callback);
    void setExitGameCallback(std::function<void()> callback);
private:
    UILabel m_scoreLabel;
    UILabel m_statusLabel;
    UIButton m_restartButton;
    bool m_isGameOver;
    std::function<void()> m_callback;

    UIButton m_startButton;
    UIButton m_exitButton;
    UILabel m_titleLabel;
    bool m_isInMainMenu;
    std::function<void()> m_startCallback;
    std::function<void()> m_exitCallback;
};