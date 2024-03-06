#include "RemoveContainer.h"
#include <iostream>
RemoveContainer::RemoveContainer(int count, sf::Texture& obj_texture) :
                                 Container(count, obj_texture) {}

void RemoveContainer::remove_left() {
    if (removed_from_left + removed_from_right + 1 > object_count_) {
        return;
    }
    ++removed_from_left;
}

void RemoveContainer::remove_right() {
    if (removed_from_left + removed_from_right + 1 > object_count_) {
        return;
    }
    ++removed_from_right;
}

void RemoveContainer::render(sf::RenderWindow & window) {
    for (int i = removed_from_left; i < objects_.size() - removed_from_right; ++i) {
        window.draw(*objects_[i]);
    }
}
