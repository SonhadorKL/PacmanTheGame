#include "ResourceManager.h"
#include "DataConfig.h"

std::string get_path(const std::string& name) {
    return kPathToDir + name;
}

ResourceManager::ResourceManager() {
    // LOAD TEXTURES
    textures_["food"].loadFromFile(get_path("food.png"));
    textures_["pacman"].loadFromFile(get_path("pacman.png"));
    textures_["ghost"].loadFromFile(get_path("ghost.png"));
    textures_["scared"].loadFromFile(get_path("scared.png"));
    textures_["powerUp"].loadFromFile(get_path("powerUp.png"));
    textures_["heart"].loadFromFile(get_path("heart.png"));

    textures_["play_pressed"].loadFromFile(get_path("UI/Buttons/play_pressed.png"));
    textures_["play_unpressed"].loadFromFile(get_path("UI/Buttons/play_unpressed.png"));
    textures_["quit_unpressed"].loadFromFile(get_path("UI/Buttons/quit_unpressed.png"));
    textures_["quit_pressed"].loadFromFile(get_path("UI/Buttons/quit_pressed.png"));
    textures_["leader_unpressed"].loadFromFile(get_path("UI/Buttons/leader_unpressed.png"));
    textures_["leader_pressed"].loadFromFile(get_path("UI/Buttons/leader_pressed.png"));

    textures_["wall0"].loadFromFile(get_path("walls/wall0.png"));
    textures_["wall1"].loadFromFile(get_path("walls/wall1.png"));
    textures_["wall2"].loadFromFile(get_path("walls/wall2.png"));
    textures_["wall3"].loadFromFile(get_path("walls/wall3.png"));
    textures_["wall4"].loadFromFile(get_path("walls/wall4.png"));
    textures_["wall5"].loadFromFile(get_path("walls/wall5.png"));

    // LOAD FONTS
    fonts_["pixel"].loadFromFile(get_path("UI/pixel.ttf"));

    // LOAD SOUNDS
}

ResourceManager& ResourceManager::get_instance() {
    static ResourceManager instance;
    return instance;
}

std::map<std::string,sf::Texture>& ResourceManager::get_textures() {
    return get_instance().textures_;
}

std::map<std::string,sf::Font>& ResourceManager::get_fonts() {
    return get_instance().fonts_;
}

std::map<std::string,sf::SoundBuffer>& ResourceManager::get_sounds() {
    return get_instance().sounds_;
}

