#pragma once

#include "SFML/Graphics.hpp"
#include "Field.h"

/* 
Basic class of ghost's strategy
It responsible for the movement pattern of the ghost 
*/
class Strategy {
public:
    virtual sf::Vector2i choose_direction(sf::Vector2f pacman_pos,
                                  Field& map,
                                  sf::Vector2f cur_pos,
                                  sf::Vector2i cur_dir) = 0;
};

/* Random movement */
class RandomSearch : public Strategy {
public:
    virtual sf::Vector2i choose_direction(sf::Vector2f pacman_pos,
                                  Field& map,
                                  sf::Vector2f cur_pos,
                                  sf::Vector2i cur_dir) override;
};


/* Move to the pacman */
class Attack : public Strategy {
public:
    virtual sf::Vector2i choose_direction(sf::Vector2f pacman_pos,
                                  Field& map,
                                  sf::Vector2f cur_pos,
                                  sf::Vector2i cur_dir) override;
};

/* Run away from pacman */
class RunAway : public Strategy {
public:
    virtual sf::Vector2i choose_direction(sf::Vector2f pacman_pos,
                                  Field& map,
                                  sf::Vector2f cur_pos,
                                  sf::Vector2i cur_dir) override;
};