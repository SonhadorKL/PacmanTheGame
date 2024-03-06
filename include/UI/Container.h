#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "UI.h"

/*
Container of sprites 
*/
class Container : public UI {
public:
    Container(int count, sf::Texture& obj_texture);
    
    // Replace count of objects
    void set_object_count(int count);
    // Set texture to objects
    void set_texture(sf::Texture* texture);
    // Set offset between objects
    void set_offset(float offset);
    
    virtual sf::FloatRect get_boundaries() const override;
    virtual sf::Vector2f get_position() const override;
    virtual void set_position(sf::Vector2f new_position) override;
    
    void render(sf::RenderWindow& window);
    void rebuild();
protected:

    std::vector<std::shared_ptr<sf::Sprite>> objects_;
    sf::Texture* objects_texture_;
    int object_count_ = 0;
    float offset_ = 0;
};
