#include "SFML/Graphics/Texture.hpp"
#include "components.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <iostream>
#include <memory>

Renderer::Renderer(std::string texturePath)
{
    if (!m_texture.loadFromFile(texturePath)) {
        std::cerr << "Error: texture not found at " << texturePath << std::endl;
        exit(84);
    }

    this->m_sprite.setTexture(this->m_texture);
}

sf::Sprite Renderer::getRenderer() const
{
    return this->m_sprite;

}

sf::Texture Renderer::getTexture() const
{
    return this->m_texture;

}

void Renderer::setRenderer(std::string &texturePath)
{
    sf::Texture texture;
    if (!texture.loadFromFile(texturePath)) {
        std::cerr << "Error: texture not found" << std::endl;
        exit(84);
    }
    this->m_texture = texture;
    this->m_sprite.setTexture(this->m_texture);
}
