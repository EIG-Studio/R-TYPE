#include "SFML/Graphics/Texture.hpp"
#include "components.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <iostream>
#include <memory>

Renderer::Renderer(const std::string& texturePath)
{
    if (!m_texture.loadFromFile(texturePath)) {
        std::cerr << "Error: texture not found at " << texturePath << std::endl;
        exit(84);
    }
    m_sprite.setTexture(m_texture);
}

// Return a reference to the sprite
sf::Sprite& Renderer::getRenderer()
{
    return m_sprite;
}

sf::Texture Renderer::getTexture() const
{
    return m_texture;
}

void Renderer::setRenderer(const std::string& texturePath)
{
    if (!m_texture.loadFromFile(texturePath)) {
        std::cerr << "Error: texture not found" << std::endl;
        exit(84);
    }
    m_texture = sf::Texture(); // Resetting texture
    if (!m_texture.loadFromFile(texturePath)) {
        std::cerr << "Error: texture not found at " << texturePath << std::endl;
        exit(84);
    }
    m_sprite.setTexture(m_texture);
}