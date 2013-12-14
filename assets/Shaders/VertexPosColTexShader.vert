precision mediump float;
attribute vec4 position;
attribute vec2 texCoord;
attribute vec4 colorMultiplier;
attribute float isHUD;
uniform mat4 scaleMatrix;
uniform mat4 viewInverseMatrix;
uniform mat4 projectionMatrix;
varying vec2 textureCoordinate;
varying vec4 color;

void main()
{
    vec4 wPos = position;
	wPos *= scaleMatrix;
	wPos *= projectionMatrix;
	if(isHUD < 0.5)
	{
		wPos *= viewInverseMatrix;
	}
	gl_Position = wPos;
    textureCoordinate = texCoord;
	color = colorMultiplier;
}
