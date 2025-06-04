#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<SFML/OpenGL.hpp>
#include<SFML/System.hpp>
#include<fstream>
#include<iostream>
#include"Bear.h"
#include"Map.h"
#include"Glod.h"
#include"GoldManager.h"
#include"Obstacle.h"
#include"UI.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode({ 800,600 }), "My", sf::State::Windowed);
	window.setTitle("SFML Window");
	try {
		Bear bear("sprite_01.png", "sprite_02.png", "sprite_03.png", "sprite_04.png", "sprite_05.png", { 400, 300 });
		Map map("map1.png", 100.f);

		// 初始化金币管理器
		GoldManager goldManager;
		if (!goldManager.loadTexture()) {
			std::cerr << "Failed to load gold textures!" << std::endl;
			return -1;
		}

		ObstacleManager obstacleManager;
		if (!obstacleManager.loadTextures()) {
			return -1;
		}

		sf::Font font;
		if (!font.openFromFile("C:/Windows/Fonts/arial.ttf")) {
			std::cerr << "Failed to load font!" << std::endl;
			return -1;
		}

		std::vector<sf::Texture> menuFrames;
		for (int i = 1; i <= 5; ++i) {
			sf::Texture texture;
			std::string filename = "menu_0" + std::to_string(i) + ".png";
			if (!texture.loadFromFile(filename)) {
				std::cerr << "Failed to load menu frame: " << filename << std::endl;
				return -1;
			}
			menuFrames.push_back(std::move(texture)); // 使用 move 避免复制
		}

		UIManager uiManager(font, menuFrames);

		// 游戏状态变量
		int score = 0;//积分
		bool isGameOver = false;
		bool isInGame = false;
		const float groundY = 450.0f; // 地面Y坐标
		const float gameSpeed = 200.0f; // 游戏基础速度

		sf::Clock clock;

		uiManager.setStartCallback([&]() {
			uiManager.showGameUI();
			isInGame = true;
			isGameOver = false;
			score = 0;
			bear.reset({ 400.f, 300.f });
			goldManager.reset();
			obstacleManager.reset();
			});

		uiManager.setExitCallback([&]() {
			window.close();
			});

		// 在游戏循环开始前显示主菜单
		uiManager.showMainMenu();

		/*       sf::Music backgroundMusic;
			   if (!backgroundMusic.openFromFile("background_music.ogg")) {
				   std::cerr << "Failed to load background music!" << std::endl;
				   return -1;
			   }
			   backgroundMusic.setLooping(true);
			   backgroundMusic.play();*/

		uiManager.setRestartCallback([&]() {
			isGameOver = false;
			score = 0;
			clock.restart();
			bear.reset({ 400, 300 });
			goldManager.reset();
			obstacleManager.reset();
			uiManager.setGameOver(false);
			uiManager.updateScore(0);
			});

		while (window.isOpen()) {
			//std::optional包装的时间对象,返回值存储在evet常量中
			//pollEvent用于检查并获取窗口的事件队列中的下一个事件
			float time = clock.restart().asSeconds();
			while (const std::optional event = window.pollEvent()) {
				if (event->is<sf::Event::Closed>()) {
					window.close();
				}
				uiManager.handleEvent(*event, window);
			}

			if (isInGame && !isGameOver) {
				bear.update(time);
				map.update(time);

				// 更新金币系统
				float bearWidth = bear.getBounds().size.x;

				// 检查金币收集//此处实现计分
				int collected = goldManager.checkCollection(bear.getBounds());
				if (collected > 0) {
					score += collected * 10;
					/*scoreText.setString("Score: " + std::to_string(score));*/
					std::cout << "Collected " << collected << " gold! Score: " << score << std::endl;
				}

				obstacleManager.update(time, 200.0f, bearWidth);

				if (obstacleManager.checkCollision(bear.getBounds())) {
					isGameOver = true;
					uiManager.setGameOver(true);
					std::cout << "Game Over!" << std::endl;
				}
			}

			uiManager.updateAnimation(time);

			window.clear();
			map.draw(window);
			goldManager.draw(window);
			bear.draw(window);
			obstacleManager.draw(window);
			uiManager.draw(window);
			window.display();
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return -1;
	}
	return 0;
}