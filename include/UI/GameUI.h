#pragma once

#include <vector>
#include <string>

#include "RemoveContainer.h"
#include "Label.h"
#include "ObserverPattern.h"
#include "Map.h"


/*
Class to display GUI of the gameplay.
*/
class GameUI {
public:
    GameUI(const std::vector<std::string>& map, int count = 0);

    void set_hp(int count);
    void set_score(int score);
    void set_level(int new_level);

    void show_ready(bool show);
    void remove_hp();

    void render(sf::RenderWindow& window);
private:
    Label score_;
    Label level_;
    Label be_ready_;

    RemoveContainer hearts_;
    Map map_;
};
