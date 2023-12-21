#include "components.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <iostream>

Renderer::Renderer(std::string texturePath)
{
    sf::Texture texture;
    if (!texture.loadFromFile(texturePath)) {
        std::cerr << "Error: texture not found" << std::endl;
        exit(84);
    }
    this->m_texture = texture;
    this->m_sprite.setTexture(this->m_texture);
}

sf::Sprite Renderer::getRenderer() const
{
    return this->m_sprite;

}

void Renderer::setRenderer(std::string &texturePath)
{
    sf::Sprite sprite;
    sf::Texture texture;
    if (!texture.loadFromFile(texturePath)) {
        std::cerr << "Error: texture not found" << std::endl;
        exit(84);
    }
    this->m_texture = texture;
    this->m_sprite.setTexture(this->m_texture);
}
