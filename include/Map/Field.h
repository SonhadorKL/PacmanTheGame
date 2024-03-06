#pragma once

#include <SFML/Graphics.hpp>

class Field {
public:
    
    Field();
    // Check if there is a wall on the given coords
    bool check_wall(const sf::Vector2i& coord);
    // Get the wall on current coords
    char get_wall(const sf::Vector2i& coord);

    const std::vector<std::string>& get_map();
    void render(sf::RenderWindow& window);
    
private:
    /* load map from file */
    void load_map();

    std::vector<std::string> map_;
};