#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <set>
#include "Field.h"
#include "Movement.h"

/*
Basic class for movable characters  
*/
class Entity {
public:
    Entity(sf::Texture& texture, double initial_speed_ = 0);

    void render(sf::RenderWindow& window);
    /* stop movement */
    void stop();

    sf::Vector2f get_position();
    sf::Sprite& get_sprite();
    double get_speed();

    void set_position(sf::Vector2i pos);
    void set_rotation();
    void set_speed(double speed);

    virtual ~Entity() = default;

    std::shared_ptr<MovementManager> move_;
protected:
    sf::Sprite sprite_;
    double speed_;
    double start_speed_;

};