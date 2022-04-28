#include "core/layers/layer_stack.h"

namespace Minecraft
{
    LayerStack::~LayerStack()
    {
        for (auto layer : m_layers)
        {
            delete layer;
        }
    }

    void LayerStack::push(Layer* layer)
    {
        m_layers.insert(m_layers.begin(), layer);
    }

    void LayerStack::pop()
    {
        m_layers.erase(m_layers.begin());
    }
}