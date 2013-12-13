precision mediump float;
varying vec2 textureCoordinate;
varying vec4 color;
uniform sampler2D textureSampler;

void main()
{
	vec4 sampledColor = texture2D(textureSampler, textureCoordinate);
	gl_FragColor = sampledColor * color;
}
