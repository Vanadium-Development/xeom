//
// Created by Piotr Krzysztof Wyrwas on 03.06.24.
//

#include "shader.h"

inline struct Pixel render_sky(double frame_height, double y) {

//        double d = 255.0 * (1.0 - (y / frame_height));

        return rgb(255, 255, 255);

//        struct Pixel initialColor = rgb(52, 152, 219);
//        struct Pixel targetColor = rgb(236, 240, 241);
//
//        double deltaR = targetColor.r - initialColor.r;
//        double deltaG = targetColor.g - initialColor.g;
//        double deltaB = targetColor.b - initialColor.b;
//
//        return (struct Pixel) {
//                .r = initialColor.r + (deltaR / (double) frame_height) * (double) y,
//                .g = initialColor.g + (deltaG / (double) frame_height) * (double) y,
//                .b = initialColor.b + (deltaB / (double) frame_height) * (double) y,
//        };
}
