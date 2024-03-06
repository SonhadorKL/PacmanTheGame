#include "ScoreTable.h"
#include "ResourceManager.h"
#include "DataManager.h"
#include "Menu.h"
#include "General.h"

#include <memory>
#include <iostream>

ScoreTable::ScoreTable() {
    scores_.set_name("Leaderboard");
    std::shared_ptr<JsonManager> read_record(std::make_shared<JsonManager>()); 
    auto data = read_record->get_data(30);
    if (data.size() == 0) {
        Label l(ResourceManager::get_fonts()["pixel"]);
        l.set_string("It's empty :(");
        l.get_text().setFillColor(sf::Color::Cyan);
        scores_.add_row(l);
    }

    for (size_t i = 0; i < data.size(); ++i) {
        Label l(ResourceManager::get_fonts()["pixel"]);
        l.set_string(data[i]);
        l.get_text().setCharacterSize(24);
        l.get_text().setFillColor(GetColor(i));
        scores_.add_row(l);
    }

    scores_.arrange_at_center_down(100);
}

std::shared_ptr<Scene> ScoreTable::process(sf::RenderWindow & window, sf::Event & event) {
    if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape) {
        return std::make_shared<Menu>();
    }
    return nullptr;
}

void ScoreTable::render(sf::RenderWindow & window) {
    scores_.render(window);
}

sf::Color ScoreTable::GetColor(size_t index) {
    size_t color_count = 3;
    if (index < pacg::table_max_size / color_count) {
        return sf::Color::Green;
    }
    if (index < pacg::table_max_size * 2 / color_count) {
        return sf::Color::Yellow;
    }
    return sf::Color::Red;
}
