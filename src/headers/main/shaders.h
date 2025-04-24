#ifndef SHADER_H
#define SHADER_H

#include "../raylib/raylib.h"
#include <string>

class Shaders
{
    public:
    static Shader fsShaders[];
    static void LoadContent();
    static void UnloadContent();
    enum PostproShader {FX_GRAYSCALE = 0, FX_POSTERIZATION, FX_DREAM_VISION, FX_PIXELIZER, FX_CROSS_HATCHING, 
        FX_CROSS_STITCHING, FX_PREDATOR_VIEW, FX_SCANLINES, FX_FISHEYE, FX_SOBEL, FX_BLOOM, FX_BLUR, FX_CRT_CURVE};
    static int shader;
    static bool useShader;
};

#endif