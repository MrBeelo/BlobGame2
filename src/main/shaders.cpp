#include "../headers/main/shaders.h"
#include "../headers/main/globals.hpp"
#include "../headers/main/modifiers.h"

Shader Shaders::fsShaders[shaderCount] = {0};
bool Shaders::useShader = true;

void Shaders::LoadContent()
{
    fsShaders[FX_PIXELIZER] = LoadShader(0, TextFormat("assets/shader/glsl%i/pixelizer.fs", GLSL_VERSION));
    fsShaders[FX_FISHEYE] = LoadShader(0, TextFormat("assets/shader/glsl%i/fisheye.fs", GLSL_VERSION));
    fsShaders[FX_GRAYSCALE] = LoadShader(0, TextFormat("assets/shader/glsl%i/grayscale.fs", GLSL_VERSION));
    fsShaders[FX_SOBEL] = LoadShader(0, TextFormat("assets/shader/glsl%i/sobel.fs", GLSL_VERSION));
    fsShaders[FX_CRT_CURVE] = LoadShader(0, TextFormat("assets/shader/glsl%i/crt_curve.fs", GLSL_VERSION));
    fsShaders[FX_RADIAL_LIGHT] = LoadShader(0, TextFormat("assets/shader/glsl%i/radial_light.fs", GLSL_VERSION));
    fsShaders[FX_CRT_FADED] = LoadShader(0, TextFormat("assets/shader/glsl%i/crt_faded.fs", GLSL_VERSION));
}

void Shaders::UnloadContent()
{
    for (int i = 0; i < shaderCount; i++) UnloadShader(fsShaders[i]);
}

void Shaders::Update(Player *player)
{
    int centerLoc = GetShaderLocation(fsShaders[FX_CRT_FADED], "screenCenter");
    int radiusLoc = GetShaderLocation(fsShaders[FX_CRT_FADED], "radius");
    int intensityLoc = GetShaderLocation(fsShaders[FX_CRT_FADED], "intensity");
    float screenCenter[2];
    float radius;
    float intensity;
    
    if(gameState == PLAYING)
    {
        screenCenter[0] = (player->screenPos.x + player->GetSize().x / 2) / simulationSize.x;
        screenCenter[1] = 1.0f - ((player->screenPos.y + player->GetSize().y / 2) / simulationSize.y);
        radius = 1.5f;
        if(Modifiers::lightsOutMod) intensity = 0.2f; else intensity = 1.2f;
    } else {
        screenCenter[0] = 0.5f;
        screenCenter[1] = 0.5f;
        radius = 1.6f;
        intensity = 1.2f;
    }
    
    SetShaderValue(fsShaders[FX_CRT_FADED], centerLoc, screenCenter, SHADER_UNIFORM_VEC2);
    SetShaderValue(fsShaders[FX_CRT_FADED], radiusLoc, &radius, SHADER_UNIFORM_FLOAT);
    SetShaderValue(fsShaders[FX_CRT_FADED], intensityLoc, &intensity, SHADER_UNIFORM_FLOAT);
}