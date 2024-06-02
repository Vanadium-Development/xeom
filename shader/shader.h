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

#define ShaderFunction(id, _inter, _scene) struct Pixel id(struct Intersection *_inter, struct Scene *_scene)
#define PredefinedShader(id) ShaderFunction(id, intersection, scene)

PredefinedShader(shader_binary);

#endif //XEOM_SHADER_H
