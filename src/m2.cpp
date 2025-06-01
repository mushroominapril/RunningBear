//#pragma once
//#include <SFML/Graphics.hpp>
//#include <vector>
//#include <functional>
//#include "GameState.h"
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
//    void drawScoreBoard();
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
//
//    // 记分系统
//    bool showScoreBoard = false;
//    std::vector<int> highScores = { 500, 400, 300, 200, 100 }; // 示例高分
//};
//
//// 实现部分
//GameUIState::GameUIState(sf::RenderWindow& window)
//    : window(window), currentState(GameState::MainMenu), score(0) {
//    initialize();
//}
//
//void GameUIState::initialize() {
//    // 加载字体
//    if (!font.loadFromFile("arial.ttf")) {
//        std::cerr << "无法加载字体文件！请确保arial.ttf在正确位置" << std::endl;
//    }
//
//    // 初始化分数显示
//    scoreText.setFont(font);
//    scoreText.setCharacterSize(24);
//    scoreText.setFillColor(sf::Color::White);
//    scoreText.setPosition(20, 20);
//    scoreText.setString("分数: 0");
//
//    // 初始化游戏结束文本
//    gameOverText.setFont(font);
//    gameOverText.setString("游戏结束");
//    gameOverText.setCharacterSize(48);
//    gameOverText.setFillColor(sf::Color::Red);
//
//    finalScoreText.setFont(font);
//    finalScoreText.setCharacterSize(36);
//    finalScoreText.setFillColor(sf::Color::White);
//
//    // 初始化各个菜单
//    initMainMenu();
//    initPauseMenu();
//    initGameOverMenu();
//}
//
//void GameUIState::initMainMenu() {
//    mainMenuButtons.clear();
//
//    auto createButton = [this](sf::Vector2f size, sf::Vector2f pos,
//        sf::Color color, const std::string& text,
//        std::function<void()> action) {
//            Button btn;
//            btn.rect.setSize(size);
//            btn.rect.setPosition(pos);
//            btn.rect.setFillColor(color);
//
//            btn.text.setFont(font);
//            btn.text.setString(text);
//            btn.text.setCharacterSize(24);
//            btn.text.setFillColor(sf::Color::White);
//            btn.text.setPosition(
//                pos.x + (size.x - btn.text.getLocalBounds().width) / 2,
//                pos.y + (size.y - 30) / 2
//            );
//
//            btn.action = action;
//            return btn;
//        };
//
//    // 1. 开始游戏按钮
//    mainMenuButtons.push_back(createButton(
//        { 200, 50 }, { 300, 200 }, sf::Color::Green,
//        "1. 开始游戏",
//        [this]() { showScoreBoard = false; changeState(GameState::Playing); }
//    ));
//
//    // 2. 记分系统按钮
//    mainMenuButtons.push_back(createButton(
//        { 200, 50 }, { 300, 280 }, sf::Color::Blue,
//        "2. 记分系统",
//        [this]() { showScoreBoard = true; }
//    ));
//
//    // 3. 中止游戏按钮
//    mainMenuButtons.push_back(createButton(
//        { 200, 50 }, { 300, 360 }, sf::Color(255, 165, 0), // 橙色
//        "3. 中止游戏",
//        [this]() { changeState(GameState::Paused); }
//    ));
//
//    // 4. 结束游戏按钮
//    mainMenuButtons.push_back(createButton(
//        { 200, 50 }, { 300, 440 }, sf::Color::Red,
//        "4. 结束游戏",
//        [this]() { changeState(GameState::Exit); }
//    ));
//}
//
//void GameUIState::initPauseMenu() {
//    pauseMenuButtons.clear();
//
//    auto createButton = [this](sf::Vector2f size, sf::Vector2f pos,
//        sf::Color color, const std::string& text,
//        std::function<void()> action) {
//            Button btn;
//            btn.rect.setSize(size);
//            btn.rect.setPosition(pos);
//            btn.rect.setFillColor(color);
//            
//            btn.text.setFont(font);
//            btn.text.setString(text);
//            btn.text.setCharacterSize(24);
//            btn.text.setFillColor(sf::Color::White);
//            btn.text.setPosition(
//                pos.x + (size.x - btn.text.getLocalBounds().width) / 2,
//                pos.y + (size.y - 30) / 2
//            );
//
//            btn.action = action;
//            return btn;
//        };
//
//    // 继续游戏按钮
//    pauseMenuButtons.push_back(createButton(
//        { 200, 50 }, { 300, 200 }, sf::Color::Green,
//        "继续游戏",
//        [this]() { changeState(GameState::Playing); }
//    ));
//
//    // 返回主菜单按钮
//    pauseMenuButtons.push_back(createButton(
//        { 200, 50 }, { 300, 280 }, sf::Color::Blue,
//        "主菜单",
//        [this]() { changeState(GameState::MainMenu); }
//    ));
//
//    // 退出游戏按钮
//    pauseMenuButtons.push_back(createButton(
//        { 200, 50 }, { 300, 360 }, sf::Color::Red,
//        "退出游戏",
//        [this]() { changeState(GameState::Exit); }
//    ));
//}
//
//void GameUIState::initGameOverMenu() {
//    gameOverButtons.clear();
//
//    auto createButton = [this](sf::Vector2f size, sf::Vector2f pos,
//        sf::Color color, const std::string& text,
//        std::function<void()> action) {
//            Button btn;
//            btn.rect.setSize(size);
//            btn.rect.setPosition(pos);
//            btn.rect.setFillColor(color);
//
//            btn.text.setFont(font);
//            btn.text.setString(text);
//            btn.text.setCharacterSize(24);
//            btn.text.setFillColor(sf::Color::White);
//            btn.text.setPosition(
//                pos.x + (size.x - btn.text.getLocalBounds().width) / 2,
//                pos.y + (size.y - 30) / 2
//            );
//
//            btn.action = action;
//            return btn;
//        };
//
//    // 重新开始按钮
//    gameOverButtons.push_back(createButton(
//        { 200, 50 }, { 300, 300 }, sf::Color::Green,
//        "重新开始",
//        [this]() { resetScore(); changeState(GameState::Playing); }
//    ));
//
//    // 返回主菜单按钮
//    gameOverButtons.push_back(createButton(
//        { 200, 50 }, { 300, 380 }, sf::Color::Blue,
//        "主菜单",
//        [this]() { changeState(GameState::MainMenu); }
//    ));
//}
//
//void GameUIState::handleEvents(sf::Event& event) {
//    if (event.type == sf::Event::KeyPressed) {
//        if (event.key.code == sf::Keyboard::Escape) {
//            if (currentState == GameState::Playing) {
//                changeState(GameState::Paused);
//            }
//            else if (currentState == GameState::Paused) {
//                changeState(GameState::Playing);
//            }
//        }
//    }
//
//    if (event.type == sf::Event::MouseButtonPressed) {
//        if (event.mouseButton.button == sf::Mouse::Left) {
//            sf::Vector2f mousePos = window.mapPixelToCoords(
//                sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
//
//            // 根据当前状态检查不同的按钮
//            std::vector<Button>* buttons = nullptr;
//            switch (currentState) {
//            case GameState::MainMenu: buttons = &mainMenuButtons; break;
//            case GameState::Paused: buttons = &pauseMenuButtons; break;
//            case GameState::GameOver: buttons = &gameOverButtons; break;
//            default: break;
//            }
//
//            if (buttons) {
//                for (auto& button : *buttons) {
//                    if (button.rect.getGlobalBounds().contains(mousePos)) {
//                        button.action();
//                        break;
//                    }
//                }
//            }
//        }
//    }
//}
//
//void GameUIState::update(float deltaTime) {
//    // 更新分数显示
//    scoreText.setString("分数: " + std::to_string(score));
//
//    // 如果是游戏结束状态，更新最终分数显示
//    if (currentState == GameState::GameOver) {
//        finalScoreText.setString("最终得分: " + std::to_string(score));
//
//        // 居中显示游戏结束文本
//        sf::FloatRect textRect = gameOverText.getLocalBounds();
//        gameOverText.setOrigin(textRect.left + textRect.width / 2.0f,
//            textRect.top + textRect.height / 2.0f);
//        gameOverText.setPosition(window.getSize().x / 2.0f, 150);
//
//        // 居中显示最终分数
//        textRect = finalScoreText.getLocalBounds();
//        finalScoreText.setOrigin(textRect.left + textRect.width / 2.0f,
//            textRect.top + textRect.height / 2.0f);
//        finalScoreText.setPosition(window.getSize().x / 2.0f, 220);
//    }
//}
//
//void GameUIState::render() {
//    // 根据当前状态绘制不同的UI
//    switch (currentState) {
//    case GameState::MainMenu:
//        drawMainMenu();
//        if (showScoreBoard) {
//            drawScoreBoard();
//        }
//        break;
//    case GameState::Playing:
//        drawHUD();
//        break;
//    case GameState::Paused:
//        drawHUD();
//        drawPauseMenu();
//        break;
//    case GameState::GameOver:
//        drawGameOverMenu();
//        break;
//    default:
//        break;
//    }
//}
//
//void GameUIState::drawMainMenu() {
//    // 绘制背景
//    sf::RectangleShape background(sf::Vector2f(window.getSize()));
//    background.setFillColor(sf::Color(50, 50, 100));
//    window.draw(background);
//
//    // 绘制标题
//    sf::Text title("跑酷游戏", font, 48);
//    title.setFillColor(sf::Color::White);
//    title.setPosition(300, 100);
//    window.draw(title);
//
//    // 绘制按钮
//    for (auto& button : mainMenuButtons) {
//        window.draw(button.rect);
//        window.draw(button.text);
//    }
//}
//
//void GameUIState::drawPauseMenu() {
//    // 绘制半透明背景
//    sf::RectangleShape overlay(sf::Vector2f(window.getSize()));
//    overlay.setFillColor(sf::Color(0, 0, 0, 150));
//    window.draw(overlay);
//
//    // 绘制暂停标题
//    sf::Text title("游戏已暂停", font, 48);
//    title.setFillColor(sf::Color::White);
//    title.setPosition(300, 100);
//    window.draw(title);
//
//    // 绘制按钮
//    for (auto& button : pauseMenuButtons) {
//        window.draw(button.rect);
//        window.draw(button.text);
//    }
//}
//
//void GameUIState::drawGameOverMenu() {
//    // 绘制背景
//    sf::RectangleShape background(sf::Vector2f(window.getSize()));
//    background.setFillColor(sf::Color(100, 50, 50));
//    window.draw(background);
//
//    // 绘制游戏结束文本和分数
//    window.draw(gameOverText);
//    window.draw(finalScoreText);
//
//    // 绘制按钮
//    for (auto& button : gameOverButtons) {
//        window.draw(button.rect);
//        window.draw(button.text);
//    }
//}
//
//void GameUIState::drawHUD() {
//    // 绘制分数
//    window.draw(scoreText);
//}
//
//void GameUIState::drawScoreBoard() {
//    // 绘制半透明背景
//    sf::RectangleShape overlay(sf::Vector2f(window.getSize()));
//    overlay.setFillColor(sf::Color(0, 0, 0, 200));
//    window.draw(overlay);
//
//    // 绘制记分板标题
//    sf::Text title("记分系统", font, 36);
//    title.setFillColor(sf::Color::Yellow);
//    title.setPosition(350, 100);
//    window.draw(title);
//
//    // 绘制高分记录
//    sf::Text scoresText;
//    scoresText.setFont(font);
//    scoresText.setCharacterSize(24);
//    scoresText.setFillColor(sf::Color::White);
//    scoresText.setPosition(300, 150);
//
//    std::string scoresStr = "最高分记录:\n";
//    for (size_t i = 0; i < highScores.size(); ++i) {
//        scoresStr += std::to_string(i + 1) + ". " + std::to_string(highScores[i]) + "\n";
//    }
//    scoresText.setString(scoresStr);
//    window.draw(scoresText);
//
//    // 绘制返回按钮
//    Button backButton;
//    backButton.rect.setSize({ 150, 40 });
//    backButton.rect.setPosition(325, 400);
//    backButton.rect.setFillColor(sf::Color::Blue);
//
//    backButton.text.setFont(font);
//    backButton.text.setString("返回");
//    backButton.text.setCharacterSize(24);
//    backButton.text.setFillColor(sf::Color::White);
//    backButton.text.setPosition(
//        backButton.rect.getPosition().x + 50,
//        backButton.rect.getPosition().y + 5
//    );
//
//    window.draw(backButton.rect);
//    window.draw(backButton.text);
//}
//
//void GameUIState::changeState(GameState newState) {
//    currentState = newState;
//}
//
//GameState GameUIState::getCurrentState() const {
//    return currentState;
//}
//
//void GameUIState::addScore(int points) {
//    score += points;
//}
//
//void GameUIState::resetScore() {
//    score = 0;
//}
//
//int GameUIState::getScore() const {
//    return score;
//}
//
//void GameUIState::setGameOver(int finalScore) {
//    score = finalScore;
//    changeState(GameState::GameOver);
//}
//
//
//
//
//#include <SFML/Graphics.hpp>
//
//int main() {
//    sf::RenderWindow window(sf::VideoMode(800, 600), "跑酷游戏 - 菜单");
//
//    // 1. 加载字体
//    sf::Font font;
//    if (!font.loadFromFile("arial.ttf")) {
//        // 处理加载失败
//    }
//
//    // 2. 创建UI元素（标题、按钮）
//    sf::Text title("跑酷游戏", font, 50);
//    title.setPosition(300, 100);
//
//    sf::RectangleShape startButton(sf::Vector2f(200, 50));
//    startButton.setPosition(300, 300);
//    startButton.setFillColor(sf::Color::Green);
//
//    sf::Text startText("开始游戏", font, 30);
//    startText.setPosition(350, 310);
//
//    // 主循环
//    while (window.isOpen()) {
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed) {
//                window.close();
//            }
//            // 3. 处理按钮点击事件
//            if (event.type == sf::Event::MouseButtonPressed) {
//                if (startButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
//                    // 切换到游戏场景
//                }
//            }
//        }
//
//        // 4. 绘制UI
//        window.clear();
//        window.draw(title);
//        window.draw(startButton);
//        window.draw(startText);
//        window.display();
//    }
//    return 0;
//}