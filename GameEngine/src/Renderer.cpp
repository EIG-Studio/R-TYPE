#include "SFML/Graphics/Texture.hpp"
#include "components.hpp"

#include <SFML/Graphics/Sprite.hpp>

#include <iostream>

Renderer::Renderer(const std::string& texturePath)
{
    this->m_path = texturePath;
    if (!m_texture.loadFromFile(this->m_path )) {
        std::cerr << "Error: texture not found at " << this->m_path  << std::endl;
        exit(84);
    }
    m_sprite.setTexture(m_texture);
}

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
    this->m_path = texturePath;
    if (!m_texture.loadFromFile(this->m_path )) {
        std::cerr << "Error: texture not found" << std::endl;
        exit(84);
    }
    m_texture = sf::Texture();
    if (!m_texture.loadFromFile(this->m_path )) {
        std::cerr << "Error: texture not found at " << this->m_path  << std::endl;
        exit(84);
    }
    m_sprite.setTexture(m_texture);
}
