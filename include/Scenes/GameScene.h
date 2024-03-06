#include "Scene.h"

#pragma once

#include "Level.h"
#include "ObserverPattern.h"
#include "GameUI.h"
#include "Scene.h"
#include "Timer.h"

// Gameplay scene
class GameScene : public Observer, public Scene {
public:
    GameScene();

    virtual std::shared_ptr<Scene> process(sf::RenderWindow& window, sf::Event& event) override;
    virtual void render(sf::RenderWindow& window) override;
    
    void update_score(int delta_score);
    void handle_event(SIGNAL id) override;
private:
    Level cur_level_;
    Timer be_ready_;
    bool ready_;
    float ready_wait_time_ = 3;
    int score_;
    GameUI game_interface_;

    void start();
    int multiply_score(int score);
    void wait_for_start();

};