#pragma once

#include "Scene.h"
#include "Label.h"
#include "Timer.h"

// Game over scene
class Lost : public Scene {
public:
    Lost(int score);

    virtual std::shared_ptr<Scene> process(sf::RenderWindow& window, sf::Event& event) override;
    virtual void render(sf::RenderWindow& window) override;
private:
    Label lost_;
    Label score_;
    Timer until_restart_;
};