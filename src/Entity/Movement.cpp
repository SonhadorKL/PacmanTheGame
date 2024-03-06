#include "Movement.h"
#include "Entity.h"
#include "Ghost.h"
#include "General.h"
#include <iostream>
#include <cmath>


MovementManager::MovementManager(Entity& entity_) : entity_(entity_),
                                                    cur_state_(0, 0),
                                                    next_state_(0, 0) 
{}

void MovementManager::change_state(const sf::Vector2i& new_state) {
    next_state_ = new_state;
}

sf::Vector2i MovementManager::get_state() {
    return cur_state_;
}

bool MovementManager::reverse_position() {
    sf::Vector2f pos = entity_.get_position();
    sf::Vector2i cur_tile = pacg::get_tile(pos);
    double edge = pacg::kMapWidth * pacg::kTileSize + pacg::kTileSize / 2;
    if (pos.x < -pacg::kTileSize / 2) {
        entity_.set_position({pacg::kMapWidth + 1, cur_tile.y});
        return true;
    }
    if (pos.x > edge) {
        entity_.set_position({0, cur_tile.y});
        return true;
    }
    return false;
}

bool MovementManager::at_center(const sf::Vector2i& tile_coords) {
    sf::Vector2f tile_center = pacg::convert_coords_centr(tile_coords);
    return std::abs(tile_center.x - entity_.get_position().x) < 2 &&
           std::abs(tile_center.y - entity_.get_position().y) < 2;
}

bool MovementManager::could_move_to_center(sf::Vector2i direction, sf::Vector2i tile_coords) {
    if (direction.x == 1) {
        return entity_.get_position().x < get_center(tile_coords).x;
    }
    if (direction.x == -1) {
        return entity_.get_position().x > get_center(tile_coords).x;
    }
    if (direction.y == 1) {
        return entity_.get_position().y < get_center(tile_coords).y;
    }
    if (direction.y == -1) {
        return entity_.get_position().y > get_center(tile_coords).y;
    }
    return false;
}

sf::Vector2f MovementManager::get_center(sf::Vector2i tile_coords) {
    return pacg::convert_coords_centr(tile_coords);
}

PacmanMovement::PacmanMovement(Entity& entity) : MovementManager(entity) 
{}

bool PacmanMovement::change_direction(Field& field) {
    sf::Vector2i cur_tile = pacg::get_tile(entity_.get_position());
    sf::Vector2i next_tile_cur = cur_state_ + cur_tile;
    sf::Vector2i next_tile_prev = next_state_ + cur_tile;

    sf::Vector2i opposite_direction = cur_state_;
    opposite_direction *= -1;
    bool is_opposite = opposite_direction == next_state_;

    bool is_no_wall_cur = !field.check_wall(next_tile_cur);

    bool is_not_at_center_cur = could_move_to_center(cur_state_, cur_tile);
    bool is_no_wall_wanted = !field.check_wall(next_tile_prev);

    if (is_opposite || at_center(cur_tile) && is_no_wall_wanted) {
        cur_state_ = next_state_;
    }
    return true;
}

void PacmanMovement::move(Field & field) {
    reverse_position();
    sf::Vector2i cur_tile = pacg::get_tile(entity_.get_position());
    sf::Vector2i next_tile_cur = cur_state_ + cur_tile;

    bool is_no_wall_cur = !field.check_wall(next_tile_cur);
    bool is_not_at_center_cur = could_move_to_center(cur_state_, cur_tile);

    if (is_no_wall_cur || is_not_at_center_cur) {
        entity_.get_sprite().move(cur_state_.x * entity_.get_speed(),
                                 cur_state_.y * entity_.get_speed());    
    } else {
        entity_.set_position(cur_tile);
    }
}

void PacmanMovement::set_position(const sf::Vector2i& pos_in_field) {
    entity_.get_sprite().setPosition(pacg::convert_coords_centr(pos_in_field));
}


GhostMovement::GhostMovement(Entity& entity) : 
                    MovementManager(entity)
{}

bool GhostMovement::change_direction(Field& field) {
    sf::Vector2i next_tile = next_state_ + cur_tile_;
    if (check_wall(next_tile, field)) {
        next_state_ = sf::Vector2i(0, 0);
        return true;
    }
    if (at_center(next_tile)) {
        cur_state_ = cur_tile_;
        cur_tile_ = next_tile;
        return true;
    }
    return false;
}

void GhostMovement::move(Field& field) {
    if (reverse_position()) {
        cur_tile_ = pacg::get_tile(entity_.get_position());
    }
    entity_.get_sprite().move(next_state_.x * entity_.get_speed(),
                            next_state_.y * entity_.get_speed());   
}

void GhostMovement::set_position(const sf::Vector2i& pos_in_field) {
    entity_.get_sprite().setPosition(pacg::convert_coords_centr(pos_in_field));
    cur_tile_ = pos_in_field;
}

bool GhostMovement::check_wall(const sf::Vector2i& coord, Field& field) {
    if (field.get_wall(coord) == '#' || field.get_wall(coord) == 'D') {
        return true;
    }
    return false;
}
