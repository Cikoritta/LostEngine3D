#include "Texture.hpp"

#include "../Debug/Debug.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


void le::Texture2D::loadFromFile(const std::string& filePath)
{
    glGenTextures(1, &m_textureID);
    glBindTexture(GL_TEXTURE_2D, m_textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);

    int width, height, nrChannels;
    unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);

    if (data)
    {
        GLenum internalFormat, format;

        if (nrChannels == 1) {
            internalFormat = GL_RED;
            format = GL_RED;
        }
        else if (nrChannels == 3) {
            internalFormat = GL_RGB8;
            format = GL_RGB;
        }
        else if (nrChannels == 4) {
            internalFormat = GL_RGBA8;
            format = GL_RGBA;
        }
        else {
            LOG_WARN("Unsupported channel count: " + std::to_string(nrChannels));
            stbi_image_free(data);
            return;
        }

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        m_width = width;
        m_height = height;
        m_channels = nrChannels;

        LOG_DEBUG("Texture loaded successfully: " + filePath +
            " (" + std::to_string(width) + "x" + std::to_string(height) +
            ", " + std::to_string(nrChannels) + " channels)");
    }
    else
    {
        LOG_WARN("Failed to load texture: " + filePath);
    }

    stbi_image_free(data);

    glBindTexture(GL_TEXTURE_2D, 0);
}


void le::Texture2D::bind(GLuint unit) const
{
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, m_textureID);
}
