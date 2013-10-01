attribute vec4 position;
uniform vec4 inputColor;
uniform mat4 MVP;
varying vec4 color;

void main()
{
    gl_Position = MVP * position;
    color = inputColor;
}