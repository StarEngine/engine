attribute vec3 Position;
attribute vec2 TexCoord;
uniform mat4 MVP;
varying vec2 textureCoordinate;

void main()
{
    vec4 wPos = vec4(Position,1);
	wPos *= MVP;
	
	gl_Position = wPos;
    textureCoordinate = TexCoord;
}