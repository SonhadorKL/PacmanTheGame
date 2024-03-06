#include "Scene.h"
#include "Table.h"
#include "Button.h"

#include <SFML/Graphics.hpp>
#include <memory>

/*
Scene with user's leaderboard
*/
class ScoreTable : public Scene {
public:
    // Constructor which set the scene
    ScoreTable();

    // Back to menu on ESCAPE button
    std::shared_ptr<Scene> process(sf::RenderWindow& window, sf::Event& event);
    void render(sf::RenderWindow& window);

private:
    // Main table
    Table scores_;
    // Return color of the rows in the table
    sf::Color GetColor(size_t index);
};