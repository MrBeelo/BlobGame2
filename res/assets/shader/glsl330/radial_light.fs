#version 330

in vec2 fragTexCoord;
out vec4 finalColor;

uniform sampler2D texture0;
uniform vec2 screenCenter;
uniform float radius;
uniform float intensity;

void main()
{
    vec4 texColor = texture(texture0, fragTexCoord);

    // Distance from center of screen (0.0 - 1.0 range)
    float dist = distance(fragTexCoord, screenCenter);

    // Compute light falloff (soft circular gradient)
    float darkness = clamp((dist / radius), 0.0, 1.0);
    darkness = pow(darkness, intensity); // Makes edge falloff sharper

    finalColor = texColor * (1.0 - darkness);
}
