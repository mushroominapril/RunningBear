//#pragma once
//#include <SFML/Graphics.hpp>
//#include <vector>
//#include <functional>
//
//// ��Ϸ״̬ö��
//enum class GameState {
//    MainMenu,
//    Playing,
//    Paused,
//    GameOver,
//    Exit
//};
//
//// ��ť�ṹ��
//struct Button {
//    sf::RectangleShape rect;
//    sf::Text text;
//    std::function<void()> action;
//};
//
//// ��ϷUI��״̬������
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
//    // ��������
//    void addScore(int points);
//    void resetScore();
//    int getScore() const;
//
//    // Ϊ����ģ���ṩ������Ϸ�����ķ���
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
//    // UI��Դ
//    sf::Font font;
//    std::vector<Button> mainMenuButtons;
//    std::vector<Button> pauseMenuButtons;
//    std::vector<Button> gameOverButtons;
//
//    // ����
//    int score;
//    sf::Text scoreText;
//
//    // ��Ϸ������Ϣ
//    sf::Text gameOverText;
//    sf::Text finalScoreText;
//};