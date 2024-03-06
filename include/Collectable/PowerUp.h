#pragma once
#include "Collectable.h"

// Collectable which makes pacman invurable
class PowerUp : public Collectable {
public:
    PowerUp(sf::Vector2i pos);    
    COLLECT_TYPE collected() override;
};