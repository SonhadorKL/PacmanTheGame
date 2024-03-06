#include "Label.h"

Label::Label(sf::Font& font) : font_(&font) {
    text_.setFont(*font_);
}

sf::FloatRect Label::get_boundaries() const {
    return text_.getGlobalBounds();
}

sf::Vector2f Label::get_position() const {
    return text_.getPosition();
}

void Label::set_position(sf::Vector2f new_position) {
    text_.setPosition(new_position);
}

void Label::set_string(const std::string& str) {
    text_.setString(str);
}

std::string Label::get_string() {
    return text_.getString();
}

void Label::set_size(int size) {
    text_.setCharacterSize(size);
}

sf::Text& Label::get_text() {
    return text_;
}

void Label::set_is_shown(bool is_show) {
    is_shown_ = is_show;
}

void Label::render(sf::RenderWindow& window) {
    if (is_shown_) {
        window.draw(text_);
    }
}
