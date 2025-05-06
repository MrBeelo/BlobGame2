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

//BLOOM
const vec2 size = vec2(800, 450);   // Framebuffer size
const float samples = 5.0;          // Pixels per axis; higher = bigger glow, worse performance
const float quality = 2.5;          // Defines size factor: Lower = smaller glow, better quality

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
    
    vec4 baseColor = texColor * (1.0 - darkness);
    
    // BLOOM calculation (simple blur around bright areas)
    vec4 sum = vec4(0);
    vec2 sizeFactor = vec2(1)/size*quality;
    
    const int range = 2;            // should be = (samples - 1)/2;
    
    for (int x = -range; x <= range; x++)
    {
        for (int y = -range; y <= range; y++)
        {
            vec2 sampleCoord = distortedUV + vec2(x, y) * sizeFactor;
            float sampleDist = distance(sampleCoord, screenCenter);
            float sampleDarkness = pow(clamp(sampleDist / radius, 0.0, 1.0), intensity);
        
            vec4 sampleColor = texture(texture0, sampleCoord) * (1.0 - sampleDarkness);
            sum += sampleColor;
        }
    }
    
    vec4 bloom = ((sum/(samples*samples)))*colDiffuse;

    gl_FragColor = baseColor + bloom * 0.2;
}
