#pragma once

#include <cstddef>
#include <string>
#include <SFML/Graphics.hpp>
#include "DataConfig.h"

/* Contains general constants and functions */
namespace pacg {
    const int kTileSize = 32;
    const int kMapWidth = 19;
    const int kMapHeight = 21;
    const sf::Vector2f kMapStart = {-static_cast<float>(kTileSize), 100};
    
    const int window_size_x = kTileSize * kMapWidth;
    const int window_size_y = kTileSize * kMapHeight + kMapStart.y;

    const int window_up_height = 38;
    const std::string kPathToMap = kPathToDir + "map.txt";

    const size_t table_max_size = 10;

    sf::Vector2f convert_coords_centr(sf::Vector2i pos_in_field);
    sf::Vector2f convert_coords(sf::Vector2i pos_in_field);

    sf::Vector2f get_mouse_pos(sf::RenderWindow& window);

    sf::Vector2f get_vec2f(sf::Vector2i another);
    double get_angle(sf::Vector2f first, sf::Vector2f second);
    double get_len(sf::Vector2f v);
    sf::Vector2i get_tile(const sf::Vector2f& coords);

    double get_random_range(double num, double range);
}

