#include "core/utils/debug/debug_renderer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "core/render/shader.h"
#include "core/render/texture.h"
#include "core/render/quad.h"
#include "core/render/renderer.h"
#include "core/utils/texture_util.h"
#include "core/utils/debug/debug.h"
#include "core/application.h"
#include "fonts/font.h"

namespace Minecraft
{
    namespace DebugRender
    {
        // constants
        const int MAX_FONT_CHARS = 128;

        // forward declare internal functions
        void load_font_textures();


        struct DebugRenderData
        {
            Shader* shader;
            Quad quad;
            Texture font_textures[MAX_FONT_CHARS];

            DebugRenderData()
            {
                shader = new Shader("minecraft/res/shaders/debug_vshader.vs", "minecraft/res/shaders/debug_fshader.fs");
            }

            ~DebugRenderData() { delete shader; }
        };

        DebugRenderData* rd = nullptr;

        void init()
        {
            rd = new DebugRenderData();
            load_font_textures();
        }

        void load_font_textures()
        {
            for (int i = 0; i < MAX_FONT_CHARS; i++)
            {
                Texture& texture = rd->font_textures[i];
                texture.bind();
                texture.load_data(TextureUtil::load_image_from_int64(DefaultFont::font[i]), 8, 8, 4);
            }
        }

        void render_debug_item(Debug::DebugItem& item)
        {
            // Source of sloweness could be that each vao is being rendered individually, try something similar to how chunk mesh was created
            // will need to combine font textures into one large texture atlas

            // size variables
            int window_width = Application::get()->get_window()->get_width();
            int window_height = Application::get()->get_window()->get_height();

            float screen_char_width = (float)CHAR_WIDTH / (float)window_width;
            float screen_char_height = (float)CHAR_HEIGHT / (float)window_height;

            float screen_item_x = ((float)item.x / (float)window_width) * 2 - 1;
            float screen_item_y = ((float)item.y / (float)window_height) * 2 - 1;

            rd->shader->use();

            // draw characters
            glm::mat4 transform(1.0f);
            transform = glm::translate(transform, glm::vec3(screen_item_x, screen_item_y, 0.0f));

            for (int i = 0; i < item.text.length(); i++)
            {
                char c = item.text[i];

                rd->font_textures[c].bind();

                transform = glm::translate(transform, glm::vec3(screen_char_width * i, 0.0f, 0.0f));
                transform = glm::scale(transform, glm::vec3(screen_char_width, screen_char_height, 1.0f));
                rd->shader->load_mat4(transform, "transform");


                Render::render(rd->quad.get_vao(), RM_TRIANGLES);

                transform = glm::mat4(1.0f);
                transform = glm::translate(transform, glm::vec3(screen_item_x, screen_item_y, 0.0f));
            }
        }

        void render_debug_list(Debug::DebugList* list)
        {
            for (auto it = list->begin(); it != list->end(); it++)
            {
                Debug::DebugItem& item = *it;
                render_debug_item(item);
            }
        }

        void shutdown()
        {
            delete rd;
        }
    }
}