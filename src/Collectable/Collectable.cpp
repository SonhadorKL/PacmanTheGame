#include "Collectable.h"
#include "General.h"

Collectable::Collectable(const sf::Vector2i& pos, COLLECT_TYPE type) : type_(type) {
    is_active_ = true;
    sprite_.setPosition(pacg::convert_coords(pos));
}

void Collectable::render(sf::RenderWindow& window) {
    window.draw(sprite_);
}

sf::Sprite& Collectable::get_sprite() {
    return sprite_;
}

COLLECT_TYPE Collectable::get_type() {
    return type_;
}

bool Collectable::is_active() {
    return is_active_;
}

void Collectable::activate() {
    is_active_ = true;
}

void Collectable::disable() {
    is_active_ = false;
}

void Bonuses::render(sf::RenderWindow& window) {
    for (auto& collect : bonuses_) {
        if (collect->is_active())
            collect->render(window);
    }
}

void Bonuses::restart() {
    for (auto& collect : bonuses_) {
        if (!collect->is_active()) {
            left_bonuses_++;
            collect->activate();
        }
    }
}

void Bonuses::was_eaten(std::shared_ptr<Collectable> bonus) {
    left_bonuses_--;
    bonus->collected();
    if (bonus->get_type() == COLLECT_TYPE::POWER_UP) {
        emit_signal(SIGNAL::POWER_UP);
    } else if (bonus->get_type() == COLLECT_TYPE::FOOD) {
        emit_signal(SIGNAL::FOOD_UP);
    }
}

bool Bonuses::all_collected() {
    return left_bonuses_ == 0;
}

void Bonuses::add_bonus(std::shared_ptr<Collectable> collect) {
    left_bonuses_++;
    bonuses_.push_back(collect);
}

std::list<std::shared_ptr<Collectable>>& Bonuses::get_bonuses() {
    return bonuses_;
}
