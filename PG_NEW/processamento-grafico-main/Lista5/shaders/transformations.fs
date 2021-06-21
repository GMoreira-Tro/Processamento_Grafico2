#version 450 core

in vec3 ourColor;
in vec2 TexCoord;

out vec4 color;

// Texture sampler
uniform sampler2D ourTexture1;

uniform int channel;        // Image filter channel
uniform vec3 modifier;      // Modifier
uniform vec3 resolution;    // Resolution of window

void main()
{
    color = texture(ourTexture1, TexCoord);
    float grayScale = color.r * 0.2125 + color.g * 0.7154 + color.b * 0.0721;

    switch(channel)
    {
    case 1:
        color = vec4(color.r, 0, 0, 1);
        break;
    case 2:
        color = vec4(0, color.g, 0, 1);
        break;
    case 3:
        color = vec4(0,0,color.b,1);
        break;
    case 4:
        color = vec4(grayScale, grayScale, grayScale, 1);
        break;
    case 5:
        color = vec4(color.r + modifier.r, color.g + modifier.g, color.b + modifier.b, 1.0);
        break;
    case 6:
        color = vec4(1 - color.r, 1 - color.g, 1 - color.b, 1);
        break;
    case 7:
        if(grayScale < 0.5f)
        {
            color = vec4(0,0,0,1);
        }
        else
        {
            color = vec4(1,1,1,1);
        }
        break;
    case 8:
        ////Dark Purple :3
        //color = vec4(color.r/2, 0, color.b/2, 1);
        //If pixel is too dark, turn into white.
        if(grayScale < 0.12)
        {
            color = vec4(1,1,1,1);
        }
        break;
    case 9:
        vec4 texColor = texture2D(ourTexture1, TexCoord);
        vec2 position = (gl_FragCoord.xy / resolution.xy) - vec2(0.5);
        float len = length(position);
        
        //Squared vignette :/... Not good at all, sorry teacher.
        if(len > 0.5)
        {
            color = vec4(0,0,0,1);
        }
	    
        break;
    }
}