#pragma once

#include "Level.h"
#include "ObserverPattern.h"
#include "GameUI.h"

/* Class to run the whole game */
class Game : public Observer {
public:
    Game();

    /* prepare the game */
    void start();

    /* Play the game. Run after start */
    void play(sf::RenderWindow& window);
    
    /* process the gameplay */
    bool process(sf::RenderWindow& window);

    void update_score(int delta_score);

    void handle_event(SIGNAL id) override;
private:
    Level cur_level_;
    int score_;
    bool is_lost;

    GameUI game_interface_;
};