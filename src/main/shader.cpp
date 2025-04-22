#include "../headers/main/shader.h"
#include "../headers/main/globals.hpp"

Shader Shaders::fsShaders[13] = {0};
int Shaders::shader = FX_CRT_CURVE;
bool Shaders::useShader = true;

void Shaders::LoadContent()
{
    fsShaders[FX_PIXELIZER] = LoadShader(0, TextFormat("assets/shader/glsl%i/pixelizer.fs", GLSL_VERSION));
    fsShaders[FX_FISHEYE] = LoadShader(0, TextFormat("assets/shader/glsl%i/fisheye.fs", GLSL_VERSION));
    fsShaders[FX_GRAYSCALE] = LoadShader(0, TextFormat("assets/shader/glsl%i/grayscale.fs", GLSL_VERSION));
    fsShaders[FX_SOBEL] = LoadShader(0, TextFormat("assets/shader/glsl%i/sobel.fs", GLSL_VERSION));
    fsShaders[FX_CRT_CURVE] = LoadShader(0, TextFormat("assets/shader/glsl%i/crt_curve.fs", GLSL_VERSION));
}

void Shaders::UnloadContent()
{
    for (int i = 0; i < 13; i++) UnloadShader(fsShaders[i]);
}