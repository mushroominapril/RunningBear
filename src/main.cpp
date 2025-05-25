#include<SFML/Window.hpp>
#include<fstream>
#include<iostream>
#include"Bear.h"
#include"Map.h"
int main()
{
    sf::RenderWindow window(sf::VideoMode({ 800,600 }), "My",sf::State::Windowed);

    window.setTitle("SFML WIndow");
    /*sprite.setPosition({400,300});*/
    try {
        Bear bear("sprite_01.png", { 400,300 });
        Map map("map1.png","map2.png", {800, 600});
        map.setScrollSpread(100.f);
        sf::Clock clock;
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
            window.clear();
            map.update(time, {400,300});//此处应该绑定玩家，但是我好像做不到，图片太像了，可以尝试暴露bear.position
            map.draw(window);
           
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