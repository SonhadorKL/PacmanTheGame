#include "Button.h"
#include "General.h"
#include <iostream>


Button::Button(sf::Texture & pressed, sf::Texture & unpressed) {
    pressed_texture_ = &pressed;
    unpressed_texture_ = &unpressed;

    button_.setTexture(unpressed);
}

sf::FloatRect Button::get_boundaries() const {
    return button_.getGlobalBounds();
}

sf::Vector2f Button::get_position() const {
    return button_.getPosition();
}

void Button::set_position(sf::Vector2f new_position) {
    button_.setPosition(new_position);
}

void Button::control(sf::Event& event) {
    if (in_focus_ && event.type == sf::Event::MouseButtonReleased) {
        button_pressed();
    }
}


bool Button::update(sf::RenderWindow& window, sf::Event& event) {
    was_pressed_ = false;
    if (this->get_boundaries().contains(pacg::get_mouse_pos(window))) {
        in_focus_ = true;
        button_.setTexture(*pressed_texture_);
    } else {
        in_focus_ = false;
        button_.setTexture(*unpressed_texture_);
    }
    control(event);
    return was_pressed_;
}

void Button::render(sf::RenderWindow& window) {
    window.draw(button_);
}

void Button::button_pressed() {
    emit_signal(signal_);
    was_pressed_ = true;
}

void Button::set_signal(SIGNAL new_signal) {
    signal_ = new_signal;
}
