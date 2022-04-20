#include "texture_manager.hpp"

unsigned TextureManager::get_texture_index(const std::string& path) {
    if (textures_map.contains(path)) {
        return textures_map.at(path);
    }

    auto [data, width, height, channels] = open_texture_file(path);
    if (data != nullptr) {
        unsigned texture_id = create_texture_id(data, width, height, channels);

        textures_map.insert(std::make_pair(path, texture_id));

        return texture_id;
    }

    return -1;
}

std::tuple<unsigned char *, int, int, int > TextureManager::open_texture_file(const std::string& path) {
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

    if (data) {
        std::cout << "Texture loaded: " << path << " - " << width << ", " << height << " : " << nrChannels << std::endl;
        return {data, width, height, nrChannels};
    }

    std::cout << "Failed to load texture: " << path << std::endl;
    return {nullptr, 0, 0, 0};
}

unsigned TextureManager::create_texture_id(unsigned char *texture_data, int width, int height, int channels) {
    unsigned texture_id;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    int channel_type = GL_NONE;

    switch (channels) {
        case 3: channel_type = GL_RGB;
                break;
        case 4: channel_type = GL_RGBA;
                break;
        default:
            break;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, channel_type, width, height, 0, channel_type, GL_UNSIGNED_BYTE, texture_data);
    glGenerateMipmap(GL_TEXTURE_2D);

    return texture_id;
}
