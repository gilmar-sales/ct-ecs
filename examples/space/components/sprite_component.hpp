#ifndef SPACE_ECS_SPRITECOMPONENT_H
#define SPACE_ECS_SPRITECOMPONENT_H

#include <vector>

namespace ecs {
    struct SpriteComponent {
        unsigned width;
        unsigned height;
        unsigned textures[8];
        unsigned textures_count;
        float frame_time;
    };
}

#endif //SPACE_ECS_SPRITECOMPONENT_H
