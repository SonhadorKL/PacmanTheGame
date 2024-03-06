#include "Container.h"
#include <iostream>



Container::Container(int count, sf::Texture& obj_texture) {
    object_count_ = count;
    objects_texture_ = &obj_texture;
    rebuild();
}

void Container::set_object_count(int count) {
    object_count_ = count;
    rebuild();
}

void Container::set_texture(sf::Texture* texture) {
    objects_texture_ = texture;
    rebuild();
}

void Container::set_offset(float offset) {
    offset_ = offset;
    rebuild();
}


sf::FloatRect Container::get_boundaries() const {
    sf::FloatRect bound;
    bound.height = objects_texture_->getSize().y;
    bound.top = get_position().y;
    bound.left = get_position().x;
    bound.width = objects_texture_->getSize().x * object_count_ + offset_ * (object_count_ - 1);
    return bound;
}

sf::Vector2f Container::get_position() const {
    if (objects_.size() == 0) {
        return sf::Vector2f(0, 0);
    }
    return objects_[0]->getPosition();
}

void Container::set_position(sf::Vector2f new_position) {
    sf::Vector2f pos = new_position;
    for (size_t i = 0; i < objects_.size(); ++i) {
        objects_[i]->setPosition(pos);
        pos.x += objects_texture_->getSize().x + offset_;
    }
}

void Container::render(sf::RenderWindow& window) {
    for (auto& element : objects_) {
        window.draw(*element);
    }
}


void Container::rebuild() {
    sf::Vector2f pos = this->get_position();
    objects_.clear();
    for (size_t i = 0; i < object_count_; ++i) {
        std::shared_ptr<sf::Sprite> obj = std::make_shared<sf::Sprite>();
        obj->setTexture(*objects_texture_);        
        objects_.push_back(obj);
    }
    this->set_position(pos);
}
