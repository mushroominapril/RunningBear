//#pragma once
//#include <SFML/Graphics.hpp>
//#include <vector>
//#include <functional>
//#include "GameState.h"
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
//
//    // �Ƿ�ϵͳ
//    bool showScoreBoard = false;
//    std::vector<int> highScores = { 500, 400, 300, 200, 100 }; // ʾ���߷�
//};
//
//// ʵ�ֲ���
//GameUIState::GameUIState(sf::RenderWindow& window)
//    : window(window), currentState(GameState::MainMenu), score(0) {
//    initialize();
//}
//
//void GameUIState::initialize() {
//    // ��������
//    if (!font.loadFromFile("arial.ttf")) {
//        std::cerr << "�޷����������ļ�����ȷ��arial.ttf����ȷλ��" << std::endl;
//    }
//
//    // ��ʼ��������ʾ
//    scoreText.setFont(font);
//    scoreText.setCharacterSize(24);
//    scoreText.setFillColor(sf::Color::White);
//    scoreText.setPosition(20, 20);
//    scoreText.setString("����: 0");
//
//    // ��ʼ����Ϸ�����ı�
//    gameOverText.setFont(font);
//    gameOverText.setString("��Ϸ����");
//    gameOverText.setCharacterSize(48);
//    gameOverText.setFillColor(sf::Color::Red);
//
//    finalScoreText.setFont(font);
//    finalScoreText.setCharacterSize(36);
//    finalScoreText.setFillColor(sf::Color::White);
//
//    // ��ʼ�������˵�
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
//    // 1. ��ʼ��Ϸ��ť
//    mainMenuButtons.push_back(createButton(
//        { 200, 50 }, { 300, 200 }, sf::Color::Green,
//        "1. ��ʼ��Ϸ",
//        [this]() { showScoreBoard = false; changeState(GameState::Playing); }
//    ));
//
//    // 2. �Ƿ�ϵͳ��ť
//    mainMenuButtons.push_back(createButton(
//        { 200, 50 }, { 300, 280 }, sf::Color::Blue,
//        "2. �Ƿ�ϵͳ",
//        [this]() { showScoreBoard = true; }
//    ));
//
//    // 3. ��ֹ��Ϸ��ť
//    mainMenuButtons.push_back(createButton(
//        { 200, 50 }, { 300, 360 }, sf::Color(255, 165, 0), // ��ɫ
//        "3. ��ֹ��Ϸ",
//        [this]() { changeState(GameState::Paused); }
//    ));
//
//    // 4. ������Ϸ��ť
//    mainMenuButtons.push_back(createButton(
//        { 200, 50 }, { 300, 440 }, sf::Color::Red,
//        "4. ������Ϸ",
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
//    // ������Ϸ��ť
//    pauseMenuButtons.push_back(createButton(
//        { 200, 50 }, { 300, 200 }, sf::Color::Green,
//        "������Ϸ",
//        [this]() { changeState(GameState::Playing); }
//    ));
//
//    // �������˵���ť
//    pauseMenuButtons.push_back(createButton(
//        { 200, 50 }, { 300, 280 }, sf::Color::Blue,
//        "���˵�",
//        [this]() { changeState(GameState::MainMenu); }
//    ));
//
//    // �˳���Ϸ��ť
//    pauseMenuButtons.push_back(createButton(
//        { 200, 50 }, { 300, 360 }, sf::Color::Red,
//        "�˳���Ϸ",
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
//    // ���¿�ʼ��ť
//    gameOverButtons.push_back(createButton(
//        { 200, 50 }, { 300, 300 }, sf::Color::Green,
//        "���¿�ʼ",
//        [this]() { resetScore(); changeState(GameState::Playing); }
//    ));
//
//    // �������˵���ť
//    gameOverButtons.push_back(createButton(
//        { 200, 50 }, { 300, 380 }, sf::Color::Blue,
//        "���˵�",
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
//            // ���ݵ�ǰ״̬��鲻ͬ�İ�ť
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
//    // ���·�����ʾ
//    scoreText.setString("����: " + std::to_string(score));
//
//    // �������Ϸ����״̬���������շ�����ʾ
//    if (currentState == GameState::GameOver) {
//        finalScoreText.setString("���յ÷�: " + std::to_string(score));
//
//        // ������ʾ��Ϸ�����ı�
//        sf::FloatRect textRect = gameOverText.getLocalBounds();
//        gameOverText.setOrigin(textRect.left + textRect.width / 2.0f,
//            textRect.top + textRect.height / 2.0f);
//        gameOverText.setPosition(window.getSize().x / 2.0f, 150);
//
//        // ������ʾ���շ���
//        textRect = finalScoreText.getLocalBounds();
//        finalScoreText.setOrigin(textRect.left + textRect.width / 2.0f,
//            textRect.top + textRect.height / 2.0f);
//        finalScoreText.setPosition(window.getSize().x / 2.0f, 220);
//    }
//}
//
//void GameUIState::render() {
//    // ���ݵ�ǰ״̬���Ʋ�ͬ��UI
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
//    // ���Ʊ���
//    sf::RectangleShape background(sf::Vector2f(window.getSize()));
//    background.setFillColor(sf::Color(50, 50, 100));
//    window.draw(background);
//
//    // ���Ʊ���
//    sf::Text title("�ܿ���Ϸ", font, 48);
//    title.setFillColor(sf::Color::White);
//    title.setPosition(300, 100);
//    window.draw(title);
//
//    // ���ư�ť
//    for (auto& button : mainMenuButtons) {
//        window.draw(button.rect);
//        window.draw(button.text);
//    }
//}
//
//void GameUIState::drawPauseMenu() {
//    // ���ư�͸������
//    sf::RectangleShape overlay(sf::Vector2f(window.getSize()));
//    overlay.setFillColor(sf::Color(0, 0, 0, 150));
//    window.draw(overlay);
//
//    // ������ͣ����
//    sf::Text title("��Ϸ����ͣ", font, 48);
//    title.setFillColor(sf::Color::White);
//    title.setPosition(300, 100);
//    window.draw(title);
//
//    // ���ư�ť
//    for (auto& button : pauseMenuButtons) {
//        window.draw(button.rect);
//        window.draw(button.text);
//    }
//}
//
//void GameUIState::drawGameOverMenu() {
//    // ���Ʊ���
//    sf::RectangleShape background(sf::Vector2f(window.getSize()));
//    background.setFillColor(sf::Color(100, 50, 50));
//    window.draw(background);
//
//    // ������Ϸ�����ı��ͷ���
//    window.draw(gameOverText);
//    window.draw(finalScoreText);
//
//    // ���ư�ť
//    for (auto& button : gameOverButtons) {
//        window.draw(button.rect);
//        window.draw(button.text);
//    }
//}
//
//void GameUIState::drawHUD() {
//    // ���Ʒ���
//    window.draw(scoreText);
//}
//
//void GameUIState::drawScoreBoard() {
//    // ���ư�͸������
//    sf::RectangleShape overlay(sf::Vector2f(window.getSize()));
//    overlay.setFillColor(sf::Color(0, 0, 0, 200));
//    window.draw(overlay);
//
//    // ���ƼǷְ����
//    sf::Text title("�Ƿ�ϵͳ", font, 36);
//    title.setFillColor(sf::Color::Yellow);
//    title.setPosition(350, 100);
//    window.draw(title);
//
//    // ���Ƹ߷ּ�¼
//    sf::Text scoresText;
//    scoresText.setFont(font);
//    scoresText.setCharacterSize(24);
//    scoresText.setFillColor(sf::Color::White);
//    scoresText.setPosition(300, 150);
//
//    std::string scoresStr = "��߷ּ�¼:\n";
//    for (size_t i = 0; i < highScores.size(); ++i) {
//        scoresStr += std::to_string(i + 1) + ". " + std::to_string(highScores[i]) + "\n";
//    }
//    scoresText.setString(scoresStr);
//    window.draw(scoresText);
//
//    // ���Ʒ��ذ�ť
//    Button backButton;
//    backButton.rect.setSize({ 150, 40 });
//    backButton.rect.setPosition(325, 400);
//    backButton.rect.setFillColor(sf::Color::Blue);
//
//    backButton.text.setFont(font);
//    backButton.text.setString("����");
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
//    sf::RenderWindow window(sf::VideoMode(800, 600), "�ܿ���Ϸ - �˵�");
//
//    // 1. ��������
//    sf::Font font;
//    if (!font.loadFromFile("arial.ttf")) {
//        // �������ʧ��
//    }
//
//    // 2. ����UIԪ�أ����⡢��ť��
//    sf::Text title("�ܿ���Ϸ", font, 50);
//    title.setPosition(300, 100);
//
//    sf::RectangleShape startButton(sf::Vector2f(200, 50));
//    startButton.setPosition(300, 300);
//    startButton.setFillColor(sf::Color::Green);
//
//    sf::Text startText("��ʼ��Ϸ", font, 30);
//    startText.setPosition(350, 310);
//
//    // ��ѭ��
//    while (window.isOpen()) {
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed) {
//                window.close();
//            }
//            // 3. ����ť����¼�
//            if (event.type == sf::Event::MouseButtonPressed) {
//                if (startButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
//                    // �л�����Ϸ����
//                }
//            }
//        }
//
//        // 4. ����UI
//        window.clear();
//        window.draw(title);
//        window.draw(startButton);
//        window.draw(startText);
//        window.display();
//    }
//    return 0;
//}