#pragma once

#include "Entity.h"
#include "GhostStrategy.h"
#include "ObserverPattern.h"

#include "Timer.h"
#include <memory>
#include <vector>

class GhostManager;

class Ghost : public Entity {
public:
    friend GhostManager;

    Ghost(const sf::Vector2i& start_pos, const sf::Vector2i& start_out_pos);
    void update(Field& map, const sf::Vector2f& pacman_position);

    void get_scared();
    void get_hit();
    void get_normal();

    void set_start_timer(double seconds);

    bool is_scared();

private:
    std::shared_ptr<Strategy> strategy_;
    sf::Vector2i start_position_;
    sf::Vector2i start_out_position_;

    double vision_radius_;

    Timer scared_timer_;
    Timer start_timer_;
    bool is_scared_ = false;

    void change_strategy(const sf::Vector2f& pacman_position);
};

/* Container for ghosts */
class GhostManager : public Observer {
public:
    friend Ghost;

    GhostManager() = default;
    void update(Field& map, const sf::Vector2f& pacman_position);
    void render(sf::RenderWindow& window);

    /* Create ghosts */
    void spawn(int count);

    /* Save positions of the ghosts*/
    void save_position(sf::Vector2i in_cage, sf::Vector2i out_of_cage);
   
    /* set ghosts to base positiong*/
    void restart();

    void stop_start();
    void continue_start();

    void set_speed(double speed);

    // handle event SIGNAL::POWER_UP
    void handle_event(SIGNAL id) override;

    std::vector<std::shared_ptr<Ghost>>& get_ghosts();

private:
    sf::Vector2i start_cage_pos_;
    sf::Vector2i start_out_of_cage_pos_;

    std::vector<std::shared_ptr<Ghost>> ghosts_;
};