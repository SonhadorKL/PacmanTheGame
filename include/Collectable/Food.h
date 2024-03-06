#pragma once

#include "Collectable.h"

/* Collectables which pacman have to pick up to go to the next level*/
class Food : public Collectable {
public:
    Food(sf::Vector2i pos);    
    COLLECT_TYPE collected() override;
};