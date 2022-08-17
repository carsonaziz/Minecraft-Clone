#include "core/render/texture.h"

#include <glad/glad.h>

#include "core/utils/texture_util.h"
#include "core/log.h"

namespace Minecraft
{
    Texture::Texture() : m_width(0), m_height(0), m_channels(0)
    {
        glGenTextures(1, &m_tex);
    }

    Texture::~Texture()
    {
        glDeleteTextures(1, &m_tex);
    }

    void Texture::bind() const
    {
        glBindTexture(GL_TEXTURE_2D, m_tex);
    }

    void Texture::unbind() const
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Texture::load_data(const std::string& filepath)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        unsigned char* data = TextureUtil::load_image(filepath, &m_width, &m_height, &m_channels);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
}