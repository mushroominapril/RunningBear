//#pragma once
//#include <SFML/Graphics.hpp>
//#include <vector>
//#include <functional>
//
//// 游戏状态枚举
//enum class GameState {
//    MainMenu,
//    Playing,
//    Paused,
//    GameOver,
//    Exit
//};
//
//// 按钮结构体
//struct Button {
//    sf::RectangleShape rect;
//    sf::Text text;
//    std::function<void()> action;
//};
//
//// 游戏UI和状态管理类
//class GameUIState {
//public:
//    GameUIState(sf::RenderWindow& window);
//
//    void initialize();
//    void handleEvents(sf::Event& event);
//    void update(float deltaTime);
//    void render();
//
//    void changeState(GameState newState);
//    GameState getCurrentState() const;
//
//    // 分数管理
//    void addScore(int points);
//    void resetScore();
//    int getScore() const;
//
//    // 为其他模块提供设置游戏结束的方法
//    void setGameOver(int finalScore);
//
//private:
//    void initMainMenu();
//    void initPauseMenu();
//    void initGameOverMenu();
//
//    void drawMainMenu();
//    void drawPauseMenu();
//    void drawGameOverMenu();
//    void drawHUD();
//
//    sf::RenderWindow& window;
//    GameState currentState;
//
//    // UI资源
//    sf::Font font;
//    std::vector<Button> mainMenuButtons;
//    std::vector<Button> pauseMenuButtons;
//    std::vector<Button> gameOverButtons;
//
//    // 分数
//    int score;
//    sf::Text scoreText;
//
//    // 游戏结束信息
//    sf::Text gameOverText;
//    sf::Text finalScoreText;
//};