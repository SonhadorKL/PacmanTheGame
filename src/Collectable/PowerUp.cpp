#include "PowerUp.h"
#include "ResourceManager.h"

#include <iostream>

PowerUp::PowerUp(sf::Vector2i pos) : Collectable(pos, COLLECT_TYPE::POWER_UP) {
    sprite_.setTexture(ResourceManager::get_textures()["powerUp"]);
}

COLLECT_TYPE PowerUp::collected() {
    disable();
    return type_;
}