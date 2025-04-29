#include "../headers/main/shaders.h"
#include "../headers/main/globals.hpp"

Shader Shaders::fsShaders[14] = {0};
bool Shaders::useShader = true;

void Shaders::LoadContent()
{
    fsShaders[FX_PIXELIZER] = LoadShader(0, TextFormat("assets/shader/glsl%i/pixelizer.fs", GLSL_VERSION));
    fsShaders[FX_FISHEYE] = LoadShader(0, TextFormat("assets/shader/glsl%i/fisheye.fs", GLSL_VERSION));
    fsShaders[FX_GRAYSCALE] = LoadShader(0, TextFormat("assets/shader/glsl%i/grayscale.fs", GLSL_VERSION));
    fsShaders[FX_SOBEL] = LoadShader(0, TextFormat("assets/shader/glsl%i/sobel.fs", GLSL_VERSION));
    fsShaders[FX_CRT_CURVE] = LoadShader(0, TextFormat("assets/shader/glsl%i/crt_curve.fs", GLSL_VERSION));
    fsShaders[FX_RADIAL_LIGHT] = LoadShader(0, TextFormat("assets/shader/glsl%i/radial_light.fs", GLSL_VERSION));
}

void Shaders::UnloadContent()
{
    for (int i = 0; i < 13; i++) UnloadShader(fsShaders[i]);
}

void Shaders::Update()
{
    int centerLoc = GetShaderLocation(fsShaders[FX_RADIAL_LIGHT], "screenCenter");
    int radiusLoc = GetShaderLocation(fsShaders[FX_RADIAL_LIGHT], "radius");
    int intensityLoc = GetShaderLocation(fsShaders[FX_RADIAL_LIGHT], "intensity");
    
    float screenCenter[2] = { 0.5f, 0.5f }; // normalized coords
    float radius = 0.5f; // 0.0 to 1.0
    float intensity = 0.4f; // higher = sharper falloff
    
    SetShaderValue(fsShaders[FX_RADIAL_LIGHT], centerLoc, screenCenter, SHADER_UNIFORM_VEC2);
    SetShaderValue(fsShaders[FX_RADIAL_LIGHT], radiusLoc, &radius, SHADER_UNIFORM_FLOAT);
    SetShaderValue(fsShaders[FX_RADIAL_LIGHT], intensityLoc, &intensity, SHADER_UNIFORM_FLOAT);

}