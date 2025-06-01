//// ScoreSystem.h
//#pragma once
//#include <SFML/Graphics.hpp>
//#include <fstream>
//
//class ScoreSystem {
//private:
//    int currentScore;
//    int highScore;
//    sf::Text scoreText;
//    std::string scoreFile = "scores.txt";
//
//public:
//    ScoreSystem(sf::Font& font) {
//        currentScore = 0;
//        highScore = 0;
//
//        scoreText.setFont(font);
//        scoreText.setCharacterSize(30);
//        scoreText.setFillColor(sf::Color::White);
//        scoreText.setPosition(20, 20);
//
//        loadHighScore();
//    }
//
//    void increaseScore() {
//        currentScore++;
//        if (currentScore > highScore) {
//            highScore = currentScore;
//        }
//        updateText();
//    }
//
//    void reset() {
//        currentScore = 0;
//        updateText();
//    }
//
//    void updateText() {
//        scoreText.setString("Score: " + std::to_string(currentScore) +
//            "\nHigh: " + std::to_string(highScore));
//    }
//
//    void draw(sf::RenderWindow& window) {
//        window.draw(scoreText);
//    }
//
//    void saveScore() {
//        std::ofstream file(scoreFile, std::ios::app);
//        if (file.is_open()) {
//            file << currentScore << "\n";
//            file.close();
//        }
//    }
//
//    void loadHighScore() {
//        std::ifstream file(scoreFile);
//        if (file.is_open()) {
//            int score;
//            while (file >> score) {
//                if (score > highScore) {
//                    highScore = score;
//                }
//            }
//            file.close();
//        }
//        updateText();
//    }
//
//    int getCurrentScore() const { return currentScore; }
//    int getHighScore() const { return highScore; }
//};
//
//
//
//
//
//// ScoreScreen.h
//#pragma once
//#include <SFML/Graphics.hpp>
//#include <vector>
//#include <algorithm>
//#include <fstream>
//
//class ScoreScreen {
//private:
//    sf::Text title;
//    std::vector<sf::Text> scoreTexts;
//    sf::RectangleShape backButton;
//    sf::Text backText;
//    std::string scoreFile = "scores.txt";
//
//public:
//    ScoreScreen(sf::Font& font) {
//        title.setFont(font);
//        title.setString("High Scores");
//        title.setCharacterSize(50);
//        title.setFillColor(sf::Color::White);
//        title.setPosition(300, 50);
//
//        backButton.setSize(sf::Vector2f(200, 50));
//        backButton.setPosition(300, 500);
//        backButton.setFillColor(sf::Color::Blue);
//
//        backText.setFont(font);
//        backText.setString("Back");
//        backText.setCharacterSize(30);
//        backText.setFillColor(sf::Color::White);
//        backText.setPosition(370, 510);
//    }
//
//    void loadScores(sf::Font& font) {
//        std::ifstream file(scoreFile);
//        std::vector<int> scores;
//        int score;
//
//        while (file >> score) {
//            scores.push_back(score);
//        }
//        file.close();
//
//        // 排序并取前10名
//        std::sort(scores.rbegin(), scores.rend());
//        if (scores.size() > 10) {
//            scores.resize(10);
//        }
//
//        scoreTexts.clear();
//        for (size_t i = 0; i < scores.size(); ++i) {
//            sf::Text text;
//            text.setFont(font);
//            text.setString(std::to_string(i + 1) + ". " + std::to_string(scores[i]));
//            text.setCharacterSize(30);
//            text.setFillColor(sf::Color::White);
//            text.setPosition(350, 150 + i * 40);
//            scoreTexts.push_back(text);
//        }
//    }
//
//    void draw(sf::RenderWindow& window) {
//        window.draw(title);
//        for (auto& text : scoreTexts) {
//            window.draw(text);
//        }
//        window.draw(backButton);
//        window.draw(backText);
//    }
//
//    bool isBackClicked(sf::Event::MouseButtonEvent& mouseEvent) {
//        return backButton.getGlobalBounds().contains(mouseEvent.x, mouseEvent.y);
//    }
//};