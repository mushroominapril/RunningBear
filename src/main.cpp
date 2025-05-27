#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/OpenGL.hpp>
#include<SFML/System.hpp>
#include<fstream>
#include<iostream>
#include"Bear.h"
#include"Map.h"
#include"Glod.h"
int main()
{
    sf::RenderWindow window(sf::VideoMode({ 800,600 }), "My",sf::State::Windowed);
    window.setTitle("SFML WIndow");
    try {
        Bear bear("sprite_01.png", "sprite_02.png", "sprite_03.png", "sprite_04.png", "sprite_05.png", { 400, 300 });
        Map map("map1.png", 0.5f);

        /*Glod glod1("glod.png", {500,400});
        Glod glod2("glod.png", { 500, 600});

        std::vector<Glod>glods;
        glods.push_back(glod1);
        glods.push_back(glod2);*/
   
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
            window.clear();
            map.draw(window);
            //glod1.draw(window);
            //// 调试：绘制红色矩形代替金币
            //sf::RectangleShape debugRect(sf::Vector2f(20, 20));
            //debugRect.setFillColor(sf::Color::Red);
            //debugRect.setPosition(glod1.getPosition());
            //window.draw(debugRect);
            bear.draw(window);
            window.display();
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }
    return 0;
}