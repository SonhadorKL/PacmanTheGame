#include "GameUI.h"
#include "ResourceManager.h"
#include "General.h"
#include <iostream>
GameUI::GameUI(const std::vector<std::string>& map, int count) :
                                map_(map),
                                level_(ResourceManager::get_fonts()["pixel"]),
                                hearts_(count, ResourceManager::get_textures()["heart"]),
                                score_(ResourceManager::get_fonts()["pixel"]), 
                                be_ready_(ResourceManager::get_fonts()["pixel"]) {
    hearts_.set_offset(5);
    hearts_.set_object_count(count);
    score_.set_string("0");
    score_.set_size(32);

    level_.get_text().setFillColor(sf::Color(150, 150, 150)); // Grey color
    level_.set_size(16);
    set_level(1);
    
    be_ready_.set_string("be ready");
    be_ready_.set_size(24);
    be_ready_.get_text().setFillColor(sf::Color::Yellow);
    be_ready_.arrange_up_at_center(map_, 0, 15);

    level_.arrange_up_at_left(map_, 30, 15);
    score_.arrange_up_at_left(level_, 0, 15);
    hearts_.arrange_up_at_right(map_, 30, 15);
   
}


void GameUI::set_hp(int count) {
    hearts_.set_object_count(count);
}

void GameUI::set_score(int score) {
    score_.set_string(std::to_string(score));
}

void GameUI::set_level(int new_level) {
    level_.set_string("lvl " + std::to_string(new_level));
}

void GameUI::show_ready(bool show) {
    be_ready_.set_is_shown(show);
}

void GameUI::remove_hp() {
    hearts_.remove_left();
}

void GameUI::render(sf::RenderWindow& window) {
    score_.render(window);
    hearts_.render(window);
    map_.render(window);
    level_.render(window);
    be_ready_.render(window);
}



