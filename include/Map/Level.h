#pragma once

#include <SFML/Graphics.hpp>

#include "Ghost.h"
#include "Pacman.h"
#include "Field.h"
#include "Collectable.h"

/*
Connect the main nodes of gameplay: pacman, ghosts, map
*/
class Level : public Observer {
public:
    Level();

    /* reset and go to next level */
    void reset();

    /* put entities at start positions */
    void relocate();

    void update(sf::Event& event);
    void render(sf::RenderWindow& window);

    bool is_playing();

    bool all_collected();

    Pacman& get_pacman();
    Bonuses& get_bonuses();
    Field& get_field();
    GhostManager& get_ghosts();

    int get_level();
private:

    Field field_;
    GhostManager ghosts_;
    Pacman player_;
    Bonuses bonuses_;

    int cur_level_ = 0;

    sf::Vector2i start_pacman_position_;
    sf::Vector2i start_ghost_cage_position_;
    sf::Vector2i start_ghost_out_cage_position_;

    virtual void handle_event(SIGNAL id) override;
    
    /* Set positions of everything according to the map */
    void map_processing();

    int get_ghost_count();
    double get_pacman_speed();
    double get_ghost_speed();
};
