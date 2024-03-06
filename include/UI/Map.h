#pragma once

#include "UI.h"
#include <vector>
#include <string>
#include <memory>

/*
Map of the field.
*/
class Map : public UI {
public:
    Map(const std::vector<std::string>& map);
    virtual sf::FloatRect get_boundaries() const;
    virtual sf::Vector2f get_position() const;

    virtual void set_position(sf::Vector2f new_position);
    void render(sf::RenderWindow& window);
private:
    std::shared_ptr<sf::Sprite> process_texture(const std::vector<std::string>& map,
                                                 sf::Vector2i pos);

    std::vector<std::shared_ptr<sf::Sprite>> walls_;
};