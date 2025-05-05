#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;
uniform vec4 colDiffuse;

uniform vec2 screenCenter;
uniform float radius;
uniform float intensity;

out vec4 finalColor;

//CRT CURVE
const float distortion = 0.15;

//BLOOM
const vec2 size = vec2(800, 450);   // Framebuffer size
const float samples = 5.0;          // Pixels per axis; higher = bigger glow, worse performance
const float quality = 2.5;          // Defines size factor: Lower = smaller glow, better quality

void main()
{
// Convert [0,1] -> [-1,1] for distortion
    vec2 uv = fragTexCoord * 2.0 - 1.0;

    // Apply CRT barrel distortion
    uv *= 0.9;
    vec2 offset = uv * length(uv) * distortion;
    vec2 curvedUV = uv + offset;

    // Back to [0,1] for sampling
    vec2 distortedUV = (curvedUV + 1.0) / 2.0;

    // Clamp to avoid artifacts
    if (distortedUV.x < 0.0 || distortedUV.x > 1.0 || distortedUV.y < 0.0 || distortedUV.y > 1.0)
        discard;

    // Sample the base color with curvature
    vec4 texColor = texture(texture0, distortedUV) * colDiffuse * fragColor;

    // Vignette (radial fade from center)
    float dist = distance(fragTexCoord, screenCenter);
    float darkness = pow(clamp(dist / radius, 0.0, 1.0), intensity);
    vec4 baseColor = texColor * (1.0 - darkness);

    // BLOOM calculation (simple blur around bright areas)
    vec4 sum = vec4(0);
    vec2 sizeFactor = vec2(1)/size*quality;
    
    // Texel color fetching from texture sampler
    vec4 source = texture(texture0, distortedUV);
    
    const int range = 2;            // should be = (samples - 1)/2;
    
    for (int x = -range; x <= range; x++)
    {
        for (int y = -range; y <= range; y++)
        {
            sum += texture(texture0, distortedUV + vec2(x, y)*sizeFactor);
        }
    }
    vec4 bloom = ((sum/(samples*samples)) + source)*colDiffuse;

    // Final color: base + bloom (additive)
    finalColor = baseColor + bloom * 0.2; // Scale bloom if too strong
}
