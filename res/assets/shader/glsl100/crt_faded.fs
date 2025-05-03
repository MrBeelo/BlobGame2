#ifdef GL_ES
precision mediump float;
#endif

varying vec2 fragTexCoord;
varying vec4 fragColor;

uniform sampler2D texture0;
uniform vec4 colDiffuse;

uniform vec2 screenCenter;
uniform float radius;
uniform float intensity;

const float distortion = 0.15;

void main()
{
    // Convert from [0,1] to [-1,1]
    vec2 uv = fragTexCoord * 2.0 - 1.0;

    // Apply barrel distortion
    uv *= 0.9;
    vec2 offset = uv * length(uv) * distortion;
    vec2 curvedUV = uv + offset;

    // Convert back to [0,1]
    vec2 distortedUV = (curvedUV + 1.0) / 2.0;

    // Clamp out-of-bounds UVs
    if (distortedUV.x < 0.0 || distortedUV.x > 1.0 || distortedUV.y < 0.0 || distortedUV.y > 1.0) {
        discard;
    }

    // Sample distorted texture
    vec4 texColor = texture2D(texture0, distortedUV) * colDiffuse * fragColor;

    // Vignette based on original coord
    float dist = distance(fragTexCoord, screenCenter);
    float darkness = clamp(dist / radius, 0.0, 1.0);
    darkness = pow(darkness, intensity);

    gl_FragColor = texColor * (1.0 - darkness);
}
