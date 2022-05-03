#include "core/layers/game_layer.h"

#include <glm/glm.hpp>

#include "core/render/vertex_array.h"
#include "core/render/buffer.h"
#include "core/render/shader.h"

namespace Minecraft
{
    GameLayer::GameLayer() : Layer()
    {
        m_camera_controller = std::make_shared<CameraController>(glm::vec3(0, 0, 1));
    }

    void GameLayer::on_event(Event& event) {}

    void GameLayer::update()
    {
        m_camera_controller->update();
    }

    void GameLayer::render(std::shared_ptr<Renderer>& renderer)
    {
        float vertices[] = {
            0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            1.0f,  1.0f, 0.0f,
            0.0f, 0.0f, 0.0f,
            1.0f,  1.0f, 0.0f,
            1.0f, 0.0f, 0.0f,

            1.0f, 0.0f, -1.0f,
            1.0f, 1.0f, -1.0f,
            0.0f,  1.0f, -1.0f,
            1.0f, 0.0f, -1.0f,
            0.0f,  1.0f, -1.0f,
            0.0f, 0.0f, -1.0f,

            0.0f, 0.0f, -1.0f,
            0.0f, 1.0f, -1.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, -1.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f,

            
        };

        const char* vertex_source = R"(
            #version 330 core
            layout (location = 0) in vec3 aPos;

            uniform mat4 model;
            uniform mat4 view;
            uniform mat4 projection;

            void main()
            {
                gl_Position = projection * view * model * vec4(aPos, 1.0);
                // gl_Position =  view * model * vec4(aPos, 1.0);
            }
            )";

        const char* fragment_source = R"(
            #version 330 core
            out vec4 FragColor;

            void main()
            {
                FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
            }
            )";
        
        // Square
        BufferLayout layout(0, 3);
        auto buffer = std::make_shared<VertexBuffer>(vertices, sizeof(vertices), layout);
        
        VertexArray vao;
        vao.add_vertex_buffer(buffer);

        //////////// Matrices ////////////
        glm::mat4 model = glm::mat4(1.0f);

        Shader shader(vertex_source, fragment_source);
        shader.use();
        shader.load_mat4(model, "model");
        shader.load_mat4(m_camera_controller->get_camera()->get_view(), "view");
        shader.load_mat4(m_camera_controller->get_camera()->get_projection(), "projection");

        vao.bind();
        renderer->render(vao);
    }
}