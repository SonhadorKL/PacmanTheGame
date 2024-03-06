#include "General.h"
#include <cmath>


sf::Vector2f pacg::convert_coords_centr(sf::Vector2i pos_in_field) {   
    return sf::Vector2f(pos_in_field.x * kTileSize + kTileSize / 2 + pacg::kMapStart.x,
                        pos_in_field.y * kTileSize + kTileSize / 2 + pacg::kMapStart.y);
}

sf::Vector2f pacg::convert_coords(sf::Vector2i pos_in_field) {
    return sf::Vector2f(pos_in_field.x * kTileSize + pacg::kMapStart.x,
                        pos_in_field.y * kTileSize + pacg::kMapStart.y);
}

sf::Vector2f pacg::get_mouse_pos(sf::RenderWindow& window) {
    int x_pos = (sf::Mouse::getPosition() - window.getPosition()).x;
    int y_pos = sf::Mouse::getPosition().y - window.getPosition().y - window_up_height;
    return sf::Vector2f(x_pos, y_pos);
}

sf::Vector2f pacg::get_vec2f(sf::Vector2i another) {
    return sf::Vector2f(another.x, another.y);
}

double pacg::get_angle(sf::Vector2f first, sf::Vector2f second) {
    double inner_prod = first.x * second.x + first.y * second.y; 
    return std::acos(inner_prod / get_len(first) / get_len(second));
}

double pacg::get_len(sf::Vector2f v) {
    return std::sqrt(v.x * v.x + v.y * v.y);
}

sf::Vector2i pacg::get_tile(const sf::Vector2f& coords) {
    size_t x_coord = static_cast<int>(coords.x - pacg::kMapStart.x) / pacg::kTileSize;
    size_t y_coord = static_cast<int>(coords.y - pacg::kMapStart.y) / pacg::kTileSize;
    return sf::Vector2i(x_coord, y_coord);
}

double pacg::get_random_range(double num, double range) {
    return num + -((float)(rand()) / (float)(RAND_MAX) * range);
}
