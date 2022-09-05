#pragma once

#include <string>

namespace Minecraft
{
    class Texture
    {
    private:
        unsigned int m_tex;
        int m_width, m_height, m_channels;

    public:
        Texture();
        ~Texture();

        void bind() const;
        void load_data(const std::string& filepath);
        void load_data(const unsigned char* data, int width, int height, int channels);
        void unbind() const;

        inline int get_width() const { return m_width; }
        inline int get_height() const { return m_height; }
        inline int get_channels() const { return m_channels; }
    };
}