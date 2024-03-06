#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include "Menu.h"
#include "ScoreTable.h"
#include "DataManager.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(pacg::window_size_x, pacg::window_size_y), "Pacman");
    window.setFramerateLimit(60);

    std::shared_ptr<Scene> cur_scene = std::make_shared<Menu>();
    std::shared_ptr<Scene> next_scene = nullptr;
    while (window.isOpen())
    {   
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();  
        }  
        next_scene = cur_scene->process(window, event);
        if (next_scene != nullptr) {
            cur_scene = next_scene;
        }
        window.clear();
        cur_scene->render(window);
        window.display();
    }
}