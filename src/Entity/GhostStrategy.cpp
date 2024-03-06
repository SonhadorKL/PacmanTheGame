#include "GhostStrategy.h"
#include "General.h"
#include "Ghost.h"

#include <vector>
#include <array>
#include <algorithm>
#include <numeric>

sf::Vector2i RandomSearch::choose_direction(sf::Vector2f pacman_pos,
                              Field& map,
                              sf::Vector2f cur_pos,
                              sf::Vector2i prev_tile_) {
    std::vector<sf::Vector2i> available_dir;
    sf::Vector2i cur_ind = pacg::get_tile(cur_pos);

    std::array<sf::Vector2i, 4> possible_dir = {
        sf::Vector2i(0, 1),
        sf::Vector2i(0, -1),
        sf::Vector2i(1, 0),
        sf::Vector2i(-1, 0)
    };

    // add all possible directions
    for (const sf::Vector2i& dir : possible_dir) {
        if (!map.check_wall(cur_ind + dir) && cur_ind + dir != prev_tile_) {
            available_dir.push_back(dir);
        }
    }

    if (available_dir.size() == 0) {
        // move to previous position
        return prev_tile_ - cur_ind;
    }

    // get random available direction
    return available_dir.at(rand() % available_dir.size());
}

sf::Vector2i Attack::choose_direction(sf::Vector2f pacman_pos,
                              Field& map,
                              sf::Vector2f cur_pos,
                              sf::Vector2i prev_tile_) {
    sf::Vector2f to_pac = pacman_pos - cur_pos;
    sf::Vector2i cur_ind = pacg::get_tile(cur_pos);

    std::array<sf::Vector2i, 4> pos_dir = {
        sf::Vector2i(0, 1),
        sf::Vector2i(0, -1),
        sf::Vector2i(1, 0),
        sf::Vector2i(-1, 0)
    };

    // sort directions to get the most accurate direction to pacman 
    std::sort(pos_dir.begin(), pos_dir.end(),
        [to_pac](sf::Vector2i v1, sf::Vector2i v2) {
            return pacg::get_angle(pacg::get_vec2f(v1), to_pac) < 
                pacg::get_angle(pacg::get_vec2f(v2), to_pac); 
        });
    
    
    // get the best direction
    for (auto& v : pos_dir) {
        if (!map.check_wall(cur_ind + v) && cur_ind + v != prev_tile_) {
            return v;
        }
    }
    // go to previous tile
    return prev_tile_ - cur_ind;
}

//remove copypaste
sf::Vector2i RunAway::choose_direction(sf::Vector2f pacman_pos,
                                       Field& map,
                                       sf::Vector2f cur_pos,
                                       sf::Vector2i prev_tile_) {
    sf::Vector2f to_pac = pacman_pos - cur_pos;
    sf::Vector2i cur_ind = pacg::get_tile(cur_pos);

    std::array<sf::Vector2i, 4> pos_dir = {
        sf::Vector2i(0, 1),
        sf::Vector2i(0, -1),
        sf::Vector2i(1, 0),
        sf::Vector2i(-1, 0)
    };

    std::sort(pos_dir.begin(), pos_dir.end(),
        [to_pac](sf::Vector2i v1, sf::Vector2i v2) {
            return pacg::get_angle(pacg::get_vec2f(v1), to_pac) >
                pacg::get_angle(pacg::get_vec2f(v2), to_pac); 
        });
    

    for (auto& v : pos_dir) {
        if (!map.check_wall(cur_ind + v) && cur_ind + v != prev_tile_) {
            return v;
        }
    }
    return prev_tile_ - cur_ind;
}
