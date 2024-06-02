//
// Created by Piotr Krzysztof Wyrwas on 02.06.24.
//

#ifndef XEOM_CAMERA_H
#define XEOM_CAMERA_H

#include "../math/vec3d.h"

#include <inttypes.h>

struct Camera {
        struct Vec3d location;
        double focal_length;
        uint64_t frame_width;
        uint64_t frame_height;
};

#endif //XEOM_CAMERA_H
