#include "GameScene.h"
#include "Menu.h"
#include "Lost.h"

GameScene::GameScene(): game_interface_(cur_level_.get_field().get_map(), 3) {
    start();
}

void GameScene::start() {
    cur_level_.get_bonuses().add_observer(SIGNAL::FOOD_UP, this);
    cur_level_.get_bonuses().add_observer(SIGNAL::POWER_UP, this);
    cur_level_.get_pacman().add_observer(SIGNAL::GHOST_HIT, this);
    cur_level_.get_pacman().add_observer(SIGNAL::HIT, this);
    
    cur_level_.reset();
    wait_for_start();
    score_ = 0;
}

std::shared_ptr<Scene> GameScene::process(sf::RenderWindow& window, sf::Event& event) {
    if (be_ready_.check_timer()) {
        ready_ = true;
        game_interface_.show_ready(false);
        cur_level_.get_ghosts().continue_start();
    }

    if (!ready_) {
        return nullptr;
    }

    cur_level_.update(event);
    if (cur_level_.all_collected()) {
        cur_level_.reset();
        wait_for_start();
    }
    if (!cur_level_.is_playing()) {
        return std::make_shared<Lost>(score_);
    }
    return nullptr;
}

void GameScene::render(sf::RenderWindow & window) {
    cur_level_.render(window);
    game_interface_.render(window);
}

void GameScene::update_score(int delta_score) {
    score_ += delta_score;
    game_interface_.set_score(score_);
}

void GameScene::handle_event(SIGNAL id) {
    if (id == SIGNAL::FOOD_UP) {
        update_score(multiply_score(10));
    } else if (id == SIGNAL::GHOST_HIT) {
        update_score(multiply_score(200));
    } else if (id == SIGNAL::POWER_UP) {
        update_score(multiply_score(100));
    } else if (id == SIGNAL::HIT) {
        game_interface_.remove_hp();
        wait_for_start();
    }
}

int GameScene::multiply_score(int score) {
    return score + score / 2 * (cur_level_.get_level() - 1);
}

void GameScene::wait_for_start() {
    ready_ = false;
    game_interface_.set_level(cur_level_.get_level());
    game_interface_.show_ready(true);
    be_ready_.start_timer(ready_wait_time_);
    cur_level_.get_ghosts().stop_start();
}
