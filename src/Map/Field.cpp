#include <fstream>

#include "Field.h"
#include "General.h"

#include <iostream>

Field::Field() {
    load_map();
}

bool Field::check_wall(const sf::Vector2i& coord) {
    return map_[coord.y][coord.x] == '#';
}

char Field::get_wall(const sf::Vector2i& coord) {
    return map_[coord.y][coord.x];
}


const std::vector<std::string>& Field::get_map() {
    return map_;
}

void Field::render(sf::RenderWindow& window) {}

void Field::load_map() {
    std::ifstream in(pacg::kPathToMap);
    std::string row;
    if (in.is_open()) {
        while (getline(in, row)) {
            map_.push_back(row);
        }
    }
    in.close();
}
