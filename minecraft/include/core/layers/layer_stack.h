#pragma once

#include <vector>

#include "layer.h"

namespace Minecraft
{
    class LayerStack
    {
    private:
        std::vector<Layer*> m_layers;

    public:
        LayerStack() {}
        ~LayerStack();

        void push(Layer* layer);
        void pop();

        std::vector<Layer*>::iterator begin() { return m_layers.begin(); }
        std::vector<Layer*>::iterator end() { return m_layers.end(); }
    };
}