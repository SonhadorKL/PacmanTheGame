#include "Table.h"
#include "ResourceManager.h"


Table::Table() : name_(ResourceManager::get_fonts()["pixel"]) {}

void Table::set_name(std::string name) {
    name_ = Label(ResourceManager::get_fonts()["pixel"]);
    name_.set_string(name);
    name_.get_text().setCharacterSize(50);
    name_.get_text().setFillColor(sf::Color::Blue);
    rebuild();
}

void Table::add_row(Label name) {
    if (rows_.size() == 0) {
        name.arrange_down_at_center(name_, 0, 10);
    } else {
        name.arrange_down_at_center(rows_.back(), 0, 10);
    }
    rows_.push_back(name);
    rebuild();
}

sf::FloatRect Table::get_boundaries() const {
    sf::Vector2f left_up;
    sf::Vector2f right_down;
    left_up.y = name_.get_position().y;
    if (rows_.size() != 0) {
        right_down.y = rows_.back().get_boundaries().height + rows_.back().get_position().y;
    } else {
        right_down.y = name_.get_position().y + name_.get_boundaries().height;
    }
    
    left_up.x = name_.get_position().x;
    right_down.x = name_.get_position().x + name_.get_boundaries().width;

    for (const auto& label : rows_) {
        left_up.x = std::min(left_up.x, label.get_position().x);
        right_down.x = std::max(right_down.x, label.get_position().x + label.get_boundaries().width);
    }
    sf::FloatRect rect;
    rect.left = left_up.x;
    rect.top = left_up.y;
    rect.width = right_down.x - left_up.x;
    rect.height = left_up.y - right_down.y;
    return rect;
}

sf::Vector2f Table::get_position() const {
    return name_.get_position();
}

void Table::set_position(sf::Vector2f new_position) {
    sf::FloatRect bound = get_boundaries();
    sf::Vector2f name_pos;
    name_pos.y = new_position.y;
    name_pos.x = new_position.x + bound.width / 2.f - name_.get_boundaries().width / 2.f;
    name_.set_position(new_position);
    rebuild();
}

void Table::render(sf::RenderWindow& window) {
    name_.render(window);
    for (auto& lab : rows_) {
        lab.render(window);
    }
}

void Table::rebuild() {
    size_t gap = 20;
    for (size_t i = 0; i < rows_.size(); ++i) {
        if (i == 0) {
            rows_.at(i).arrange_down_at_center(name_, 0, 2 * gap);
        } else {
            rows_.at(i).arrange_down_at_center(rows_[i - 1], 0, gap);
        }
    }
}
