#include "Ghost.h"
#include "ResourceManager.h"
#include "General.h"
#include <iostream>

Ghost::Ghost(const sf::Vector2i& start_pos, const sf::Vector2i& start_out_pos) :
                    Entity(ResourceManager::get_textures()["ghost"], 2),
                    vision_radius_(250),
                    start_position_(start_pos),
                    start_out_position_(start_out_pos)
                {
    move_ = std::make_shared<GhostMovement>(*this);
    move_->set_position(start_position_);

    strategy_ = std::make_shared<Attack>();
}

void Ghost::update(Field& map, const sf::Vector2f& pacman_position) {
    if (scared_timer_.check_timer()) {
        get_normal();
    }
    if (start_timer_.check_timer()) {
        move_->set_position(start_out_position_);
    }
    change_strategy(pacman_position);
    if(move_->change_direction(map)) { 
        move_->change_state(
                        strategy_->choose_direction(
                        pacman_position,
                        map,
                        get_position(),
                        move_->get_state()
                    )
                );
    }
    move_->move(map);
}

void Ghost::get_scared() {
    scared_timer_.start_timer(5);
    speed_ = start_speed_ / 2;
    sprite_.setTexture(ResourceManager::get_textures()["scared"]);
    is_scared_ = true;
}

void Ghost::get_hit() {
    get_normal();
    start_timer_.start_timer(3);
    move_->set_position(start_position_);
}

void Ghost::get_normal() {
    is_scared_ = false;
    speed_ = start_speed_;
    sprite_.setTexture(ResourceManager::get_textures()["ghost"]);
}

void Ghost::set_start_timer(double seconds) {
    start_timer_.start_timer(seconds);
}

bool Ghost::is_scared() {
    return is_scared_;
}

void Ghost::change_strategy(const sf::Vector2f& pacman_position) {
    if (is_scared_) {
        strategy_ = std::make_shared<RunAway>();
        return;
    }

    if (pacg::get_len(pacman_position - get_position()) < vision_radius_) {
        strategy_ = std::make_shared<Attack>();
    } else {
        strategy_ = std::make_shared<RandomSearch>();
    }
}

void GhostManager::update(Field& map, const sf::Vector2f& pacman_position) {
    for (auto ghost : ghosts_) {
        ghost->update(map, pacman_position);
    }
}

void GhostManager::render(sf::RenderWindow& window) {
    for (auto ghost : ghosts_) {
        ghost->render(window);
    }
}

void GhostManager::save_position(sf::Vector2i in_cage, sf::Vector2i out_of_cage) {
    start_cage_pos_ = in_cage;
    start_out_of_cage_pos_ = out_of_cage;
}

void GhostManager::restart() {
    for (size_t i = 0; i < ghosts_.size(); ++i) {
        ghosts_.at(i)->set_position(start_cage_pos_);
        ghosts_.at(i)->get_normal();
        ghosts_.at(i)->set_start_timer(i * 3);
    }
}

void GhostManager::stop_start() {
    for (size_t i = 0; i < ghosts_.size(); ++i) {
        ghosts_.at(i)->start_timer_.stop_timer();
    }
}

void GhostManager::continue_start() {
    for (size_t i = 0; i < ghosts_.size(); ++i) {
        ghosts_.at(i)->start_timer_.continue_timer();
    }
}

void GhostManager::set_speed(double speed) {
    for (size_t i = 0; i < ghosts_.size(); ++i) {
        ghosts_.at(i)->set_speed(pacg::get_random_range(speed, 0.25));
    }
}

void GhostManager::handle_event(SIGNAL id) {
    if (id == SIGNAL::POWER_UP) {
        for (auto& ghost : ghosts_) {
            ghost->get_scared();
        }
    }
}

std::vector<std::shared_ptr<Ghost>>& GhostManager::get_ghosts() {
    return ghosts_;
}

void GhostManager::spawn(int count) {

    for (int i = 0; i < count; ++i) {
        auto ghost = std::make_shared<Ghost>(start_cage_pos_, start_out_of_cage_pos_);
        ghost->set_start_timer(i * 3);
        ghosts_.push_back(ghost);
    }

    // int time_to_start = 0;
    // for (auto& position : start_positions_) {
    //     auto ghost = std::make_shared<Ghost>(position);
    //     ghost->set_start_timer(time_to_start);
    //     ghosts_.push_back(ghost);

    //     time_to_start += 3;
    // }
}
