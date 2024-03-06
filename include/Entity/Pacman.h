#pragma once
#include "Entity.h"
#include "Ghost.h"
#include "Collectable.h"
#include "ObserverPattern.h"

/* Main character: can move, eat, sometimes kill */
class Pacman : public Entity, public Observable {
public:
    Pacman();
    // process user inputs
    void set_move_direction(sf::Event& event);
    void update(Field& field, GhostManager& ghosts, Bonuses& bonuses);

    void get_hit();
    bool is_alive();
private:
    int health_ = 3;

    // process collisions with collectables
    void check_bonuses(Bonuses& bonuses);
};