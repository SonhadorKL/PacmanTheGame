#pragma once

#include <SFML/Graphics.hpp>
#include "UI.h"
#include "ObserverPattern.h"

/*
Just a button. Check update function to check if button was pressed
*/
class Button : public UI, public Observable {
public:
    Button(sf::Texture& pressed, sf::Texture& unpressed);

    virtual sf::FloatRect get_boundaries() const override;
    virtual sf::Vector2f get_position() const override;
    virtual void set_position(sf::Vector2f new_position) override;

    void control(sf::Event& event);
    // Return True if button was pressed
    bool update(sf::RenderWindow& window, sf::Event& event);
    // Print button
    void render(sf::RenderWindow& window);
    // Set signal which should be emitted on pressed
    void set_signal(SIGNAL new_signal);
protected:

    void button_pressed();

    sf::Sprite button_;
    sf::Texture* unpressed_texture_;
    sf::Texture* pressed_texture_;
    SIGNAL signal_ = SIGNAL::BUTTON_PRESSED;

    bool in_focus_ = false;
    bool was_pressed_ = false;
};

