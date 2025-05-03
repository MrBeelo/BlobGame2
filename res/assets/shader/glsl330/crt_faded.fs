#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;
uniform vec4 colDiffuse;

uniform vec2 screenCenter;
uniform float radius;
uniform float intensity;

out vec4 finalColor;

// Adjust this for curvature strength
const float distortion = 0.15;

void main()
{
    // Convert from [0,1] to [-1,1]
    vec2 uv = fragTexCoord * 2.0 - 1.0;

    // Apply barrel distortion (CRT-style curve)
    uv *= 0.9;
    vec2 offset = uv * length(uv) * distortion;
    vec2 curvedUV = uv + offset;

    // Back to [0,1] range
    vec2 distortedUV = (curvedUV + 1.0) / 2.0;

    // Prevent wrapping artifacts
    if (distortedUV.x < 0.0 || distortedUV.x > 1.0 || distortedUV.y < 0.0 || distortedUV.y > 1.0) {
        discard;
    }

    // Sample color from distorted texture coords
    vec4 texColor = texture(texture0, distortedUV) * colDiffuse * fragColor;

    // Compute distance from screen center
    float dist = distance(fragTexCoord, screenCenter);

    // Radial darkness (vignette effect)
    float darkness = clamp(dist / radius, 0.0, 1.0);
    darkness = pow(darkness, intensity); // Sharper falloff

    finalColor = texColor * (1.0 - darkness);
}
