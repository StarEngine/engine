attribute vec3 Position;
attribute vec2 TexCoord;
uniform mat4 Projection;
uniform mat4 Translation;
varying vec2 textureCoordinate;

void main()
{
    vec4 wPos = vec4(Position,1);
	wPos *= Translation;
	wPos *= Projection;
	
	gl_Position = wPos;
    textureCoordinate = TexCoord;
}