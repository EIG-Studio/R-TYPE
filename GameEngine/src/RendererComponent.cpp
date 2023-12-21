#include "components.hpp"

RendererComponent::RendererComponent(float rendererComponent)
{
    this->m_rendererComponent = rendererComponent;
}

float RendererComponent::getRendererComponent() const
{
    return this->m_rendererComponent;
}

void RendererComponent::setRendererComponent(float newRendererComponent)
{
    this->m_rendererComponent = newRendererComponent;
}
