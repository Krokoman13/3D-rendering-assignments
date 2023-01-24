#version 330

in vec2 uv;
out vec4 sColor;

uniform float layers;
uniform float sections;

uniform vec2 u_resolution;
uniform vec2 u_mouse;

void applyLight(vec2 lightSource, float strength)
{
    vec4 originalColor = sColor;
    sColor -= sColor*0.9f;

    float dis = distance(vec2(gl_FragCoord), lightSource);
    sColor += originalColor/max(0.1f,dis/(120.0f * strength));
}

void main(void)
{
    float value = 1 / (layers - 2);
    
    vec2 midpoint = vec2(0, 0);
    float radMod = mod(distance(midpoint, uv), (value * 2)) - value;

    float angleSize = 360/sections;
    float currentAngleDegrees = degrees(atan(uv.x/uv.y));
    float circleMod = mod(currentAngleDegrees, angleSize * 2) - angleSize;

    float colorValue = (circleMod/abs(circleMod) * radMod/abs(radMod))/2 + 0.5f;

    sColor = vec4(colorValue, colorValue, colorValue, 1);

    applyLight(u_mouse, 1.0f);
}