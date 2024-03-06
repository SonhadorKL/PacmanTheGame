#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <map>
#include <string>

/*
Class to load and store all used data
*/
class ResourceManager {
private:
    std::map<std::string, sf::Texture> textures_;
    std::map<std::string, sf::Font> fonts_;
    std::map<std::string, sf::SoundBuffer> sounds_;

    ResourceManager();

    static ResourceManager& get_instance();

public:
    static std::map<std::string, sf::Texture>& get_textures();
    static std::map<std::string, sf::Font>& get_fonts();
    static std::map<std::string, sf::SoundBuffer>& get_sounds();
};