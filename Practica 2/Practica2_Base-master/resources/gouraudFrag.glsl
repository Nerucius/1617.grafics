#version 430

in vec4 color;

out vec4 FragColor;

void main()
{
    if (gl_FrontFacing)
        FragColor = color;
    else
        FragColor = vec4(0,0,0,1);
}
