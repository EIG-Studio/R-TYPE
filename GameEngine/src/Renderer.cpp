#include "components.hpp"

Renderer::Renderer(float rendererComponent)
{
    this->m_renderer = rendererComponent;
}

float Renderer::getRenderer() const
{
    return this->m_renderer;
}

void Renderer::setRenderer(float newRendererComponent)
{
    this->m_renderer = newRendererComponent;
}
