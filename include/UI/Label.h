#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "UI.h"

/*
Label to display text
*/
class Label : public UI {
public:
    Label(sf::Font&);

    virtual sf::FloatRect get_boundaries() const override;
    virtual sf::Vector2f get_position() const override;
    virtual void set_position(sf::Vector2f new_position) override;
    
    void set_string(const std::string& str);
    std::string get_string();

    void set_size(int size);
    void set_is_shown(bool is_show);

    sf::Text& get_text();

    void render(sf::RenderWindow& window);
protected:
    sf::Font* font_;
    sf::Text text_;
    bool is_shown_ = true;
};