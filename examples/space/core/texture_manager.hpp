#ifndef SPACE_MESH_ASSET_HPP
#define SPACE_MESH_ASSET_HPP

#include <unordered_map>
#include <utility>
#include "../utils/stb_image.h"

class TextureManager {
public:

    static TextureManager* get() {
        static auto* instance = new TextureManager();

        return instance;
    }

    unsigned get_texture_index(const std::string& path);

private:
    TextureManager() = default;
    ~TextureManager() = default;

    static std::tuple<unsigned char *, int, int, int> open_texture_file(const std::string& path);
    static unsigned create_texture_id(unsigned char *texture_data, int width, int height, int channels);

    std::unordered_map<std::string, unsigned> textures_map;
};

#endif // SPACE_MESH_ASSET_HPP
