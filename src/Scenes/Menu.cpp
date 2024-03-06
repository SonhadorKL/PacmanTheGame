#include "Menu.h"
#include "ResourceManager.h"
#include "GameScene.h"
#include "ScoreTable.h"


Menu::Menu(): play_(ResourceManager::get_textures()["play_unpressed"],
                    ResourceManager::get_textures()["play_pressed"]),
              quit_(ResourceManager::get_textures()["quit_unpressed"],
                    ResourceManager::get_textures()["quit_pressed"]),
              leader_board_(ResourceManager::get_textures()["leader_pressed"],
                            ResourceManager::get_textures()["leader_unpressed"]),
              menu_(ResourceManager::get_fonts()["pixel"]) {
    menu_.set_string("Menu");
    menu_.set_size(72);
    menu_.get_text().setFillColor(sf::Color::Yellow);
    
    menu_.arrange_at_center_down(100);
    play_.arrange_down_at_center(menu_, 0, 50);
    leader_board_.arrange_down_at_center(play_, 0, 25);
    quit_.arrange_down_at_center(leader_board_, 0, 25);

}

std::shared_ptr<Scene> Menu::process(sf::RenderWindow & window, sf::Event & event) {
    if (quit_.update(window, event) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        window.close();
        return nullptr;
    }
    if (play_.update(window, event)) {
        return std::make_shared<GameScene>();
    }
    if (leader_board_.update(window, event)) {
        return std::make_shared<ScoreTable>();
    }    
    return nullptr;
}

void Menu::render(sf::RenderWindow& window) {
    menu_.render(window);
    quit_.render(window);
    leader_board_.render(window);
    play_.render(window);
}
