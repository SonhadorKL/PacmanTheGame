#include <iostream>

#include "UI.h"
#include "General.h"

void UI::arrange_at_left_corner(float offset_x, float offset_y) {
    this->set_position(sf::Vector2f(offset_x, offset_y));
}

void UI::arrange_at_right_corner(float offset_x, float offset_y) {
    float x_pos = pacg::window_size_x - this->get_boundaries().width - offset_x;
    float y_pos = offset_y;
    this->set_position(sf::Vector2f(x_pos, y_pos));
}

void UI::arrange_at_center_down(float offset_y) {
    float x_pos = pacg::window_size_x / 2 - this->get_boundaries().width / 2;
    float y_pos = offset_y;
    this->set_position(sf::Vector2f(x_pos, y_pos));
}

void UI::arrange_down_at_left(const UI& other, float offset_x, float offset_y) {
    sf::Vector2f new_pos;
    sf::FloatRect bound = other.get_boundaries(); 
    new_pos.x = bound.left + offset_x;
    new_pos.y = bound.top + bound.height + offset_y;

    this->set_position(new_pos);
}

void UI::arrange_down_at_center(const UI& other, float offset_x, float offset_y) {
    sf::Vector2f new_pos;
    sf::FloatRect other_bound = other.get_boundaries(); 
    sf::FloatRect obj_bound = this->get_boundaries(); 
    new_pos.x = other_bound.left + other_bound.width / 2 - obj_bound.width / 2 + offset_x;
    new_pos.y = other_bound.top + other_bound.height + offset_y;

    this->set_position(new_pos);
}

void UI::arrange_up_at_left(const UI & other, float offset_x, float offset_y) {
    sf::Vector2f new_pos;
    sf::FloatRect other_bound = other.get_boundaries(); 
    sf::FloatRect obj_bound = this->get_boundaries(); 
    new_pos.x = other_bound.left + offset_x;
    new_pos.y = other_bound.top - obj_bound.height - offset_y;

    this->set_position(new_pos);    
}

void UI::arrange_up_at_right(const UI & other, float offset_x, float offset_y) {
    sf::Vector2f new_pos;
    sf::FloatRect other_bound = other.get_boundaries(); 
    sf::FloatRect obj_bound = this->get_boundaries(); 
    new_pos.x = other_bound.left + other_bound.width - obj_bound.width - offset_x;
    new_pos.y = other_bound.top - obj_bound.height - offset_y;

    this->set_position(new_pos);    
}

void UI::arrange_up_at_center(const UI & other, float offset_x, float offset_y) {
    sf::Vector2f new_pos;
    sf::FloatRect other_bound = other.get_boundaries(); 
    sf::FloatRect obj_bound = this->get_boundaries(); 
    new_pos.x = other_bound.left + other_bound.width / 2 - obj_bound.width / 2 - offset_x;
    new_pos.y = other_bound.top - obj_bound.height - offset_y;

    this->set_position(new_pos);

}

void UI::arrange_right_at_center(const UI & other, float offset_x, float offset_y) {
    sf::Vector2f new_pos;
    sf::FloatRect other_bound = other.get_boundaries(); 
    sf::FloatRect obj_bound = this->get_boundaries();

    new_pos.x = other_bound.left + offset_x;
    new_pos.y = other_bound.top + other_bound.height / 2 - obj_bound.height / 2 - offset_y;

    this->set_position(new_pos); 
}
