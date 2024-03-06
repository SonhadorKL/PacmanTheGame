#pragma once
#include "Container.h"

/* 
Updated version of container with ability to remove objects
*/
class RemoveContainer : public Container {
public:
    RemoveContainer(int count, sf::Texture& obj_texture);

    void remove_left();
    void remove_right();

    void render(sf::RenderWindow& window);
protected:
    int removed_from_left = 0;
    int removed_from_right = 0;
};