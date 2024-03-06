#include "Lost.h"
#include "ResourceManager.h"
#include "General.h"
#include "Menu.h"
#include "DataManager.h"

#include <string>
#include <memory>


Lost::Lost(int score) : lost_(ResourceManager::get_fonts()["pixel"]),
                        score_(ResourceManager::get_fonts()["pixel"]) {
    lost_.set_string("YOU DIED");
    lost_.set_size(72);
    lost_.get_text().setFillColor(sf::Color::Red);
    lost_.arrange_at_center_down(pacg::window_size_y / 3);

    until_restart_.start_timer(3);

    score_.set_string("Your score: " + std::to_string(score));
    score_.set_size(36);
    score_.get_text().setFillColor(sf::Color(160, 160, 160));
    std::shared_ptr<WriteRecord> writer = std::make_shared<JsonManager>();
    if (writer->set_data(score)) {
        score_.set_string("New record: " + std::to_string(score) + "!");
    }
    score_.arrange_down_at_center(lost_, 0, 30);
}

std::shared_ptr<Scene> Lost::process(sf::RenderWindow & window, sf::Event & event) {
    if (until_restart_.check_timer() ||
        event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape) {
        return std::make_shared<Menu>();
    }
    return nullptr;
}

void Lost::render(sf::RenderWindow & window) {
    lost_.render(window);
    score_.render(window);
}
