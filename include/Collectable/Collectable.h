#pragma once

#include <SFML/Graphics.hpp>
#include <list>
#include <memory>

#include "ObserverPattern.h"

enum class COLLECT_TYPE {
    FOOD, POWER_UP 
};

/*
Basic class for static pick-ups on the field
*/
class Collectable {
public:
    
    Collectable(const sf::Vector2i& pos, COLLECT_TYPE type);
    void render(sf::RenderWindow& window);

    sf::Sprite& get_sprite();
    COLLECT_TYPE get_type();

    void disable();
    void activate();
    bool is_active();

    virtual COLLECT_TYPE collected() = 0;

protected:
    bool is_active_;
    sf::Sprite sprite_;
    COLLECT_TYPE type_;
};

/*
Container for collectables
*/
class Bonuses : public Observable {
public:

    void render(sf::RenderWindow& window);
    void add_bonus(std::shared_ptr<Collectable> collect);
    
    /* make all collectables active */
    void restart();

    /* run to eat bonus */
    void was_eaten(std::shared_ptr<Collectable> bonus);
    bool all_collected();
    std::list<std::shared_ptr<Collectable>>& get_bonuses();

private:
    int left_bonuses_ = 0;
    std::list<std::shared_ptr<Collectable>> bonuses_;
};