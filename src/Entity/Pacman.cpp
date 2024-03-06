#include "Pacman.h"
#include "ResourceManager.h"
#include <iostream>

Pacman::Pacman() : Entity(ResourceManager::get_textures()["pacman"], 3) {
    move_ = std::make_shared<PacmanMovement>(*this);
}

void Pacman::set_move_direction(sf::Event& event) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        move_->change_state(sf::Vector2i(-1, 0));
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        move_->change_state(sf::Vector2i(1, 0));
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        move_->change_state(sf::Vector2i(0, 1));
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        move_->change_state(sf::Vector2i(0, -1));
    }
}

void Pacman::update(Field& field, GhostManager& ghosts, Bonuses& bonuses) {
    move_->change_direction(field);
    set_rotation();
    move_->move(field);

    for (auto ghost : ghosts.get_ghosts()) {
        if (ghost->get_sprite().getGlobalBounds().contains(sprite_.getPosition())) {
            if (ghost->is_scared()) {
                ghost->get_hit();
                emit_signal(SIGNAL::GHOST_HIT);
            } else {
                get_hit();
            }
            break;
        }
    }
    check_bonuses(bonuses);
    
}

void Pacman::get_hit() {
    health_--;
    if (health_ > 0) {
        emit_signal(SIGNAL::HIT);
    }
}

bool Pacman::is_alive() {
    return health_ > 0;
}

void Pacman::check_bonuses(Bonuses& bonuses) {
    for (auto& bonus : bonuses.get_bonuses()) {
        if (bonus->is_active() && bonus->get_sprite().getGlobalBounds().contains(sprite_.getPosition())) {
            bonuses.was_eaten(bonus);
        }
    }
}
