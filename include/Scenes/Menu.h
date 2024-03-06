#pragma once

#include "Scene.h"
#include "Label.h"
#include "Button.h"

// Basic menu
class Menu : public Scene {
public:
    Menu();
    virtual std::shared_ptr<Scene> process(sf::RenderWindow& window, sf::Event& event) override;
    void render(sf::RenderWindow& window) override;

private:
    Button play_;
    Button quit_;
    Button leader_board_;
    Label menu_;
};