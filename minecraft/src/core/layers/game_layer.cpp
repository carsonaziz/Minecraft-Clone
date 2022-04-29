#include "core/layers/game_layer.h"

#include "core/render/vertex_array.h"
#include "core/render/buffer.h"
#include "core/render/shader.h"

namespace Minecraft
{
    void GameLayer::on_event(Event& event)
    {
        EventHandler handler(event);
        handler.handle_event<KeyPressedEvent>(std::bind(&GameLayer::test, this, std::placeholders::_1));
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
        };

        const char* vertex_source = R"(
            #version 330 core
            layout (location = 0) in vec3 aPos;

            void main()
            {
                gl_Position = vec4(aPos, 1.0);
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
        
        BufferLayout layout(0, 3);
        auto buffer = std::make_shared<VertexBuffer>(vertices, sizeof(vertices), layout);
        
        VertexArray vao;
        vao.add_vertex_buffer(buffer);

        Shader shader(vertex_source, fragment_source);
        shader.use();

        vao.bind();
        renderer->render(vao);
    }
}