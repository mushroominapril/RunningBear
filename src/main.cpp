#include<SFML/Window.hpp>
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

int main()
{
	sf::RenderWindow window(sf::VideoMode({ 800,600 }), "My", sf::State::Windowed);
	window.setTitle("SFML WIndow");
	try {
		Bear bear("sprite_01.png", "sprite_02.png", "sprite_03.png", "sprite_04.png", "sprite_05.png", { 400, 300 });
		Map map("map1.png", 0.5f);
		// 初始化金币管理器
		GoldManager goldManager;
		if (!goldManager.loadTexture()) {
			std::cerr << "Failed to load gold textures!" << std::endl;
			return -1;
		}

		// 游戏状态变量
		int score = 0;//积分
		const float groundY = 450.0f; // 地面Y坐标
		const float gameSpeed = 200.0f; // 游戏基础速度

		ObstacleManager obstacleManager;
		if (!obstacleManager.loadTextures()) { return -1; }

		sf::Clock clock;
		/*       sf::Music backgroundMusic;
			   if (!backgroundMusic.openFromFile("background_music.ogg")) {
				   std::cerr << "Failed to load background music!" << std::endl;
				   return -1;
			   }
			   backgroundMusic.setLooping(true);
			   backgroundMusic.play();*/

		while (window.isOpen()) {
			//std::optional包装的时间对象,返回值存储在evet常量中
			//pollEvent用于检查并获取窗口的事件队列中的下一个事件
			float time = clock.restart().asSeconds();
			while (const std::optional event = window.pollEvent()) {
				if (event->is<sf::Event::Closed>()) {
					window.close();
				}
			}
			bear.update(time);
			map.update(bear.getPosition(), time);

			// 更新金币系统
			float bearWidth = bear.getBounds().size. x;
			goldManager.update(time, gameSpeed, groundY, bearWidth);

			// 检查金币收集//此处实现计分
			int collected = goldManager.checkCollection(bear.getBounds());
			if (collected > 0) {
				score += collected * 10;
				/*scoreText.setString("Score: " + std::to_string(score));*/
				std::cout << "Collected " << collected << " gold! Score: " << score << std::endl;
			}

			obstacleManager.update(time, 200.0f, bearWidth);

			if (obstacleManager.checkCollision(bear.getBounds())) {
				std::cout << "si!" << std::endl;
			}

			window.clear();
			map.draw(window);
			goldManager.draw(window);
			bear.draw(window);
			obstacleManager.draw(window);
			window.display();
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return -1;
	}
	return 0;
}