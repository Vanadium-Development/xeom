//
// Created by Piotr Krzysztof Wyrwas on 02.06.24.
//

#ifndef XEOM_SHADER_H
#define XEOM_SHADER_H

#include "callback.h"

#include "../image/image.h"

#include "../math/shape.h"

#include "../core/scene.h"

#include "../math/utility.h"

#define ShaderFunction(id, _inter, _scene, _bounces) struct Pixel id(struct Intersection *_inter, struct Scene *_scene, uint64_t _bounces)
#define PredefinedShader(id) ShaderFunction(id, intersection, scene, bounces)

struct Pixel render_sky(double frame_height, double y);

PredefinedShader(shader_binary);
PredefinedShader(shader_normal);
PredefinedShader(shader_metal);
PredefinedShader(shader_nothing);
PredefinedShader(shader_diffuse);

#endif //XEOM_SHADER_H
