/* header file for dealing with each states fonts and texture*/
#pragma once

#include <map>

#include <SFML/Graphics.hpp>

namespace Frosher{
class AssetManager{
public:
    AssetManager() {}
    ~AssetManager() {}

    void LoadTexture(std::string name, std::string fileName);
    sf::Texture &GetTexture(std::string name);

    void LoadFont(std::string name, std::string fileName);
    sf::Font &GetFont(std::string name);

private:
    std::map<std::string, sf::Texture>_texture;
    std::map<std::string, sf::Font>_fonts;
};
}
