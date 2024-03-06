#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

// Interaface of the scene class
class Scene {
public:
    // Run a scene. Return a next scene to which switch
    virtual std::shared_ptr<Scene> process(sf::RenderWindow& window, sf::Event& event) = 0;
    // Print a scene
    virtual void render(sf::RenderWindow& window) = 0;
};