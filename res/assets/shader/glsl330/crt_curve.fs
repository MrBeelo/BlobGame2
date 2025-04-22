#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;
uniform vec4 colDiffuse;

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
    curvedUV = (curvedUV + 1.0) / 2.0;

    // Prevent wrapping artifacts
    if (curvedUV.x < 0.0 || curvedUV.x > 1.0 || curvedUV.y < 0.0 || curvedUV.y > 1.0) {
        discard;
    }

    finalColor = texture(texture0, curvedUV) * colDiffuse * fragColor;
}
