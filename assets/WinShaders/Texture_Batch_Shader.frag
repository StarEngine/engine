precision mediump float;
varying vec2 textureCoordinate;
uniform vec4 colorMultiplier;
uniform sampler2D textureSampler;

void main()
{
	vec4 color = texture2D(textureSampler, textureCoordinate);
	gl_FragColor = color * colorMultiplier;
}
