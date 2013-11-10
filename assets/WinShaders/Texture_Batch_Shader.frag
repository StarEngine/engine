precision mediump float;
varying vec2 textureCoordinate;
uniform sampler2D textureSampler;

void main()
{
	vec4 color = texture2D(textureSampler, textureCoordinate);
	color.r += 0.2f;
	color.g -= 0.1f;
	color.b += 0.2f;
    gl_FragColor = color;
}
