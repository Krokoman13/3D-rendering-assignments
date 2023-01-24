#version 330

in vec2 uv;
out vec4 sColor;

uniform float rows;
uniform float colums;

uniform vec2 u_resolution;
uniform vec2 u_mouse;

void applyLight(vec2 lightSource, float strength)
{
    vec4 originalColor = sColor;
    sColor -= sColor*0.9f;

    float dis = distance(vec2(gl_FragCoord), lightSource);
    sColor += originalColor/max(0.1f, dis/(120.0f * strength));
}

void main(void)
{
    float xValue = 1 / colums;  
    float yValue = 1 / rows;

    vec2 UV_Mod = uv;

    UV_Mod.x += mod(colums, 2)/2;
    UV_Mod.y += mod(rows, 2)/2;

    float xMod = mod(UV_Mod.x, (xValue * 2)) - xValue;
    float yMod = mod(UV_Mod.y, (yValue * 2)) - yValue;

    float colorValue = (xMod/abs(xMod) * yMod/abs(yMod))/2 + 0.5f;

    sColor = vec4(colorValue, colorValue, colorValue, 1);

    applyLight(u_mouse, 1.0f);
}

/*
    float xValue = 1 / colums;  
    float yValue = 1 / rows;

    vec2 UV_Mod = uv;

    UV_Mod.x += mod(colums, 2)/2;
    UV_Mod.y += mod(rows, 2);

    float xMod = mod(UV_Mod.x, (xValue * 2));
    float yMod = mod(UV_Mod.y, (yValue * 2));

    if ((xMod > xValue && yMod > yValue) || (xMod < xValue && yMod < yValue)){
       sColor = vec4(1.0f, 1.0f, 1.0f, 1);
    }
    else 
        sColor = vec4(0.0f,0.0f,0.0f,1);

    applyLight(u_mouse, 1.0f);
    */