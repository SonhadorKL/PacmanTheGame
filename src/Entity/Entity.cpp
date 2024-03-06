#include "Entity.h"
#include "General.h"

Entity::Entity(sf::Texture& texture, double initial_speed_):
                start_speed_(initial_speed_) {
    speed_ = start_speed_;
    sprite_.setTexture(texture);
    sprite_.setOrigin(sprite_.getTextureRect().width / 2,
                      sprite_.getTextureRect().height / 2);
}


void Entity::render(sf::RenderWindow& window) {
    window.draw(sprite_);
}

void Entity::stop() {
    move_->change_state(sf::Vector2i(0, 0));
}

sf::Vector2f Entity::get_position() {
    return sprite_.getPosition();
}

double Entity::get_speed() {
    return speed_;
}

sf::Sprite& Entity::get_sprite() {
    return sprite_;
}

void Entity::set_position(sf::Vector2i pos) {
    return move_->set_position(pos);
}

void Entity::set_rotation() {
    if (move_->get_state().x == 1) {
        sprite_.setRotation(0);
    }
    if (move_->get_state().x == -1) {
        sprite_.setRotation(180);
    }
    if (move_->get_state().y == 1) {
        sprite_.setRotation(90);
    }
    if (move_->get_state().y == -1) {
        sprite_.setRotation(270);
    }
}

void Entity::set_speed(double speed) {
    start_speed_ = speed;
    speed_ = speed;
}
