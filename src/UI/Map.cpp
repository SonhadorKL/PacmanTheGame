#include "Map.h"
#include "ResourceManager.h"
#include "General.h"

#include <iostream>
Map::Map(const std::vector<std::string>& map) {
    for (int i = 0; i < static_cast<int>(map.size()); ++i) {
        for (int j = 0; j < static_cast<int>(map.at(i).size()); ++j) {
            if (map[i][j] == '#') {
                auto wall = process_texture(map, {j, i});
                wall->setPosition(pacg::convert_coords_centr({j, i}));
                walls_.push_back(wall);
            }
        }
    }
}

sf::FloatRect Map::get_boundaries() const {
    sf::FloatRect bound;
    bound.left = get_position().x;
    bound.top = get_position().y;
    if (walls_.size() == 0) {
        bound.height = 0;
        bound.width = 0;
    } else {
        auto wall0 = walls_[0]->getGlobalBounds();
        auto wall_end = walls_[walls_.size() - 1]->getGlobalBounds();
        bound.width = wall_end.left - wall0.left + wall_end.width;
        bound.height = wall_end.top - wall0.top + wall_end.height;
    }
    return bound;
}

sf::Vector2f Map::get_position() const {
    if (walls_.size() == 0) {
        return sf::Vector2f(0, 0);
    }
    sf::Vector2f pos;
    pos.x = walls_[0]->getGlobalBounds().left;
    pos.y = walls_[0]->getGlobalBounds().top;
    return pos;
}

void Map::set_position(sf::Vector2f new_position) {}

void Map::render(sf::RenderWindow & window) {
    for (auto a : walls_) {

        window.draw(*a);
    }
}

std::shared_ptr<sf::Sprite> Map::process_texture(const std::vector<std::string>& map,
                                                 sf::Vector2i pos) {
    int neig_count = 0;
    bool dir[4] = {false, false, false, false};
    if (pos.x - 1 >= 0 && map[pos.y][pos.x - 1] == '#') {
        dir[0] = true;
        ++neig_count;
    }

    if (pos.x + 1 < map[pos.y].size() && map[pos.y][pos.x + 1] == '#') {
        dir[2] = true;
        ++neig_count;
    }

    if (pos.y - 1 >= 0 && map[pos.y - 1][pos.x] == '#') {
        dir[1] = true;
        ++neig_count;
    }

    if (pos.y + 1 < map.size() && map[pos.y + 1][pos.x] == '#') {
        dir[3] = true;
        ++neig_count;
    }

    std::shared_ptr<sf::Sprite> wall = std::make_shared<sf::Sprite>();
    wall->setOrigin(pacg::kTileSize / 2, pacg::kTileSize / 2);
    int cur_dir = 0;
    if (neig_count == 4) {
        wall->setTexture(ResourceManager::get_textures()["wall4"]);
    } else if (neig_count == 1) {
        wall->setTexture(ResourceManager::get_textures()["wall5"]);
        for (int i = 0; i < 4; ++i) {
            if (dir[i]) {
                cur_dir = i;
                break;
            }
        }
    } else if (neig_count == 3) {
        wall->setTexture(ResourceManager::get_textures()["wall3"]);
        for (int i = 0; i < 4; ++i) {
            if (dir[i] && !dir[(i + 2) % 4]) {
                cur_dir = i;
                break;
            }
        }
    } else if (neig_count == 2) {
        if (dir[0] && dir[2] || dir[1] && dir[3]) {
            wall->setTexture(ResourceManager::get_textures()["wall1"]);
            for (int i = 0; i < 2; ++i) {
                if (dir[i]) {
                    cur_dir = i;
                    break;
                }
            }
        } else {
            wall->setTexture(ResourceManager::get_textures()["wall2"]);
            for (int i = 0; i < 4; ++i) {
                if (dir[i] && dir[(i + 1) % 4]) {
                    cur_dir = (i + 2) % 4;
                    break;
                }
            }
        }
    } else if (neig_count == 0) {
        wall->setTexture(ResourceManager::get_textures()["wall0"]);
    }
    wall->rotate(cur_dir * 90);
    return wall;
}