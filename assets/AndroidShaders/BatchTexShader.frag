precision mediump float;
varying vec2 textureCoordinate;
uniform sampler2D textureSampler;
uniform vec4 colorMultiplier;

void main()
{
	vec4 color = texture2D(textureSampler, textureCoordinate);
	gl_FragColor = color * colorMultiplier;
}