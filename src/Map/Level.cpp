#include "Level.h"
#include "Food.h"
#include "PowerUp.h"
#include <cmath>

Level::Level() {
    map_processing();

    player_.add_observer(SIGNAL::HIT, this);
    bonuses_.add_observer(SIGNAL::POWER_UP, &ghosts_);
}

void Level::reset() {
    ++cur_level_;
    bonuses_.restart();   
    
    player_.stop();
    player_.set_speed(get_pacman_speed());
    player_.set_position(start_pacman_position_);

    ghosts_ = GhostManager();
    ghosts_.save_position(start_ghost_cage_position_, start_ghost_out_cage_position_);
    ghosts_.spawn(get_ghost_count());
    ghosts_.set_speed(get_ghost_speed());
    ghosts_.restart();
}

void Level::relocate() {
    player_.set_position(start_pacman_position_);
    player_.stop();
    ghosts_.restart();
}

void Level::update(sf::Event& event) {
    player_.set_move_direction(event);
    player_.update(field_, ghosts_, bonuses_);
    ghosts_.update(field_, player_.get_position());
}

void Level::render(sf::RenderWindow& window) {
    player_.render(window);
    bonuses_.render(window);
    ghosts_.render(window);
}

bool Level::is_playing() {
    return player_.is_alive();
}

bool Level::all_collected() {
    return bonuses_.all_collected();
}

Pacman& Level::get_pacman() {
    return player_;
}

Bonuses& Level::get_bonuses() {
    return bonuses_;
}

Field & Level::get_field() {
    return field_;
}

GhostManager& Level::get_ghosts() {
    return ghosts_;
}

int Level::get_level() {
    return cur_level_;
}

void Level::handle_event(SIGNAL id) {
    if (id == SIGNAL::HIT) {
        relocate();
    }
}

void Level::map_processing() {
    const auto& map = field_.get_map();
    for (int i = 0; i < static_cast<int>(map.size()); ++i) {
        for (int j = 0; j < static_cast<int>(map.size()); ++j) {
            switch (map[i][j]) {
                case '#':
                {
                    break;
                }
                case 'P':
                {
                    start_pacman_position_ = {j, i};
                    break;
                }
                case 'G':
                {
                    start_ghost_cage_position_ = {j, i};
                    break;
                }
                case 'O':
                {
                    start_ghost_out_cage_position_ = {j, i};
                    break;
                }
                case '.':
                {
                    bonuses_.add_bonus(std::make_shared<Food>(Food({j, i})));
                    break;
                }
                case '^':
                {
                    bonuses_.add_bonus(std::make_shared<PowerUp>(PowerUp({j, i})));
                    break;
                }
            } 
        }
    }
}

int Level::get_ghost_count() {
    return 4;
}

double Level::get_pacman_speed() {
    return 4.0 / 7.0 * std::pow(cur_level_, 2.0 / 3.0) + 1.5;
}

double Level::get_ghost_speed() {
    return get_pacman_speed() * (cur_level_ / (1.0 + cur_level_));
}

