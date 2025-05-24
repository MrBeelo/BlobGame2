#ifndef SHADERS_H
#define SHADERS_H

#include "../raylib/raylib.h"
#include "../sprite/player.h"
#include <string>

class Shaders
{
    public:
    const static int shaderCount = 7;
    static Shader fsShaders[];
    static void LoadContent();
    static void UnloadContent();
    static void Update(Player *player);
    enum PostproShader {FX_GRAYSCALE = 0, FX_PIXELIZER, FX_FISHEYE, FX_SOBEL, FX_CRT_CURVE, FX_CRT_FADED};
    static bool useShader;
    static int centerLoc;
    static int radiusLoc;
    static int intensityLoc;
};

#endif
