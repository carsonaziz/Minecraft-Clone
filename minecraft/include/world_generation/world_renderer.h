#pragma once

#include <memory>
#include <unordered_map>

#include "world.h"
#include "core/render/shader.h"
#include "core/camera/camera_controller.h"

namespace Minecraft
{
    class WorldRenderer
    {
    private:
        std::shared_ptr<Shader> m_shader;

    public:
        WorldRenderer();
        ~WorldRenderer();

        void render(std::shared_ptr<World>& world, std::shared_ptr<CameraController>& camera_controller) const;
    };
}