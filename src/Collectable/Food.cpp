#include "Food.h"
#include "ResourceManager.h"
#include <iostream>

Food::Food(sf::Vector2i pos) : Collectable(pos, COLLECT_TYPE::FOOD) {
    sprite_.setTexture(ResourceManager::get_textures()["food"]);
}

COLLECT_TYPE Food::collected() {
    disable();
    return type_;
}