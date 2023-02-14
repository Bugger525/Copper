#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D image;
uniform bool tex;
uniform vec3 spriteColor;

void main()
{   
    if (tex)
    {
        color = texture(image, TexCoords);
    }
    else
    {
        color = vec4(spriteColor, 1.0);
    }
}  