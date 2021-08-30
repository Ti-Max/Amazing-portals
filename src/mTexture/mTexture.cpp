#include "mTexture.h"

mTexture::mTexture()
{
}

mTexture::mTexture(GLenum filteringType, const std::string& path)
{
    loadTexture(filteringType, path);
}

mTexture::mTexture(std::vector<std::string> faces, GLenum filteringType)
{
    loadCubeMapTexture(filteringType, faces);
}

void mTexture::load(GLenum filteringType, const std::string& path)
{
    loadTexture(filteringType, path);
}

void mTexture::loadCubeMapTexture(GLenum filteringType, std::vector<std::string> faces)
{
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_CUBE_MAP, id);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        faces[i] = "res/img/cubeMaps/" + faces[i];
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            //std::cout << "Texture " + faces[i] + " was load" << std::endl;
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
            );
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

}

void mTexture::loadTexture(GLenum filteringType, const std::string& path)
{
    std::string pathF = "res/img/" + path;
    glGenTextures(1, &id);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(pathF.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        //std::cout << "Texture " + path + " was load" << std::endl;
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, id);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filteringType);
        glBindTexture(GL_TEXTURE_2D, 0);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << pathF << std::endl;
        stbi_image_free(data);
    }
}