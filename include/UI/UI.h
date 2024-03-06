#pragma once

#include <SFML/Graphics.hpp>

/*
Basic class of UI objects.
Override functions get_boundaries(), get_position(), set_position(),
so arrange fuction will work.
*/
class UI {
public:
    virtual sf::FloatRect get_boundaries() const = 0;
    virtual sf::Vector2f get_position() const = 0;
    virtual void set_position(sf::Vector2f new_position) = 0;

    void arrange_at_left_corner(float offset_x = 0, float offset_y = 0);
    void arrange_at_right_corner(float offset_x = 0, float offset_y = 0);
    void arrange_at_center_down(float offset_y = 0);

    void arrange_down_at_left(const UI& other, float offset_x = 0, float offset_y = 0);
    void arrange_down_at_center(const UI& other, float offset_x = 0, float offset_y = 0);

    void arrange_up_at_left(const UI& other, float offset_x = 0, float offset_y = 0);
    void arrange_up_at_right(const UI& other, float offset_x = 0, float offset_y = 0);
    void arrange_up_at_center(const UI& other, float offset_x = 0, float offset_y = 0);

    void arrange_right_at_center(const UI& other, float offset_x = 0, float offset_y = 0);
};