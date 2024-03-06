#include "Game.h"
#include <iostream>

Game::Game(): game_interface_(cur_level_.get_field().get_map(), 3) {}

void Game::start() {
    is_lost = false;

    cur_level_.reset();
    cur_level_.get_bonuses().add_observer(SIGNAL::FOOD_UP, this);
    cur_level_.get_bonuses().add_observer(SIGNAL::POWER_UP, this);
    cur_level_.get_pacman().add_observer(SIGNAL::GHOST_HIT, this);
    cur_level_.get_pacman().add_observer(SIGNAL::HIT, this);
    score_ = 0;

}

void Game::play(sf::RenderWindow& window) {
    while (process(window)) {
        cur_level_.reset();
    }
}

bool Game::process(sf::RenderWindow& window) {
    while (window.isOpen() && cur_level_.is_playing()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
        }

        cur_level_.update(event);

        window.clear();
        cur_level_.render(window);
        game_interface_.render(window);
        window.display();

        if (cur_level_.all_collected()) {
            return true;
        }
    }
    return false;
}

void Game::update_score(int delta_score) {
    score_ += delta_score;
    game_interface_.set_score(score_);
}

void Game::handle_event(SIGNAL id) {
    if (id == SIGNAL::FOOD_UP) {
        update_score(10);
    } else if (id == SIGNAL::GHOST_HIT) {
        update_score(200);
    } else if (id == SIGNAL::POWER_UP) {
        update_score(200);
    } else if (id == SIGNAL::HIT) {
        game_interface_.remove_hp();
    }
}
