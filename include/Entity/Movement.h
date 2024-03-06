#pragma once

#include <SFML/Graphics.hpp>

class Entity;
class Field;

/*
Manage every movement of entities:
save two states of entity cur_state and wanted_state and 
set the rules to process them
*/
class MovementManager {
public:
    MovementManager(Entity& entity);

    /* change stated */
    virtual bool change_direction(Field& field) = 0;
    /* move entity*/
    virtual void move(Field& field) = 0;
    virtual void set_position(const sf::Vector2i& pos_in_field) = 0;

    /* set new wanted direction */
    void change_state(const sf::Vector2i& new_state);
    sf::Vector2i get_state();

protected:
    Entity& entity_;

    sf::Vector2i cur_state_;
    sf::Vector2i next_state_;

    /* process case when entity out of window*/
    bool reverse_position();

    bool at_center(const sf::Vector2i& tile_coords);
    bool could_move_to_center(sf::Vector2i direction, sf::Vector2i tile_coords);
    sf::Vector2f get_center(sf::Vector2i tile_coords);

};

class PacmanMovement : public MovementManager {
public:
    PacmanMovement(Entity& entity);

    virtual bool change_direction(Field& field);
    virtual void move(Field& field);
    virtual void set_position(const sf::Vector2i& pos_in_field);

};

class GhostMovement : public MovementManager {
public:
    GhostMovement(Entity& entity);

    virtual bool change_direction(Field& field);
    virtual void move(Field& field);
    virtual void set_position(const sf::Vector2i& pos_in_field);

private:
    bool check_wall(const sf::Vector2i& coord, Field& field);

    sf::Vector2i cur_tile_;
};