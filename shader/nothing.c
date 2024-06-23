//
// Created by Piotr Krzysztof Wyrwas on 03.06.24.
//

#include "shader.h"

inline struct Pixel render_sky(double frame_height, double y)
{

//        double d = 255.0 * (1.0 - (y / frame_height));

//        return pixel_black();

//        return rgb(255, 255, 255);

//        return rgb(235, 245, 255);

        struct Pixel initialColor = rgb(255, 255, 255);
        struct Pixel targetColor = rgb(245, 246, 250);

        double deltaR = (double) targetColor.r - (double) initialColor.r;
        double deltaG = (double) targetColor.g - (double) initialColor.g;
        double deltaB = (double) targetColor.b - (double) initialColor.b;

        if (y < 0)
                y *= -1;

        double _r = ((double) initialColor.r) + (deltaR * y);
        double _g = ((double) initialColor.g) + (deltaG * y);
        double _b = ((double) initialColor.b) + (deltaB * y);

        return rgb(_r, _g, _b);
}
